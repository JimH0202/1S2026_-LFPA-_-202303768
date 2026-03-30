#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H

#include <string>
#include <vector>

struct LexError {
    int id;
    std::string lexeme;
    std::string errorType;
    std::string description;
    int line;
    int column;
    std::string severity; // "ERROR" or "CRITICAL"
};

class ErrorManager {
private:
    std::vector<LexError> errors;
    int errorCount = 0;

public:
    void addError(const std::string& lex, const std::string& errType, const std::string& desc, int ln, int col, const std::string& sev = "ERROR");
    bool hasErrors() const;
    const std::vector<LexError>& getErrors() const;
    void clear();
    void printErrors() const;
};

#endif // ERRORMANAGER_H