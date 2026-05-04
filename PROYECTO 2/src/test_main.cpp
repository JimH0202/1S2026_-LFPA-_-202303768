#include <fstream>
#include <iostream>
#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "ErrorManager.h"

int main() {
    // Prueba del análisis sintáctico y generación del árbol
    std::ifstream inputFile("../test_input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "No se pudo abrir el archivo de entrada." << std::endl;
        return 1;
    }

    std::string input((std::istreambuf_iterator<char>(inputFile)),
                      std::istreambuf_iterator<char>());
    inputFile.close();

    ErrorManager errorManager;
    LexicalAnalyzer lexer(input, &errorManager);
    SyntaxAnalyzer parser(&lexer, &errorManager);

    parser.parse();

    std::cout << "Análisis completado. Árbol generado en 'arbol.dot'" << std::endl;

    return 0;
}