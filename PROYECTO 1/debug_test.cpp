#include "src/LexicalAnalyzer.h"
#include "src/ReportGenerator.h"
#include "src/ErrorManager.h"
#include <fstream>
#include <iostream>

int main() {
    // Leer el archivo de prueba
    std::ifstream file("tests/test_caso_1_basico.med");
    if (!file.is_open()) {
        std::cerr << "[ERROR] No se pudo abrir el archivo\n";
        return 1;
    }
    
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    
    // Crear analizador léxico
    ErrorManager errMgr;
    LexicalAnalyzer lexer(content, &errMgr);
    lexer.tokenize();
    
    auto tokens = lexer.getTokens();
    
    std::cout << "=== TOKENS ===\n";
    std::cout << "Total tokens: " << tokens.size() << "\n\n";
    
    // Mostrar todos los tokens
    for (size_t i = 0; i < tokens.size(); i++) {
        const auto& tok = tokens[i];
        std::cout << "[" << i << "] Type: " << static_cast<int>(tok.type) 
                  << " | Lexeme: '" << tok.lexeme << "'\n";
    }
    
    std::cout << "\n=== DEBUG: BUSCANDO MEDICOS ===\n";
    
    // Buscar tokens MEDICOS
    for (size_t i = 0; i < tokens.size(); i++) {
        if (tokens[i].type == TokenType::MEDICOS) {
            std::cout << "[" << i << "] Encontrado token MEDICOS\n";
            
            // Mirar los siguientes tokens
            for (size_t j = i; j < std::min(i + 20, tokens.size()); j++) {
                std::cout << "  [" << j << "] Type:" << static_cast<int>(tokens[j].type) 
                          << " Lexeme:'" << tokens[j].lexeme << "'\n";
            }
            break;
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
