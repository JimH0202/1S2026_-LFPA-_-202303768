#include "SyntaxAnalyzer.h"

SyntaxAnalyzer::SyntaxAnalyzer(LexicalAnalyzer* lexer, ErrorManager* errorManager)
    : lexer(lexer), errorManager(errorManager) {
    currentToken = lexer->nextToken();
}

void SyntaxAnalyzer::parse() {
    programa();
}
void SyntaxAnalyzer::advance() {
    currentToken = lexer->nextToken();
}
bool SyntaxAnalyzer::match(TokenType expected) {
    if (currentToken.type == expected) {
        advance();
        return true;
    }
    return false;
}
void SyntaxAnalyzer::syntaxError(const std::string& expected) {
    errorManager->addSyntaxError(currentToken.getLexeme(), "Se esperaba: " + expected, currentToken.getLine(), currentToken.getColumn());
    advance(); // Intentar recuperar avanzando al siguiente token
}
bool SyntaxAnalyzer::match(TokenType expected) {
    if (currentToken.getType() == expected) {
        advance();
        return true;
    }

    syntaxError("Se esperaba token " + std::to_string((int)expected));
    return false;
}
void SyntaxAnalyzer::syntaxError(const std::string& expected) {
    errorManager->addSyntaxError(
        currentToken.getLexeme(),
        expected,
        currentToken.getLine(),
        currentToken.getColumn()
    );

    // Recuperación básica: avanzar hasta un delimitador seguro
    while (currentToken.getType() != TokenType::PUNTO_Y_COMA &&
           currentToken.getType() != TokenType::LLAVE_CIERRA &&
           currentToken.getType() != TokenType::END_OF_FILE) {
        advance();
    }
}
// <programa>       ::= TABLERO CADENA "{" <columnas> "}" ";"
//<columnas>       ::= <columna> <columnas> | <columna>
//<columna>        ::= COLUMNA CADENA "{" <tareas> "}" ";"
//<tareas>         ::= <tarea> "," <tareas> | <tarea>
//<tarea>          ::= tarea ":" CADENA "[" <atributos> "]"
//<atributos>      ::= <atributo> "," <atributos> | <atributo>
//<atributo>       ::= prioridad ":" <prioridad>
//                   | responsable ":" CADENA
//                   | fecha_limite ":" FECHA
//<prioridad>      ::= ALTA | MEDIA | BAJA

void SyntaxAnalyzer::programa() {
    match(TokenType::TABLERO);
    match(TokenType::CADENA);
    match(TokenType::LLAVE_ABRE);

    columnas();

    match(TokenType::LLAVE_CIERRA);
    match(TokenType::PUNTO_Y_COMA);
}
void SyntaxAnalyzer::columnas() {
    columna();

    while (currentToken.getType() == TokenType::COLUMNA) {
        columna();
    }
}
void SyntaxAnalyzer::columna() {
    match(TokenType::COLUMNA);
    match(TokenType::CADENA);
    match(TokenType::LLAVE_ABRE);

    tareas();

    match(TokenType::LLAVE_CIERRA);
    match(TokenType::PUNTO_Y_COMA);
}
void SyntaxAnalyzer::tareas() {
    tarea();

    while (currentToken.getType() == TokenType::COMA) {
        match(TokenType::COMA);
        tarea();
    }
}
void SyntaxAnalyzer::tarea() {
    match(TokenType::TAREA);
    match(TokenType::DOS_PUNTOS);
    match(TokenType::CADENA);
    match(TokenType::CORCHETE_ABRE);

    atributos();

    match(TokenType::CORCHETE_CIERRA);
}
void SyntaxAnalyzer::atributos() {
    atributo();

    while (currentToken.getType() == TokenType::COMA) {
        match(TokenType::COMA);
        atributo();
    }
}
void SyntaxAnalyzer::atributo() {
    if (currentToken.getType() == TokenType::PRIORIDAD) {
        match(TokenType::PRIORIDAD);
        match(TokenType::DOS_PUNTOS);
        prioridad();
        return;
    }

    if (currentToken.getType() == TokenType::RESPONSABLE) {
        match(TokenType::RESPONSABLE);
        match(TokenType::DOS_PUNTOS);
        match(TokenType::CADENA);
        return;
    }

    if (currentToken.getType() == TokenType::FECHA_LIMITE) {
        match(TokenType::FECHA_LIMITE);
        match(TokenType::DOS_PUNTOS);
        match(TokenType::FECHA);
        return;
    }

    syntaxError("Se esperaba un atributo válido");
    advance();
}
void SyntaxAnalyzer::prioridad() {
    if (currentToken.getType() == TokenType::ALTA ||
        currentToken.getType() == TokenType::MEDIA ||
        currentToken.getType() == TokenType::BAJA) {
        advance();
    } else {
        syntaxError("Se esperaba ALTA, MEDIA o BAJA");
        advance();
    }
}
