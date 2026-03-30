#include "Token.h"
#include <sstream>
#include <map>

Token::Token(TokenType t, const std::string& l, int ln, int col)
    : type(t), lexeme(l), line(ln), column(col) {}

std::string getTokenTypeName(TokenType type) {
    static const std::map<TokenType, std::string> typeMap = {
        {TokenType::HOSPITAL, "HOSPITAL"},
        {TokenType::PACIENTES, "PACIENTES"},
        {TokenType::MEDICOS, "MEDICOS"},
        {TokenType::CITAS, "CITAS"},
        {TokenType::DIAGNOSTICOS, "DIAGNOSTICOS"},
        {TokenType::IDENTIFIER, "IDENTIFIER"},
        {TokenType::STRING, "STRING"},
        {TokenType::INTEGER, "INTEGER"},
        {TokenType::DATE, "DATE"},
        {TokenType::TIME, "TIME"},
        {TokenType::CODE, "CODE"},
        {TokenType::SPECIALTY, "SPECIALTY"},
        {TokenType::DOSIS, "DOSIS"},
        {TokenType::BLOOD_TYPE, "BLOOD_TYPE"},
        {TokenType::SYMBOL, "SYMBOL"},
        {TokenType::ERROR, "ERROR"},
        {TokenType::END_OF_FILE, "END_OF_FILE"}
    };
    
    auto it = typeMap.find(type);
    return it != typeMap.end() ? it->second : "UNKNOWN";
}

std::string Token::toString() const {
    std::stringstream ss;
    ss << "[" << getTokenTypeName(type) << "] '" << lexeme << "' (L" << line << ":C" << column << ")";
    return ss.str();
}