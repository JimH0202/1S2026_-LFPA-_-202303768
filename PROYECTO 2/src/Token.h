#pragma once
#include <string>
#include "TokenType.h"

class Token {
private:
    int number;
    std::string lexeme;
    TokenType type;
    int line;
    int column;

public:
    Token()
        : number(0), lexeme(""), type(TokenType::END_OF_FILE), line(0), column(0) {}

    Token(int number, const std::string& lexeme, TokenType type, int line, int column)
        : number(number), lexeme(lexeme), type(type), line(line), column(column) {}

    int getNumber() const { return number; }
    const std::string& getLexeme() const { return lexeme; }
    TokenType getType() const { return type; }
    int getLine() const { return line; }
    int getColumn() const { return column; }
};
