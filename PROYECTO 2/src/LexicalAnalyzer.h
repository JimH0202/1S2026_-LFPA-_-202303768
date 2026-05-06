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
    std::vector<Token> tokens; // ← Agregar vector para almacenar tokens

    Token addToken(const Token& token) {
        tokens.push_back(token);
        return token;
    }

    bool isIdentifierStart(char c) const {
        return std::isalpha(static_cast<unsigned char>(c)) || c == '_';
    }

    bool isIdentifierPart(char c) const {
        return std::isalnum(static_cast<unsigned char>(c)) || c == '_';
    }

    char peek() const;
    char advance();
    bool isAtEnd() const;

public:
    LexicalAnalyzer(const std::string& text, ErrorManager* errorManager);

    Token nextToken() {
    // 1. Saltar espacios y saltos de línea
    while (!isAtEnd()) {
        char c = peek();

        if (c == ' ' || c == '\t' || c == '\r') {
            advance();
            continue;
        }

        if (c == '\n') {
            advance();
            line++;
            column = 1;
            continue;
        }

        break;
    }

    // 2. Fin de archivo
    if (isAtEnd()) {
        return addToken(Token(tokenCounter++, "EOF", TokenType::END_OF_FILE, line, column));
    }

    char c = advance();

    // 3. Delimitadores
    switch (c) {
        case '{': return addToken(Token(tokenCounter++, "{", TokenType::LLAVE_ABRE, line, column - 1));
        case '}': return addToken(Token(tokenCounter++, "}", TokenType::LLAVE_CIERRA, line, column - 1));
        case '[': return addToken(Token(tokenCounter++, "[", TokenType::CORCHETE_ABRE, line, column - 1));
        case ']': return addToken(Token(tokenCounter++, "]", TokenType::CORCHETE_CIERRA, line, column - 1));
        case ':': return addToken(Token(tokenCounter++, ":", TokenType::DOS_PUNTOS, line, column - 1));
        case ',': return addToken(Token(tokenCounter++, ",", TokenType::COMA, line, column - 1));
        case ';': return addToken(Token(tokenCounter++, ";", TokenType::PUNTO_Y_COMA, line, column - 1));
    }

    // 4. Palabras reservadas o literales
    if (isIdentifierStart(c)) {
    std::string lexema;
    lexema += c;

    while (!isAtEnd() && isIdentifierPart(peek())) {
        lexema += advance();
    }

    // Convertir a mayúsculas para comparar
    std::string upper = lexema;
    for (auto &ch : upper) ch = std::toupper(static_cast<unsigned char>(ch));

    // Palabras reservadas
    if (upper == "TABLERO") return addToken(Token(tokenCounter++, lexema, TokenType::TABLERO, line, column - lexema.size()));
    if (upper == "COLUMNA") return addToken(Token(tokenCounter++, lexema, TokenType::COLUMNA, line, column - lexema.size()));
    if (upper == "TAREA") return addToken(Token(tokenCounter++, lexema, TokenType::TAREA, line, column - lexema.size()));
    if (upper == "PRIORIDAD") return addToken(Token(tokenCounter++, lexema, TokenType::PRIORIDAD, line, column - lexema.size()));
    if (upper == "RESPONSABLE") return addToken(Token(tokenCounter++, lexema, TokenType::RESPONSABLE, line, column - lexema.size()));
    if (upper == "FECHA_LIMITE") return addToken(Token(tokenCounter++, lexema, TokenType::FECHA_LIMITE, line, column - lexema.size()));

    // Prioridades
    if (upper == "ALTA") return addToken(Token(tokenCounter++, lexema, TokenType::ALTA, line, column - lexema.size()));
    if (upper == "MEDIA") return addToken(Token(tokenCounter++, lexema, TokenType::MEDIA, line, column - lexema.size()));
    if (upper == "BAJA") return addToken(Token(tokenCounter++, lexema, TokenType::BAJA, line, column - lexema.size()));

    // Si no coincide con ninguna palabra reservada → CADENA
    return addToken(Token(tokenCounter++, lexema, TokenType::CADENA, line, column - lexema.size()));
}
    

    // 5. Cadenas
    if (c == '"') {
    std::string lexema = "\"";
    int startColumn = column - 1;

    while (!isAtEnd()) {
        char ch = advance();
        lexema += ch;

        if (ch == '"') {
            // Cadena cerrada correctamente
            return addToken(Token(tokenCounter++, lexema, TokenType::CADENA, line, startColumn));
        }

        if (ch == '\n') {
            errorManager->addLexicalError(lexema, "Cadena no cerrada antes del salto de línea", line, startColumn);
            return Token(tokenCounter++, lexema, TokenType::ERROR, line, startColumn);
        }
    }

    // Fin de archivo sin cerrar cadena
    errorManager->addLexicalError(lexema, "Cadena no cerrada antes del fin del archivo", line, startColumn);
    return addToken(Token(tokenCounter++, lexema, TokenType::ERROR, line, startColumn));
}

    // 6. Números (enteros o fechas)
    if (std::isdigit(c)) {
    std::string lexema;
    lexema += c;
    int startColumn = column - 1;

    // Leer todos los dígitos iniciales
    while (!isAtEnd() && std::isdigit(peek())) {
        lexema += advance();
    }

    // ¿Es una fecha?
    if (!isAtEnd() && peek() == '-') {
        lexema += advance(); // primer guion

        // Leer mes
        if (std::isdigit(peek())) lexema += advance();
        else goto fecha_invalida;

        if (std::isdigit(peek())) lexema += advance();
        else goto fecha_invalida;

        if (peek() != '-') goto fecha_invalida;
        lexema += advance();

        // Leer día
        if (std::isdigit(peek())) lexema += advance();
        else goto fecha_invalida;

        if (std::isdigit(peek())) lexema += advance();
        else goto fecha_invalida;

        // Fecha válida
        return addToken(Token(tokenCounter++, lexema, TokenType::FECHA, line, startColumn));

fecha_invalida:
        errorManager->addLexicalError(lexema, "Formato de fecha inválido, se esperaba AAAA-MM-DD", line, startColumn);
        return addToken(Token(tokenCounter++, lexema, TokenType::ERROR, line, startColumn));
    }

    // Si no es fecha → entero
    return addToken(Token(tokenCounter++, lexema, TokenType::ENTERO, line, startColumn));
}


    // 7. Error léxico
    std::string lex(1, c);
    errorManager->addLexicalError(lex, "Carácter no reconocido", line, column - 1);

    return addToken(Token(tokenCounter++, lex, TokenType::ERROR, line, column - 1));
}

    const std::vector<Token>& getTokens() const { return tokens; }
};
