#include "MainWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "ErrorManager.h"
#include "ReportGenerator.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setupUI();
    setWindowTitle("TaskScript Analyzer");
    resize(1200, 800);
}

void MainWindow::setupUI() {
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    // Widgets
    editor = new QTextEdit(this);

    btnLoad = new QPushButton("Cargar archivo", this);
    btnAnalyze = new QPushButton("Analizar", this);
    btnReport1 = new QPushButton("Reporte Kanban", this);
    btnReport2 = new QPushButton("Reporte Responsables", this);
    btnReport3 = new QPushButton("Reporte Tokens/Errores", this);

    tokenTable = new QTableWidget(this);
    errorTable = new QTableWidget(this);

    setupTables();

    QTabWidget* tabs = new QTabWidget(this);
    tabs->addTab(tokenTable, "Tokens");
    tabs->addTab(errorTable, "Errores");

    // Layouts
    QHBoxLayout* topButtons = new QHBoxLayout();
    topButtons->addWidget(btnLoad);
    topButtons->addWidget(btnAnalyze);
    topButtons->addWidget(btnReport1);
    topButtons->addWidget(btnReport2);
    topButtons->addWidget(btnReport3);

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addWidget(editor, 2);
    mainLayout->addWidget(tabs, 1);

    QVBoxLayout* layout = new QVBoxLayout(central);
    layout->addLayout(topButtons);
    layout->addLayout(mainLayout);

    // Conexiones
    connect(btnLoad, &QPushButton::clicked, this, &MainWindow::loadFile);
    connect(btnAnalyze, &QPushButton::clicked, this, &MainWindow::analyze);
    connect(btnReport1, &QPushButton::clicked, this, &MainWindow::openReport1);
    connect(btnReport2, &QPushButton::clicked, this, &MainWindow::openReport2);
    connect(btnReport3, &QPushButton::clicked, this, &MainWindow::openReport3);
}

void MainWindow::setupTables() {
    tokenTable->setColumnCount(5);
    tokenTable->setHorizontalHeaderLabels({"No.", "Lexema", "Tipo", "Línea", "Columna"});

    errorTable->setColumnCount(7);
    errorTable->setHorizontalHeaderLabels({"No.", "Lexema", "Tipo", "Descripción", "Línea", "Columna", "Gravedad"});
}

void MainWindow::loadFile() {
    QString path = QFileDialog::getOpenFileName(this, "Abrir archivo", "", "TaskScript (*.task)");
    if (path.isEmpty()) return;

    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        editor->setText(file.readAll());
        file.close();
    }
}

void MainWindow::analyze() {
    QString text = editor->toPlainText();
    std::string input = text.toStdString();

    ErrorManager errors;
    LexicalAnalyzer lexer(input, &errors);
    SyntaxAnalyzer parser(&lexer, &errors);

    parser.parse();

    // Llenar tablas
    const auto& tokens = parser.getTokens();
    tokenTable->setRowCount(tokens.size());
    for (size_t i = 0; i < tokens.size(); ++i) {
        const Token& t = tokens[i];
        tokenTable->setItem(i, 0, new QTableWidgetItem(QString::number(t.getNumber())));
        tokenTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(t.getLexeme())));
        tokenTable->setItem(i, 2, new QTableWidgetItem(QString::number((int)t.getType())));
        tokenTable->setItem(i, 3, new QTableWidgetItem(QString::number(t.getLine())));
        tokenTable->setItem(i, 4, new QTableWidgetItem(QString::number(t.getColumn())));
    }

    const auto& errorList = parser.getErrors();
    errorTable->setRowCount(errorList.size());
    for (size_t i = 0; i < errorList.size(); ++i) {
        const ErrorInfo& e = errorList[i];
        errorTable->setItem(i, 0, new QTableWidgetItem(QString::number(e.number)));
        errorTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(e.lexeme)));
        errorTable->setItem(i, 2, new QTableWidgetItem(e.type == ErrorType::LEXICO ? "Léxico" : "Sintáctico"));
        errorTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(e.description)));
        errorTable->setItem(i, 4, new QTableWidgetItem(QString::number(e.line)));
        errorTable->setItem(i, 5, new QTableWidgetItem(QString::number(e.column)));
        errorTable->setItem(i, 6, new QTableWidgetItem(e.severity == ErrorSeverity::ERROR ? "ERROR" : "CRITICO"));
    }

    // Generar reportes si no hay errores
    if (!errors.hasErrors()) {
        ReportGenerator rep(parser.getBoard());
        rep.generateKanbanReport("reporte_kanban.html");
        rep.generateResponsableReport("reporte_responsables.html");
        rep.generateTokenErrorReport("reporte_tokens.html", tokens, errorList);
        QMessageBox::information(this, "Éxito", "Análisis completado y reportes generados.");
    } else {
        QMessageBox::warning(this, "Errores", "El archivo contiene errores. Revise la tabla de errores.");
    }
}

void MainWindow::openReport1() {
    QDesktopServices::openUrl(QUrl::fromLocalFile("reporte_kanban.html"));
}

void MainWindow::openReport2() {
    QDesktopServices::openUrl(QUrl::fromLocalFile("reporte_responsables.html"));
}

void MainWindow::openReport3() {
    QDesktopServices::openUrl(QUrl::fromLocalFile("reporte_tokens.html"));
}
