#include <fstream>
#include <iostream>
#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "ErrorManager.h"
#include "ReportGenerator.h"

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

    // Generar reporte Kanban
    ReportGenerator reportGen(parser.getBoard());
    reportGen.generateKanbanReport("kanban_report.html");
    std::cout << "Reporte Kanban generado en 'kanban_report.html'" << std::endl;

    // Generar reporte por responsable
    reportGen.generateResponsableReport("responsable_report.html");
    std::cout << "Reporte por Responsable generado en 'responsable_report.html'" << std::endl;

    return 0;
}