#include "LexicalAnalyzer.h"
#include "ErrorManager.h"
#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::string filename = "test.med"; // assume file exists
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return 1;
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    ErrorManager errMgr;
    LexicalAnalyzer lexer(content, &errMgr);

    lexer.tokenize();

    std::cout << "Tokens:" << std::endl;
    lexer.printTokens();

    std::cout << "\nErrors:" << std::endl;
    errMgr.printErrors();

    return 0;
}