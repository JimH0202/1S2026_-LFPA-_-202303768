#pragma once
#include <string>
#include <vector>
#include "Token.h"
#include "ErrorManager.h"

class LexicalAnalyzer {
private:
    std::string input;
    size_t index;
    int line;
    int column;
    int tokenCounter;

    ErrorManager* errorManager;

    char peek() const;
    char advance();
    bool isAtEnd() const;

public:
    LexicalAnalyzer(const std::string& text, ErrorManager* errorManager);

    Token nextToken();
};
