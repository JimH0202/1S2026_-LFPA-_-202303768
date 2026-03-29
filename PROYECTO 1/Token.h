#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    HOSPITAL, PACIENTES, MEDICOS, CITAS, DIAGNOSTICOS,
    IDENTIFIER, STRING, INTEGER, DATE, TIME, CODE,
    SPECIALTY, DOSIS, BLOOD_TYPE, SYMBOL, ERROR, END_OF_FILE
};

class Token {
public:
    TokenType type;
    std::string lexeme;
    int line;
    int column;

    Token(TokenType t, const std::string& l, int ln, int col);
    std::string toString() const;
};

#endif // TOKEN_H