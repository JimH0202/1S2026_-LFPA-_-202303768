#pragma once
#include <string>
#include <vector>

enum class ErrorType {
    LEXICO,
    SINTACTICO
};

enum class ErrorSeverity {
    ERROR,
    CRITICO
};

struct ErrorInfo {
    int number;
    std::string lexeme;
    ErrorType type;
    std::string description;
    int line;
    int column;
    ErrorSeverity severity;
};
class ErrorManager {
private:
    std::vector<ErrorInfo> errors;
    int errorCounter;

public:
    ErrorManager() : errorCounter(1) {}

    void addLexicalError(const std::string& lexeme, const std::string& description, int line, int column);
    void addSyntaxError(const std::string& lexeme, const std::string& description, int line, int column);

    const std::vector<ErrorInfo>& getErrors() const { return errors; }
    bool hasErrors() const { return !errors.empty(); }
};
