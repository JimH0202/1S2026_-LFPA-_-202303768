#include "src/LexicalAnalyzer.h"
#include "src/ReportGenerator.h"
#include "src/ErrorManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>

int main() {
    // Cargar test 2
    std::ifstream file("tests/test_caso_2_multiples.med");
    if (!file.is_open()) {
        std::cerr << "[ERROR] No se pudo abrir test_caso_10_hospital_grande.med\n";
        return 1;
    }
    
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    
    // Análisis léxico
    ErrorManager errMgr;
    LexicalAnalyzer lexer(content, &errMgr);
    lexer.tokenize();
    std::vector<Token> tokens = lexer.getTokens();
    
    std::cout << "=== TOKENS ===\n";
    std::cout << "Total tokens: " << tokens.size() << "\n\n";
    
    // Mostrar todos los tokens
    for (size_t i = 0; i < tokens.size(); i++) {
        const auto& tok = tokens[i];
        std::cout << "[" << i << "] Type: " << static_cast<int>(tok.type) 
                  << " | Lexeme: '" << tok.lexeme << "'\n";
    }
    
    std::cout << "\n=== PROCESAMIENTO MANUAL DE CITAS ===\n";
    
    // Buscar posición de CITAS
    int citasPos = -1;
    for (size_t i = 0; i < tokens.size(); i++) {
        if (tokens[i].type == TokenType::CITAS) {
            citasPos = i;
            break;
        }
    }
    
    if (citasPos != -1) {
        std::cout << "Token CITAS en posición: " << citasPos << "\n";
        std::cout << "\nAnalizando tokens 240-390:\n";
        for (int i = 240; i < 390 && i < tokens.size(); i++) {
            if (tokens[i].lexeme == "cita" || tokens[i].lexeme == "con" || 
                tokens[i].lexeme == "fecha" || tokens[i].lexeme == "hora" ||
                tokens[i].type == TokenType::STRING || tokens[i].type == TokenType::DATE || 
                tokens[i].type == TokenType::TIME) {
                std::cout << "[" << i << "] Type:" << static_cast<int>(tokens[i].type) 
                          << " Lexeme:'" << tokens[i].lexeme << "'\n";
            }
        }
    }
    
    std::cout << "\n=== PROCESAMIENTO ===\n";
    
    // Procesar tokens
    ReportGenerator reportGen;
    reportGen.procesarTokens(tokens);
    
    auto& data = reportGen.getDatos();
    std::cout << "Pacientes: " << data.totalPacientes() << "\n";
    std::cout << "Médicos: " << data.totalMedicos() << "\n";
    std::cout << "Citas: " << data.totalCitas() << "\n";
    std::cout << "Diagnósticos: " << data.diagnosticos.size() << "\n";
    
    // Mostrar detalles de médicos
    std::cout << "\n=== MEDICOS ENCONTRADOS ===\n";
    for (const auto& m : data.medicos) {
        std::cout << "- " << m.nombre << " (" << m.especialidad << ") [" << m.codigo << "]\n";
    }
    
    return 0;
}
