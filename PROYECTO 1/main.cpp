#include "LexicalAnalyzer.h"
#include "ErrorManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[ERROR] Cannot open file: " << filename << std::endl;
        return "";
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}

void printHeader() {
    std::cout << std::string(80, '=') << std::endl;
    std::cout << "FASE 2 - LEXICAL ANALYZER (Motor Léxico)" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
}

void printTokenTable(const std::vector<Token>& tokens) {
    if (tokens.empty()) {
        std::cout << "\n[INFO] No tokens generated." << std::endl;
        return;
    }
    
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "TOKENS GENERATED (" << tokens.size() << " total)" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    
    std::cout << std::left << std::setw(12) << "#"
              << std::setw(15) << "Type"
              << std::setw(30) << "Lexeme"
              << "Location" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    for (size_t i = 0; i < tokens.size(); ++i) {
        const auto& tok = tokens[i];
        std::stringstream typeName;
        std::string lex = tok.lexeme;
        if (lex.length() > 28) lex = lex.substr(0, 25) + "...";
        
        std::cout << std::left << std::setw(12) << (i + 1)
                  << std::setw(15) << tok.toString().substr(1, tok.toString().find(']') - 1)
                  << std::setw(30) << ("'" + lex + "'")
                  << "(L" << tok.line << ":C" << tok.column << ")" << std::endl;
    }
}

int main() {
    printHeader();
    
    std::string filename = "test.med";
    std::cout << "\n[*] Opening file: " << filename << std::endl;
    
    std::string content = readFile(filename);
    if (content.empty()) {
        std::cerr << "[ERROR] File is empty or cannot be read." << std::endl;
        return 1;
    }
    
    std::cout << "[+] File read successfully (" << content.length() << " characters)" << std::endl;
    
    ErrorManager errMgr;
    LexicalAnalyzer lexer(content, &errMgr);
    
    std::cout << "\n[*] Starting lexical analysis..." << std::endl;
    lexer.tokenize();
    
    const auto& tokens = lexer.getTokens();
    std::cout << "[+] Analysis complete!" << std::endl;
    
    // Print tokens
    printTokenTable(tokens);
    
    // Print errors
    std::cout << std::endl;
    if (errMgr.hasErrors()) {
        errMgr.printErrors();
    } else {
        std::cout << "\n" << std::string(80, '=') << std::endl;
        std::cout << "[SUCCESS] Lexical analysis completed without errors!" << std::endl;
        std::cout << std::string(80, '=') << std::endl;
    }
    
    std::cout << "\n[SUMMARY]" << std::endl;
    std::cout << "  Tokens Found: " << tokens.size() << std::endl;
    std::cout << "  Errors Found: " << errMgr.getErrors().size() << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    
    return 0;
}