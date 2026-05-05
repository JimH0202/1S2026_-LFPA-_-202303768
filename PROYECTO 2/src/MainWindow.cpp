#include "MainWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDesktopServices>
#include <QHeaderView>
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
    tokenTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tokenTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tokenTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    tokenTable->setAlternatingRowColors(true);
    tokenTable->verticalHeader()->setVisible(false);
    tokenTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    errorTable->setColumnCount(7);
    errorTable->setHorizontalHeaderLabels({"No.", "Lexema", "Tipo", "Descripción", "Línea", "Columna", "Gravedad"});
    errorTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    errorTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    errorTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    errorTable->setAlternatingRowColors(true);
    errorTable->verticalHeader()->setVisible(false);
    errorTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
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

    // Limpiar tablas antes de llenarlas
    tokenTable->clearContents();
    errorTable->clearContents();

    // Llenar tablas
    const auto& tokens = lexer.getTokens();
    tokenTable->setRowCount(tokens.size());
    for (size_t i = 0; i < tokens.size(); ++i) {
        const Token& t = tokens[i];
        auto* item0 = new QTableWidgetItem(QString::number(t.getNumber()));
        item0->setTextAlignment(Qt::AlignCenter);
        tokenTable->setItem(i, 0, item0);

        auto* item1 = new QTableWidgetItem(QString::fromStdString(t.getLexeme()));
        item1->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        tokenTable->setItem(i, 1, item1);

        auto* item2 = new QTableWidgetItem(QString::number((int)t.getType()));
        item2->setTextAlignment(Qt::AlignCenter);
        tokenTable->setItem(i, 2, item2);

        auto* item3 = new QTableWidgetItem(QString::number(t.getLine()));
        item3->setTextAlignment(Qt::AlignCenter);
        tokenTable->setItem(i, 3, item3);

        auto* item4 = new QTableWidgetItem(QString::number(t.getColumn()));
        item4->setTextAlignment(Qt::AlignCenter);
        tokenTable->setItem(i, 4, item4);
    }
    tokenTable->resizeRowsToContents();

    const auto& errorList = errors.getErrors();
    errorTable->setRowCount(errorList.size());
    for (size_t i = 0; i < errorList.size(); ++i) {
        const ErrorInfo& e = errorList[i];
        auto* item0 = new QTableWidgetItem(QString::number(e.number));
        item0->setTextAlignment(Qt::AlignCenter);
        errorTable->setItem(i, 0, item0);

        auto* item1 = new QTableWidgetItem(QString::fromStdString(e.lexeme));
        item1->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        errorTable->setItem(i, 1, item1);

        auto* item2 = new QTableWidgetItem(e.type == ErrorType::LEXICO ? "Léxico" : "Sintáctico");
        item2->setTextAlignment(Qt::AlignCenter);
        errorTable->setItem(i, 2, item2);

        auto* item3 = new QTableWidgetItem(QString::fromStdString(e.description));
        item3->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        errorTable->setItem(i, 3, item3);

        auto* item4 = new QTableWidgetItem(QString::number(e.line));
        item4->setTextAlignment(Qt::AlignCenter);
        errorTable->setItem(i, 4, item4);

        auto* item5 = new QTableWidgetItem(QString::number(e.column));
        item5->setTextAlignment(Qt::AlignCenter);
        errorTable->setItem(i, 5, item5);

        auto* item6 = new QTableWidgetItem(e.severity == ErrorSeverity::ERROR ? "ERROR" : "CRITICO");
        item6->setTextAlignment(Qt::AlignCenter);
        errorTable->setItem(i, 6, item6);
    }
    errorTable->resizeRowsToContents();

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
