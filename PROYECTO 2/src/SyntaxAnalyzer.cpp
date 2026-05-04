#include "SyntaxAnalyzer.h"
#include <fstream>

SyntaxAnalyzer::SyntaxAnalyzer(LexicalAnalyzer* lexer, ErrorManager* errorManager)
    : lexer(lexer), errorManager(errorManager), board(), currentColumn(), currentTask(), root(nullptr), nodeCounter(1), tokenIndex(0) {
    // Tokenizar todo el input
    Token t;
    do {
        t = lexer->nextToken();
        tokens.push_back(t);
    } while (t.getType() != TokenType::END_OF_FILE);

    currentToken = tokens[tokenIndex];
}

void SyntaxAnalyzer::parse() {
    programa();

    std::ofstream out("arbol.dot");
    out << "digraph G {\n";
    out << "  node [shape=box];\n";

    exportTree(root, out);

    out << "}\n";
    out.close();
}

void SyntaxAnalyzer::advance() {
    tokenIndex++;
    if (tokenIndex < tokens.size()) {
        currentToken = tokens[tokenIndex];
    }
}

bool SyntaxAnalyzer::match(TokenType expected) {
    if (currentToken.getType() == expected) {
        advance();
        return true;
    }

    syntaxError("Se esperaba token " + std::to_string((int)expected));
    return false;
}

void SyntaxAnalyzer::syntaxError(const std::string& expected) {
    errorManager->addSyntaxError(
        currentToken.getLexeme(),
        expected,
        currentToken.getLine(),
        currentToken.getColumn()
    );

    while (currentToken.getType() != TokenType::PUNTO_Y_COMA &&
           currentToken.getType() != TokenType::LLAVE_CIERRA &&
           currentToken.getType() != TokenType::END_OF_FILE) {
        advance();
    }
}

// Árbol de derivación
TreeNode* SyntaxAnalyzer::createNode(const std::string& label, bool isTerminal) {
    TreeNode* node = new TreeNode();
    node->id = nodeCounter++;
    node->label = label;
    node->isTerminal = isTerminal;
    return node;
}

void SyntaxAnalyzer::addChild(TreeNode* parent, TreeNode* child) {
    parent->children.push_back(child);
}

void SyntaxAnalyzer::exportTree(TreeNode* node, std::ofstream& out) {
    if (!node) return;

    // Color según tipo
    std::string color = node->isTerminal ? "lightblue" : "lightgreen";

    out << "  node" << node->id 
        << " [label=\"" << node->label 
        << "\", style=filled, fillcolor=" << color << "];\n";

    for (TreeNode* child : node->children) {
        out << "  node" << node->id << " -> node" << child->id << ";\n";
        exportTree(child, out);
    }
}

// <programa>       ::= TABLERO CADENA "{" <columnas> "}" ";"
// <columnas>       ::= <columna> <columnas> | <columna>
// <columna>        ::= COLUMNA CADENA "{" <tareas> "}" ";"
// <tareas>         ::= <tarea> "," <tareas> | <tarea>
// <tarea>          ::= TAREA ":" CADENA "[" <atributos> "]"
// <atributos>      ::= <atributo> "," <atributos> | <atributo>
// <atributo>       ::= PRIORIDAD ":" <prioridad>
//                    | RESPONSABLE ":" CADENA
//                    | FECHA_LIMITE ":" FECHA
// <prioridad>      ::= ALTA | MEDIA | BAJA

void SyntaxAnalyzer::programa() {
    TreeNode* node = createNode("<programa>", false);
    root = node;

    TreeNode* t1 = createNode("TABLERO", true);
    addChild(node, t1);
    match(TokenType::TABLERO);

    board = Board();
    board.name = currentToken.getLexeme();
    TreeNode* t2 = createNode("CADENA", true);
    addChild(node, t2);
    match(TokenType::CADENA);

    TreeNode* t3 = createNode("{", true);
    addChild(node, t3);
    match(TokenType::LLAVE_ABRE);

    TreeNode* cols = createNode("<columnas>", false);
    addChild(node, cols);
    columnas(cols);

    TreeNode* t4 = createNode("}", true);
    addChild(node, t4);
    match(TokenType::LLAVE_CIERRA);

    TreeNode* t5 = createNode(";", true);
    addChild(node, t5);
    match(TokenType::PUNTO_Y_COMA);
}

void SyntaxAnalyzer::columnas(TreeNode* parent) {
    TreeNode* node = createNode("<columnas>", false);
    addChild(parent, node);

    columna(node);

    while (currentToken.getType() == TokenType::COLUMNA) {
        columna(node);
    }
}

void SyntaxAnalyzer::columna(TreeNode* parent) {
    TreeNode* node = createNode("<columna>", false);
    addChild(parent, node);

    TreeNode* t1 = createNode("COLUMNA", true);
    addChild(node, t1);
    match(TokenType::COLUMNA);

    currentColumn = Column();
    currentColumn.name = currentToken.getLexeme();

    TreeNode* t2 = createNode("CADENA", true);
    addChild(node, t2);
    match(TokenType::CADENA);

    TreeNode* t3 = createNode("{", true);
    addChild(node, t3);
    match(TokenType::LLAVE_ABRE);

    TreeNode* tasks = createNode("<tareas>", false);
    addChild(node, tasks);
    tareas(tasks);

    TreeNode* t4 = createNode("}", true);
    addChild(node, t4);
    match(TokenType::LLAVE_CIERRA);

    TreeNode* t5 = createNode(";", true);
    addChild(node, t5);
    match(TokenType::PUNTO_Y_COMA);

    board.columns.push_back(currentColumn);
}

