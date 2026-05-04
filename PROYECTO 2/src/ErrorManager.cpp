#include "ErrorManager.h"

void ErrorManager::addLexicalError(const std::string& lexeme, const std::string& description, int line, int column) {
    errors.push_back({
        errorCounter++,
        lexeme,
        ErrorType::LEXICO,
        description,
        line,
        column,
        ErrorSeverity::ERROR
    });
}

void ErrorManager::addSyntaxError(const std::string& lexeme, const std::string& description, int line, int column) {
    errors.push_back({
        errorCounter++,
        lexeme,
        ErrorType::SINTACTICO,
        description,
        line,
        column,
        ErrorSeverity::ERROR
    });
}
