#include "LexicalAnalyzer.h"
#include "ErrorManager.h"
#include "ReportGenerator.h"
#include "HTMLGenerator.h"
#include "GraphvizGenerator.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>

class HospitalSystem {
private:
    ErrorManager errMgr;
    ReportGenerator reportGen;
    std::string currentFile;
    std::vector<Token> tokens;
    
public:
    HospitalSystem() {}
    
    void mostrarMenu() {
        std::cout << std::string(80, '=') << std::endl;
        std::cout << "SISTEMA DE GESTIÓN HOSPITALARIA" << std::endl;
        std::cout << std::string(80, '=') << std::endl;
        std::cout << "1. Cargar archivo (.med)\n";
        std::cout << "2. Analizar lexico\n";
        std::cout << "3. Ver tokens\n";
        std::cout << "4. Ver errores\n";
        std::cout << "\n--- REPORTES HTML ---\n";
        std::cout << "5. Reporte 1: Historial de Pacientes\n";
        std::cout << "6. Reporte 2: Carga de Medicos por Especialidad\n";
        std::cout << "7. Reporte 3: Agenda de Citas (con Conflictos)\n";
        std::cout << "8. Reporte 4: Estadisticas Generales\n";
        std::cout << "9. Tabla de Errores Lexicos (HTML)\n";
        std::cout << "10. Generar Grafo (Graphviz)\n";
        std::cout << "11. Generar TODOS los reportes\n";
        std::cout << "12. Ver Reportes en Consola\n";
        std::cout << "0. Salir\n";
        std::cout << std::string(80, '=') << std::endl;
    }
    
    void cargarArchivo() {
        std::cout << "\nNombre del archivo (.med): ";
        std::string filename;
        std::getline(std::cin, filename);
        
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "[ERROR] No se pudo abrir: " << filename << std::endl;
            return;
        }
        
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        
        currentFile = filename;
        errMgr.clear();
        tokens.clear();
        
        LexicalAnalyzer lexer(content, &errMgr);
        lexer.tokenize();
        tokens = lexer.getTokens();
        