void SyntaxAnalyzer::tareas(TreeNode* parent) {
    TreeNode* node = createNode("<tareas>", false);
    addChild(parent, node);

    tarea(node);

    while (currentToken.getType() == TokenType::COMA) {
        TreeNode* t1 = createNode(",", true);
        addChild(node, t1);
        match(TokenType::COMA);
        tarea(node);
    }
}

void SyntaxAnalyzer::tarea(TreeNode* parent) {
    TreeNode* node = createNode("<tarea>", false);
    addChild(parent, node);

    TreeNode* t1 = createNode("TAREA", true);
    addChild(node, t1);
    match(TokenType::TAREA);

    TreeNode* t2 = createNode(":", true);
    addChild(node, t2);
    match(TokenType::DOS_PUNTOS);

    currentTask = Task();
    currentTask.name = currentToken.getLexeme();

    TreeNode* t3 = createNode("CADENA", true);
    addChild(node, t3);
    match(TokenType::CADENA);

    TreeNode* t4 = createNode("[", true);
    addChild(node, t4);
    match(TokenType::CORCHETE_ABRE);

    TreeNode* attrs = createNode("<atributos>", false);
    addChild(node, attrs);
    atributos(attrs);

    TreeNode* t5 = createNode("]", true);
    addChild(node, t5);
    match(TokenType::CORCHETE_CIERRA);

    currentColumn.tasks.push_back(currentTask);
}

void SyntaxAnalyzer::atributos(TreeNode* parent) {
    TreeNode* node = createNode("<atributos>", false);
    addChild(parent, node);

    atributo(node);

    while (currentToken.getType() == TokenType::COMA) {
        TreeNode* t1 = createNode(",", true);
        addChild(node, t1);
        match(TokenType::COMA);
        atributo(node);
    }
}

void SyntaxAnalyzer::atributo(TreeNode* parent) {
    TreeNode* node = createNode("<atributo>", false);
    addChild(parent, node);

    if (currentToken.getType() == TokenType::PRIORIDAD) {
        TreeNode* t1 = createNode("PRIORIDAD", true);
        addChild(node, t1);
        match(TokenType::PRIORIDAD);

        TreeNode* t2 = createNode(":", true);
        addChild(node, t2);
        match(TokenType::DOS_PUNTOS);

        TreeNode* pri = createNode("<prioridad>", false);
        addChild(node, pri);
        prioridad(pri);
        return;
    }

    if (currentToken.getType() == TokenType::RESPONSABLE) {
        TreeNode* t1 = createNode("RESPONSABLE", true);
        addChild(node, t1);
        match(TokenType::RESPONSABLE);

        TreeNode* t2 = createNode(":", true);
        addChild(node, t2);
        match(TokenType::DOS_PUNTOS);

        if (currentToken.getType() == TokenType::CADENA) {
            currentTask.responsible = currentToken.getLexeme();
        }

        TreeNode* t3 = createNode("CADENA", true);
        addChild(node, t3);
        match(TokenType::CADENA);
        return;
    }

    if (currentToken.getType() == TokenType::FECHA_LIMITE) {
        TreeNode* t1 = createNode("FECHA_LIMITE", true);
        addChild(node, t1);
        match(TokenType::FECHA_LIMITE);

        TreeNode* t2 = createNode(":", true);
        addChild(node, t2);
        match(TokenType::DOS_PUNTOS);

        if (currentToken.getType() == TokenType::FECHA) {
            currentTask.deadline = currentToken.getLexeme();
        }

        TreeNode* t3 = createNode("FECHA", true);
        addChild(node, t3);
        match(TokenType::FECHA);
        return;
    }

    syntaxError("Se esperaba un atributo válido");
    advance();
}

void SyntaxAnalyzer::prioridad(TreeNode* parent) {
    TreeNode* node = createNode("<prioridad>", false);
    addChild(parent, node);

    if (currentToken.getType() == TokenType::ALTA) {
        TreeNode* t1 = createNode("ALTA", true);
        addChild(node, t1);
        currentTask.priority = currentToken.getLexeme();
        advance();
    } else if (currentToken.getType() == TokenType::MEDIA) {
        TreeNode* t1 = createNode("MEDIA", true);
        addChild(node, t1);
        currentTask.priority = currentToken.getLexeme();
        advance();
    } else if (currentToken.getType() == TokenType::BAJA) {
        TreeNode* t1 = createNode("BAJA", true);
        addChild(node, t1);
        currentTask.priority = currentToken.getLexeme();
        advance();
    } else {
        syntaxError("Se esperaba ALTA, MEDIA o BAJA");
        advance();
    }
}
