#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include "Token.h"
#include "ErrorManager.h"
#include <string>
#include <vector>
#include <set>

class LexicalAnalyzer {
private:
    std::string input;
    size_t pos;
    int line;
    int column;
    ErrorManager* errorManager;
    std::vector<Token> tokens;

    // Helper sets for validation
    std::set<std::string> keywords = {"HOSPITAL", "PACIENTES", "MEDICOS", "CITAS", "DIAGNOSTICOS"};
    std::set<std::string> specialties = {"CARDIOLOGIA", "NEUROLOGIA", "PEDIATRIA", "CIRUGIA", "MEDICINA_GENERAL", "ONCOLOGIA", "ENDOCRINOLOGIA", "NEUMOLOGIA"};
    std::set<std::string> dosis = {"DIARIA", "CADA_8_HORAS", "CADA_12_HORAS", "SEMANAL"};
    std::set<std::string> bloodTypes = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};

    char peek() const;
    char get();
    void unget();
    bool isDigit(char c) const;
    bool isAlpha(char c) const;
    bool isAlphaNum(char c) const;
    bool isWhitespace(char c) const;
    TokenType classifyIdentifier(const std::string& lexeme);
    bool isValidDate(const std::string& date);
    bool isValidTime(const std::string& time);
    bool isValidBloodType(const std::string& bt);
    bool isValidSpecialty(const std::string& sp);
    bool isValidDosis(const std::string& ds);
    bool isValidCode(const std::string& code);
    Token scanIdentifierOrBloodType(int startLine, int startCol, const std::string& firstPart);

public:
    LexicalAnalyzer(const std::string& src, ErrorManager* errMgr);
    Token nextToken();
    void tokenize();
    std::vector<Token> getTokens() const;
    void printTokens() const;
};

#endif // LEXICALANALYZER_H