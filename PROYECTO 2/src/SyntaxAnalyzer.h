#pragma once
#include "LexicalAnalyzer.h"
#include "ErrorManager.h"
#include "BoardModel.h"
#include "TreeNode.h"

class SyntaxAnalyzer {
private:
    LexicalAnalyzer* lexer;
    ErrorManager* errorManager;

    Token currentToken;

    void advance();
    bool match(TokenType expected);
    void syntaxError(const std::string& expected);

    // Reglas de la gramática
    void programa();
    void columnas(TreeNode* parent);
    void columna(TreeNode* parent);
    void tareas(TreeNode* parent);
    void tarea(TreeNode* parent);
    void atributos(TreeNode* parent);
    void atributo(TreeNode* parent);
    void prioridad(TreeNode* parent);

    // Árbol de derivación
    TreeNode* createNode(const std::string& label, bool isTerminal);
    void addChild(TreeNode* parent, TreeNode* child);
    void exportTree(TreeNode* node, std::ofstream& out);

public:
    SyntaxAnalyzer(LexicalAnalyzer* lexer, ErrorManager* errorManager);

    void parse();

    Board board; // ← el modelo final
    Column currentColumn;
    Task currentTask;

    TreeNode* root;
    int nodeCounter;

    const Board& getBoard() const { return board; }
};
