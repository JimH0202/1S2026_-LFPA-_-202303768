#include "ErrorManager.h"
#include <iostream>

void ErrorManager::addError(const std::string& lex, const std::string& errType, const std::string& desc, int ln, int col, const std::string& sev) {
    errorCount++;
    errors.push_back({errorCount, lex, errType, desc, ln, col, sev});
}

bool ErrorManager::hasErrors() const {
    return !errors.empty();
}

const std::vector<LexError>& ErrorManager::getErrors() const {
    return errors;
}

void ErrorManager::clear() {
    errors.clear();
    errorCount = 0;
}

void ErrorManager::printErrors() const {
    for (const auto& err : errors) {
        std::cout << "Error " << err.id << ": " << err.errorType << " - " << err.description
                  << " at line " << err.line << ", column " << err.column << " (Lexeme: '" << err.lexeme << "')" << std::endl;
    }
}