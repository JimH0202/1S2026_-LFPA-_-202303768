#include "LexicalAnalyzer.h"
#include <iostream>
#include <cctype>

LexicalAnalyzer::LexicalAnalyzer(const std::string& src, ErrorManager* errMgr)
    : input(src), pos(0), line(1), column(1), errorManager(errMgr) {}

char LexicalAnalyzer::peek() const {
    if (pos >= input.size()) return '\0';
    return input[pos];
}

char LexicalAnalyzer::get() {
    if (pos >= input.size()) return '\0';
    char c = input[pos++];
    if (c == '\n') {
        line++;
        column = 1;
    } else {
        column++;
    }
    return c;
}

void LexicalAnalyzer::unget() {
    if (pos > 0) {
        pos--;
        if (input[pos] == '\n') {
            line--;
        } else {
            column--;
        }
    }
}

bool LexicalAnalyzer::isDigit(char c) const { return std::isdigit(c); }
bool LexicalAnalyzer::isAlpha(char c) const { return std::isalpha(c); }
bool LexicalAnalyzer::isAlphaNum(char c) const { return std::isalnum(c) || c == '_'; }
bool LexicalAnalyzer::isWhitespace(char c) const { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }

TokenType LexicalAnalyzer::classifyIdentifier(const std::string& lexeme) {
    if (keywords.count(lexeme)) {
        if (lexeme == "HOSPITAL") return TokenType::HOSPITAL;
        if (lexeme == "PACIENTES") return TokenType::PACIENTES;
        if (lexeme == "MEDICOS") return TokenType::MEDICOS;
        if (lexeme == "CITAS") return TokenType::CITAS;
        if (lexeme == "DIAGNOSTICOS") return TokenType::DIAGNOSTICOS;
    }
    if (specialties.count(lexeme)) return TokenType::SPECIALTY;
    if (dosis.count(lexeme)) return TokenType::DOSIS;
    return TokenType::IDENTIFIER;
}

bool LexicalAnalyzer::isValidDate(const std::string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') return false;
    try {
        int year = std::stoi(date.substr(0, 4));
        int month = std::stoi(date.substr(5, 2));
        int day = std::stoi(date.substr(8, 2));
        if (month < 1 || month > 12) return false;
        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) daysInMonth[1] = 29;
        return day >= 1 && day <= daysInMonth[month - 1];
    } catch (...) { return false; }
}

bool LexicalAnalyzer::isValidTime(const std::string& time) {
    if (time.size() != 5 || time[2] != ':') return false;
    try {
        int hour = std::stoi(time.substr(0, 2));
        int min = std::stoi(time.substr(3, 2));
        return hour >= 0 && hour <= 23 && min >= 0 && min <= 59;
    } catch (...) { return false; }
}

bool LexicalAnalyzer::isValidBloodType(const std::string& bt) { return bloodTypes.count(bt) > 0; }
bool LexicalAnalyzer::isValidSpecialty(const std::string& sp) { return specialties.count(sp) > 0; }
bool LexicalAnalyzer::isValidDosis(const std::string& ds) { return dosis.count(ds) > 0; }

bool LexicalAnalyzer::isValidCode(const std::string& code) {
    if (code.size() < 7) return false;
    if (code[3] != '-') return false;
    for (size_t i = 0; i < 3; ++i) if (!isAlpha(code[i]) || !std::isupper(code[i])) return false;
    for (size_t i = 4; i < code.size(); ++i) if (!isDigit(code[i])) return false;
    return true;
}

