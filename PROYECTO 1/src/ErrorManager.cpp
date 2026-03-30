#include "ErrorManager.h"
#include <iostream>
#include <iomanip>

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
    if (errors.empty()) {
        std::cout << "\n[SUCCESS] No errors found during lexical analysis!" << std::endl;
        return;
    }
    
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "LEXICAL ANALYSIS - ERROR REPORT" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    
    for (const auto& err : errors) {
        std::cout << "\n[" << err.severity << " #" << err.id << "] " << err.errorType << std::endl;
        std::cout << "  Location: Line " << err.line << ", Column " << err.column << std::endl;
        std::cout << "  Lexeme: '" << err.lexeme << "'" << std::endl;
        std::cout << "  Details: " << err.description << std::endl;
    }
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "Total Errors: " << errors.size() << std::endl;
    std::cout << std::string(80, '=') << std::endl;
}