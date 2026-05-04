#include "LexicalAnalyzer.h"
#include <cctype>

LexicalAnalyzer::LexicalAnalyzer(const std::string& text, ErrorManager* errorManager)
    : input(text), index(0), line(1), column(1), tokenCounter(1), errorManager(errorManager) {}

char LexicalAnalyzer::peek() const {
    if (isAtEnd()) return '\0';
    return input[index];
}

char LexicalAnalyzer::advance() {
    char c = peek();
    index++;
    column++;
    return c;
}

bool LexicalAnalyzer::isAtEnd() const {
    return index >= input.size();
}