Token LexicalAnalyzer::scanIdentifierOrBloodType(int startLine, int startCol, const std::string& firstPart) {
    std::string lex = firstPart;
    while (isAlphaNum(peek())) lex += get();
    
    // Blood type check (A+, B-, AB+, etc.)
    if ((lex == "A" || lex == "B" || lex == "O" || lex == "AB") && (peek() == '+' || peek() == '-')) {
        std::string bt = lex + get();
        if (isValidBloodType(bt)) {
            return Token(TokenType::BLOOD_TYPE, bt, startLine, startCol);
        }
        errorManager->addError(bt, "Invalid Blood Type", "Invalid: " + bt, startLine, startCol);
        return Token(TokenType::ERROR, bt, startLine, startCol);
    }
    
    // Code format check (XXX-###)
    if (lex.size() == 3 && peek() == '-') {
        lex += get();
        while (isDigit(peek())) lex += get();
        if (isValidCode(lex)) {
            return Token(TokenType::CODE, lex, startLine, startCol);
        }
        errorManager->addError(lex, "Invalid Code", "Bad format: " + lex, startLine, startCol);
        return Token(TokenType::ERROR, lex, startLine, startCol);
    }
    
    TokenType type = classifyIdentifier(lex);
    if (type == TokenType::SPECIALTY && !isValidSpecialty(lex)) {
        errorManager->addError(lex, "Invalid Specialty", "Unknown: " + lex, startLine, startCol);
        return Token(TokenType::ERROR, lex, startLine, startCol);
    }
    if (type == TokenType::DOSIS && !isValidDosis(lex)) {
        errorManager->addError(lex, "Invalid Dosis", "Unknown: " + lex, startLine, startCol);
        return Token(TokenType::ERROR, lex, startLine, startCol);
    }
    return Token(type, lex, startLine, startCol);
}

Token LexicalAnalyzer::nextToken() {
    while (pos < input.size()) {
        char c = peek();
        if (isWhitespace(c)) {
            get();
            continue;
        }
        if (c == '/' && pos + 1 < input.size() && input[pos + 1] == '/') {
            get(); get();
            while (pos < input.size() && get() != '\n');
            continue;
        }

        int startLine = line, startCol = column;

        if (c == '"') {
            get();
            std::string lex = "\"";
            bool closed = false;
            while (pos < input.size()) {
                c = get();
                if (c == '"') {
                    lex += "\"";
                    closed = true;
                    break;
                } else if (c == '\n') {
                    break;
                } else {
                    lex += c;
                }
            }
            if (!closed) {
                errorManager->addError(lex, "Unclosed String", "Not closed", startLine, startCol);
                return Token(TokenType::ERROR, lex, startLine, startCol);
            }
            return Token(TokenType::STRING, lex, startLine, startCol);
            
        } else if (isDigit(c)) {
            std::string lex;
            while (isDigit(peek())) lex += get();
            
            if (peek() == '-') {
                lex += get();
                while (isDigit(peek())) lex += get();
                if (peek() == '-') {
                    lex += get();
                    while (isDigit(peek())) lex += get();
                    if (isValidDate(lex)) {
                        return Token(TokenType::DATE, lex, startLine, startCol);
                    } else {
                        errorManager->addError(lex, "Invalid Date", "Bad date: " + lex, startLine, startCol);
                        return Token(TokenType::ERROR, lex, startLine, startCol);
                    }
                } else {
                    errorManager->addError(lex, "Invalid Token", "Bad format", startLine, startCol);
                    return Token(TokenType::ERROR, lex, startLine, startCol);
                }
            } else if (peek() == ':') {
                lex += get();
                while (isDigit(peek())) lex += get();
                if (isValidTime(lex)) {
                    return Token(TokenType::TIME, lex, startLine, startCol);
                } else {
                    errorManager->addError(lex, "Invalid Time", "Bad time: " + lex, startLine, startCol);
                    return Token(TokenType::ERROR, lex, startLine, startCol);
                }
            } else {
                return Token(TokenType::INTEGER, lex, startLine, startCol);
            }
            
        } else if (isAlpha(c) || c == '_') {
            std::string firstChar(1, get());
            return scanIdentifierOrBloodType(startLine, startCol, firstChar);
            
        } else if (c == '{' || c == '}' || c == '[' || c == ']' || c == ':' || c == ',' || c == ';') {
            get();
            return Token(TokenType::SYMBOL, std::string(1, c), startLine, startCol);
            
        } else {
            get();
            std::string lex(1, c);
            errorManager->addError(lex, "Invalid Character", "Unexpected: " + lex, startLine, startCol);
            return Token(TokenType::ERROR, lex, startLine, startCol);
        }
    }
    return Token(TokenType::END_OF_FILE, "", line, column);
}

void LexicalAnalyzer::tokenize() {
    tokens.clear();
    Token tok = nextToken();
    while (tok.type != TokenType::END_OF_FILE) {
        tokens.push_back(tok);
        tok = nextToken();
    }
}

std::vector<Token> LexicalAnalyzer::getTokens() const {
    return tokens;
}

void LexicalAnalyzer::printTokens() const {
    for (const auto& tok : tokens) {
        std::cout << tok.toString() << std::endl;
    }
}