        std::cout << "\n[] Archivo cargado: " << filename << std::endl;
        std::cout << "[] Tokens generados: " << tokens.size() << std::endl;
    }
    
    void analizarLexico() {
        if (tokens.empty()) {
            std::cout << "\n[ERROR] Primero carga un archivo (opción 1)\n";
            return;
        }
        
        reportGen.procesarTokens(tokens);
        std::cout << "\n[] Analisis completado\n";
        std::cout << "[] Datos extraídos:\n";
        
        auto& data = reportGen.getDatos();
        std::cout << "    - Pacientes: " << data.totalPacientes() << "\n";
        std::cout << "    - Medicos: " << data.totalMedicos() << "\n";
        std::cout << "    - Citas: " << data.totalCitas() << "\n";
        std::cout << "    - Diagnosticos: " << data.diagnosticos.size() << "\n";
    }
    
    void verTokens() {
        if (tokens.empty()) {
            std::cout << "\n[ERROR] No hay tokens. Carga un archivo primero.\n";
            return;
        }
        
        std::cout << "\n" << std::string(80, '=') << std::endl;
        std::cout << "TOKENS (" << tokens.size() << " total)" << std::endl;
        std::cout << std::string(80, '=') << std::endl;
        
        std::cout << std::left << std::setw(12) << "#"
                  << std::setw(15) << "Type"
                  << std::setw(30) << "Lexeme"
                  << "Location" << std::endl;
        std::cout << std::string(80, '-') << std::endl;
        
        for (size_t i = 0; i < std::min(tokens.size(), size_t(50)); ++i) {
            const auto& tok = tokens[i];
            std::string typeName = tok.toString().substr(1, tok.toString().find(']') - 1);
            std::string lex = tok.lexeme;
            if (lex.length() > 28) lex = lex.substr(0, 25) + "...";
            
            std::cout << std::left << std::setw(12) << (i + 1)
                      << std::setw(15) << typeName
                      << std::setw(30) << ("'" + lex + "'")
                      << "(L" << tok.line << ":C" << tok.column << ")" << std::endl;
        }
        
        if (tokens.size() > 50) {
            std::cout << "\n... y " << (tokens.size() - 50) << " tokens mas\n";
        }
    }
    
    void verErrores() {
        if (!errMgr.hasErrors()) {
            std::cout << "\n[] No hay errores\n";
            return;
        }
        
        errMgr.printErrors();
    }
    
    void generarReportePacientes() {
        if (reportGen.getDatos().totalPacientes() == 0) {
            std::cout << "\n[ERROR] Primero analiza un archivo (opcion 2)\n";
            return;
        }
        
        HTMLGenerator html(reportGen.getDatos(), &errMgr);
        if (html.generarReportePacientes("reporte_1_pacientes.html")) {
            std::cout << "\n[] Reporte 1 generado: reporte_1_pacientes.html\n";
        } else {
            std::cout << "\n[ERROR] No se pudo generar el reporte\n";
        }
    }
    
    void generarReporteMedicos() {
        if (reportGen.getDatos().totalMedicos() == 0) {
            std::cout << "\n[ERROR] Primero analiza un archivo (opcion 2)\n";
            return;
        }
        
        HTMLGenerator html(reportGen.getDatos(), &errMgr);
        if (html.generarReporteMedicos("reporte_2_medicos.html")) {
            std::cout << "\n[] Reporte 2 generado: reporte_2_medicos.html\n";
        } else {
            std::cout << "\n[ERROR] No se pudo generar el reporte\n";
        }
    }
    
    void generarReporteCitas() {
        if (reportGen.getDatos().totalCitas() == 0) {
            std::cout << "\n[ERROR] Primero analiza un archivo (opcion 2)\n";
            return;
        }
        
        HTMLGenerator html(reportGen.getDatos(), &errMgr);
        if (html.generarReporteCitas("reporte_3_citas.html")) {
            std::cout << "\n[] Reporte 3 generado: reporte_3_citas.html\n";
        } else {
            std::cout << "\n[ERROR] No se pudo generar el reporte\n";
        }
    }
    
    void generarEstadisticas() {
        if (reportGen.getDatos().totalPacientes() == 0) {
            std::cout << "\n[ERROR] Primero analiza un archivo (opcion 2)\n";
            return;
        }
        
        HTMLGenerator html(reportGen.getDatos(), &errMgr);
        if (html.generarReporteEstadisticas("reporte_4_estadisticas.html")) {
            std::cout << "\n[] Reporte 4 generado: reporte_4_estadisticas.html\n";
        } else {
            std::cout << "\n[ERROR] No se pudo generar el reporte\n";
        }
    }
    
    void generarReporteErrores() {
        HTMLGenerator html(reportGen.getDatos(), &errMgr);
        if (html.generarReporteErrores("reporte_errores.html")) {
            std::cout << "\n[] Tabla de errores generada: reporte_errores.html\n";
        } else {
            std::cout << "\n[ERROR] No se pudo generar el reporte de errores\n";
        }
    }
    
    void generarGrafo() {
        if (reportGen.getDatos().totalPacientes() == 0) {
            std::cout << "\n[ERROR] Primero analiza un archivo (opcion 2)\n";
            return;
        }
        
        GraphvizGenerator gviz(reportGen.getDatos());
        if (gviz.generarGrafo("hospital_grafo.dot")) {
            std::cout << "\n[] Grafo generado: hospital_grafo.dot\n";
            std::cout << "\nPara visualizar:\n";
            std::cout << "  dot -Tpng hospital_grafo.dot -o hospital_grafo.png\n";
            std::cout << "  dot -Tsvg hospital_grafo.dot -o hospital_grafo.svg\n";
        } else {
            std::cout << "\n[ERROR] No se pudo generar el grafo\n";
        }
    }
    
    void generarTodos() {
        std::cout << "\n[*] Generando todos los reportes...\n";
        generarReportePacientes();
        generarReporteMedicos();
        generarReporteCitas();
        generarEstadisticas();
        generarReporteErrores();
        generarGrafo();
        std::cout << "\n[] Todos los reportes han sido generados\n";
    }
    
    void verReportesConsola() {
        if (reportGen.getDatos().totalPacientes() == 0) {
            std::cout << "\n[ERROR] Primero analiza un archivo (opcion 2)\n";
            return;
        }
        
        std::cout << "\n" << reportGen.generarReportePacientes();
        std::cout << "\n" << reportGen.generarReporteMedicos();
        std::cout << "\n" << reportGen.generarReporteCitas();
        std::cout << "\n" << reportGen.generarReporteEstadisticas();
    }
    
    void ejecutar() {
        std::string opcion;
        
        while (true) {
            mostrarMenu();
            std::cout << "\nOpcion: ";
            std::getline(std::cin, opcion);
            
            if (opcion == "1") cargarArchivo();
            else if (opcion == "2") analizarLexico();
            else if (opcion == "3") verTokens();
            else if (opcion == "4") verErrores();
            else if (opcion == "5") generarReportePacientes();
            else if (opcion == "6") generarReporteMedicos();
            else if (opcion == "7") generarReporteCitas();
            else if (opcion == "8") generarEstadisticas();
            else if (opcion == "9") generarReporteErrores();
            else if (opcion == "10") generarGrafo();
            else if (opcion == "11") generarTodos();
            else if (opcion == "12") verReportesConsola();
            else if (opcion == "0") {
                std::cout << "\n[] Terminando programa\n";
                break;
            }
            else {
                std::cout << "\n[ERROR] Opción inválida\n";
            }
            
            std::cout << "\nPresiona Enter para continuar...";
            std::getline(std::cin, opcion);
        }
    }
};

int main() {
    HospitalSystem sistema;
    sistema.ejecutar();
    return 0;
}
