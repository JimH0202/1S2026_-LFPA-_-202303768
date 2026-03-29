#include "Token.h"
#include <sstream>

Token::Token(TokenType t, const std::string& l, int ln, int col)
    : type(t), lexeme(l), line(ln), column(col) {}

std::string Token::toString() const {
    std::stringstream ss;
    ss << "Token(Type: " << static_cast<int>(type) << ", Lexeme: '" << lexeme << "', Line: " << line << ", Column: " << column << ")";
    return ss.str();
}