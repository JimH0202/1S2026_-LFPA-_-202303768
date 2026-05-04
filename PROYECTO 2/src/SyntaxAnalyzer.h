#pragma once
#include "LexicalAnalyzer.h"
#include "ErrorManager.h"
#include "BoardModel.h"

class SyntaxAnalyzer {
private:
    LexicalAnalyzer* lexer;
    ErrorManager* errorManager;

    Token currentToken;

    void advance();
    bool match(TokenType expected);
    void syntaxError(const std::string& expected);

    // Reglas de la gramática
    void programa();
    void columnas();
    void columna();
    void tareas();
    void tarea();
    void atributos();
    void atributo();
    void prioridad();

public:
    SyntaxAnalyzer(LexicalAnalyzer* lexer, ErrorManager* errorManager);

    void parse();
};
