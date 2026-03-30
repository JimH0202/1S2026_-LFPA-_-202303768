#include "LexicalAnalyzer.h"
#include "ErrorManager.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    std::string filename = (argc > 1) ? argv[1] : "test.med";
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[ERROR] Cannot open file: " << filename << std::endl;
        return 1;
    }
    
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    
    std::cout << std::string(80, '=') << std::endl;
    std::cout << "LEXICAL ANALYZER - FASE 2" << std::endl;
    std::cout << "File: " << filename << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    
    ErrorManager errMgr;
    LexicalAnalyzer lexer(content, &errMgr);
    lexer.tokenize();
    
    const auto& tokens = lexer.getTokens();
    
    std::cout << "\n[RESULT] " << tokens.size() << " tokens generated\n" << std::endl;
    
    if (errMgr.hasErrors()) {
        errMgr.printErrors();
    } else {
        std::cout << "[SUCCESS] No errors found!\n" << std::endl;
    }
    
    return 0;
}
