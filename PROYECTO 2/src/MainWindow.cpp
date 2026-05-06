#include "MainWindow.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QGroupBox>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDesktopServices>
#include <QHeaderView>
#include <QMenuBar>
#include <QUrl>
#include <QFont>
#include <QFileInfo>

#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "ErrorManager.h"
#include "ReportGenerator.h"

namespace {
QString tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::TABLERO: return "TABLERO";
        case TokenType::COLUMNA: return "COLUMNA";
        case TokenType::TAREA: return "TAREA";
        case TokenType::PRIORIDAD: return "PRIORIDAD";
        case TokenType::RESPONSABLE: return "RESPONSABLE";
        case TokenType::FECHA_LIMITE: return "FECHA_LÍMITE";
        case TokenType::ALTA: return "ALTA";
        case TokenType::MEDIA: return "MEDIA";
        case TokenType::BAJA: return "BAJA";
        case TokenType::CADENA: return "CADENA";
        case TokenType::ENTERO: return "ENTERO";
        case TokenType::FECHA: return "FECHA";
        case TokenType::LLAVE_ABRE: return "{";
        case TokenType::LLAVE_CIERRA: return "}";
        case TokenType::CORCHETE_ABRE: return "[";
        case TokenType::CORCHETE_CIERRA: return "]";
        case TokenType::DOS_PUNTOS: return ":";
        case TokenType::COMA: return ",";
        case TokenType::PUNTO_Y_COMA: return ";";
        case TokenType::END_OF_FILE: return "EOF";
        case TokenType::ERROR: return "ERROR";
    }
    return "DESCONOCIDO";
}
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setupUI();
    setupMenus();
    applyStyleSheet();

    setWindowTitle("TaskScript Analyzer");
    resize(1400, 900);

    updateStatus("Listo para analizar. Carga un archivo .task o pega tu contenido.");
}

void MainWindow::setupUI() {
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    editor = new QTextEdit(this);
    editor->setPlaceholderText("Pega aquí tu TaskScript o carga un archivo para comenzar...");
    editor->setFont(QFont("Consolas", 11));
    editor->setAcceptRichText(false);

    btnLoad = new QPushButton("Cargar archivo", this);
    btnAnalyze = new QPushButton("Analizar", this);
    btnReport1 = new QPushButton("Reporte Kanban", this);
    btnReport2 = new QPushButton("Reporte Responsables", this);
    btnReport3 = new QPushButton("Reporte Tokens/Errores", this);
    btnReport4 = new QPushButton("Árbol de Derivación", this);
    btnClear = new QPushButton("Limpiar", this);

    tokenTable = new QTableWidget(this);
    errorTable = new QTableWidget(this);

    setupTables();

    QTabWidget* tabs = new QTabWidget(this);
    tabs->addTab(tokenTable, "Tokens");
    tabs->addTab(errorTable, "Errores");

    QGroupBox* editorGroup = new QGroupBox("Editor TaskScript", this);
    QVBoxLayout* editorLayout = new QVBoxLayout(editorGroup);
    editorLayout->addWidget(editor);
    editorLayout->setContentsMargins(12, 12, 12, 12);

    QGroupBox* resultGroup = new QGroupBox("Resultados", this);
    QVBoxLayout* resultLayout = new QVBoxLayout(resultGroup);
    resultLayout->addWidget(tabs);
    resultLayout->setContentsMargins(12, 12, 12, 12);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(btnLoad);
    buttonLayout->addWidget(btnAnalyze);
    buttonLayout->addWidget(btnClear);
    buttonLayout->addStretch();
    buttonLayout->addWidget(btnReport1);
    buttonLayout->addWidget(btnReport2);
    buttonLayout->addWidget(btnReport3);
    buttonLayout->addWidget(btnReport4);
    buttonLayout->setSpacing(10);

    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(editorGroup);
    splitter->addWidget(resultGroup);
    splitter->setStretchFactor(0, 3);
    splitter->setStretchFactor(1, 2);
    splitter->setHandleWidth(4);

    QVBoxLayout* mainLayout = new QVBoxLayout(central);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(splitter);
    mainLayout->setContentsMargins(14, 14, 14, 14);
    mainLayout->setSpacing(14);

    statusLabel = new QLabel(this);
    statusLabel->setObjectName("statusLabel");
    statusBar()->addWidget(statusLabel, 1);

    connect(btnLoad, &QPushButton::clicked, this, &MainWindow::loadFile);
    connect(btnAnalyze, &QPushButton::clicked, this, &MainWindow::analyze);
    connect(btnClear, &QPushButton::clicked, this, &MainWindow::clearEditor);
    connect(btnReport1, &QPushButton::clicked, this, &MainWindow::openReport1);
    connect(btnReport2, &QPushButton::clicked, this, &MainWindow::openReport2);
    connect(btnReport3, &QPushButton::clicked, this, &MainWindow::openReport3);
    connect(btnReport4, &QPushButton::clicked, this, &MainWindow::openReport4);
}

void MainWindow::setupTables() {
    tokenTable->setColumnCount(5);
    tokenTable->setHorizontalHeaderLabels({"No.", "Lexema", "Tipo", "Línea", "Columna"});
    tokenTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tokenTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tokenTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    tokenTable->setAlternatingRowColors(true);
    tokenTable->verticalHeader()->setVisible(false);
    tokenTable->setMouseTracking(false);
    tokenTable->setCursor(Qt::ArrowCursor);
    tokenTable->setSelectionMode(QAbstractItemView::NoSelection);
    tokenTable->setFocusPolicy(Qt::NoFocus);
    tokenTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    errorTable->setColumnCount(7);
    errorTable->setAlternatingRowColors(true);
    errorTable->verticalHeader()->setVisible(false);
    errorTable->setMouseTracking(false);
    errorTable->setCursor(Qt::ArrowCursor);
    errorTable->setSelectionMode(QAbstractItemView::NoSelection);
    errorTable->setFocusPolicy(Qt::NoFocus);
    errorTable->setHorizontalHeaderLabels({"No.", "Lexema", "Tipo", "Descripción", "Línea", "Columna", "Gravedad"});
    errorTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    errorTable->setColumnWidth(0, 50);
    errorTable->setColumnWidth(1, 50);
    errorTable->setColumnWidth(2, 80);
    errorTable->setColumnWidth(3, 120);
    errorTable->setColumnWidth(4, 50);
    errorTable->setColumnWidth(5, 70);
    errorTable->setColumnWidth(6, 80);
    errorTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    errorTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    errorTable->setAlternatingRowColors(true);
    errorTable->verticalHeader()->setVisible(false);
    errorTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void MainWindow::setupMenus() {
    fileMenu = menuBar()->addMenu("&Archivo");

    actOpen = new QAction("Abrir archivo...", this);
    actExit = new QAction("Salir", this);

    fileMenu->addAction(actOpen);
    fileMenu->addSeparator();
    fileMenu->addAction(actExit);

    helpMenu = menuBar()->addMenu("&Ayuda");
    actAbout = new QAction("Acerca de", this);
    helpMenu->addAction(actAbout);

    connect(actOpen, &QAction::triggered, this, &MainWindow::loadFile);
    connect(actExit, &QAction::triggered, this, &MainWindow::close);
    connect(actAbout, &QAction::triggered, this, &MainWindow::showAbout);
}

void MainWindow::applyStyleSheet() {
    qApp->setStyle("Fusion");
    qApp->setStyleSheet(R"(
        QMainWindow {
            background-color: #f4f7fb;
        }
        QGroupBox {
            border: 1px solid #d4dae3;
            border-radius: 10px;
            margin-top: 10px;
            font-weight: 600;
            color: #2a3f5f;
            padding: 12px;
            background-color: white;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 14px;
            padding: 0 4px;
        }
        QPushButton {
            border: 1px solid #0078d7;
            border-radius: 8px;
            padding: 10px 16px;
            background-color: #0078d7;
            color: white;
            font-weight: 600;
        }
        QPushButton:hover {
            background-color: #005bb5;
        }
        QPushButton:pressed {
            background-color: #00468c;
        }
        QTextEdit {
            background-color: #ffffff;
            border: 1px solid #d4dae3;
            border-radius: 8px;
            padding: 10px;
            color: #24292f;
        }
        QTabWidget::pane {
            border: 1px solid #d4dae3;
            border-radius: 10px;
            background: #f9fbff;
        }
        QTabBar::tab {
            background: #e1eff9;
            border: 1px solid #d4dae3;
            border-bottom: none;
            padding: 10px 20px;
            border-top-left-radius: 10px;
            border-top-right-radius: 10px;
            margin-right: 4px;
            min-width: 130px;
            color: #1b2838;
        }
        QTabBar::tab:selected {
            background: #ffffff;
            color: #0078d7;
            border-bottom: 1px solid #ffffff;
        }
        QHeaderView::section {
            background-color: #0f4c81;
            padding: 10px;
            border: 1px solid #d4dae3;
            font-weight: 700;
            color: white;
        }
        QTableWidget {
            gridline-color: #e1e7ee;
            background-color: white;
            alternate-background-color: #f6f9ff;
        }
        QTableWidget::item,
        QTableView::item {
            padding: 8px;
            border: none;
            background-color: white;
            color: black;
        }
        QHeaderView::section:hover {
            background-color: #0f4c81 !important;
        }
        QToolTip {
            background-color: transparent !important;
            color: transparent !important;
            border: none !important;
        }
        QStatusBar {
            background-color: #ffffff;
            border-top: 1px solid #d4dae3;
            padding: 4px;
            color: #2a3f5f;
        }
    )");
}

void MainWindow::updateStatus(const QString& message) {
    if (statusLabel) {
        statusLabel->setText(message);
    }
}

void MainWindow::loadFile() {
    QString path = QFileDialog::getOpenFileName(this, "Abrir archivo", "", "TaskScript (*.task);;Texto (*.txt);;Todos los archivos (*.*)");
    if (path.isEmpty()) {
        return;
    }

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "No se pudo abrir el archivo seleccionado.");
        return;
    }

    editor->setText(file.readAll());
    file.close();
    updateStatus(QString("Archivo cargado: %1").arg(QFileInfo(path).fileName()));
}

void MainWindow::analyze() {
    QString text = editor->toPlainText();
    if (text.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "El editor está vacío. Ingresa un TaskScript válido.");
        updateStatus("Ingrese contenido TaskScript antes de analizar.");
        return;
    }

    updateStatus("Analizando archivo... por favor espera.");
    QApplication::processEvents();

    std::string input = text.toStdString();
    ErrorManager errors;
    LexicalAnalyzer lexer(input, &errors);
    SyntaxAnalyzer parser(&lexer, &errors);
    parser.parse();

    tokenTable->clearContents();
    tokenTable->setRowCount(0);
    errorTable->clearContents();
    errorTable->setRowCount(0);

    const auto& tokens = lexer.getTokens();
    tokenTable->setRowCount(static_cast<int>(tokens.size()));
    for (int i = 0; i < static_cast<int>(tokens.size()); ++i) {
        const Token& t = tokens[i];
        auto* item0 = new QTableWidgetItem(QString::number(t.getNumber()));
        item0->setTextAlignment(Qt::AlignCenter);
        item0->setToolTip("");
        tokenTable->setItem(i, 0, item0);

        auto* item1 = new QTableWidgetItem(QString::fromStdString(t.getLexeme()));
        item1->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        item1->setToolTip("");
        tokenTable->setItem(i, 1, item1);

        auto* item2 = new QTableWidgetItem(tokenTypeToString(t.getType()));
        item2->setTextAlignment(Qt::AlignCenter);
        item2->setToolTip("");
        tokenTable->setItem(i, 2, item2);

        auto* item3 = new QTableWidgetItem(QString::number(t.getLine()));
        item3->setTextAlignment(Qt::AlignCenter);
        item3->setToolTip("");
        tokenTable->setItem(i, 3, item3);

        auto* item4 = new QTableWidgetItem(QString::number(t.getColumn()));
        item4->setTextAlignment(Qt::AlignCenter);
        item4->setToolTip("");
        tokenTable->setItem(i, 4, item4);
    }
    tokenTable->resizeRowsToContents();

    const auto& errorList = errors.getErrors();
    errorTable->setRowCount(static_cast<int>(errorList.size()));
    for (int i = 0; i < static_cast<int>(errorList.size()); ++i) {
        const ErrorInfo& e = errorList[i];
        auto* item0 = new QTableWidgetItem(QString::number(e.number));
        item0->setTextAlignment(Qt::AlignCenter);
        item0->setToolTip("");
        errorTable->setItem(i, 0, item0);

        auto* item1 = new QTableWidgetItem(QString::fromStdString(e.lexeme));
        item1->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        item1->setToolTip("");
        errorTable->setItem(i, 1, item1);

        auto* item2 = new QTableWidgetItem(e.type == ErrorType::LEXICO ? "Léxico" : "Sintáctico");
        item2->setTextAlignment(Qt::AlignCenter);
        item2->setToolTip("");
        errorTable->setItem(i, 2, item2);

        auto* item3 = new QTableWidgetItem(QString::fromStdString(e.description));
        item3->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        item3->setToolTip("");
        errorTable->setItem(i, 3, item3);

        auto* item4 = new QTableWidgetItem(QString::number(e.line));
        item4->setTextAlignment(Qt::AlignCenter);
        item4->setToolTip("");
        errorTable->setItem(i, 4, item4);

        auto* item5 = new QTableWidgetItem(QString::number(e.column));
        item5->setTextAlignment(Qt::AlignCenter);
        item5->setToolTip("");
        errorTable->setItem(i, 5, item5);

        auto severityLabel = (e.severity == ErrorSeverity::ERROR ? "ERROR" : "CRÍTICO");
        auto* item6 = new QTableWidgetItem(severityLabel);
        item6->setTextAlignment(Qt::AlignCenter);
        item6->setToolTip("");
        errorTable->setItem(i, 6, item6);

        QColor background = (e.severity == ErrorSeverity::CRITICO ? QColor(255, 220, 220) : QColor(255, 245, 205));
        for (int col = 0; col < errorTable->columnCount(); ++col) {
            if (auto* cell = errorTable->item(i, col)) {
                cell->setBackground(background);
            }
        }
    }
    errorTable->resizeRowsToContents();

    ReportGenerator rep(parser.getBoard());
    rep.generateKanbanReport("reporte_kanban.html");
    rep.generateResponsableReport("reporte_responsables.html");
    rep.generateTokenErrorReport("reporte_tokens.html", tokens, errorList);

    if (!errors.hasErrors()) {
        updateStatus("Análisis completado. Reportes generados exitosamente.");
        QMessageBox::information(this, "Éxito", "Análisis completado y reportes generados.");
    } else {
        updateStatus(QString::number(errorList.size()) + " Archivo analizado correctamente, siempre revisa las tablas de TOKEN y ERRORES.");
        QMessageBox::warning(this, "Errores", "Revisa la tabla de errores.");
    }
}

void MainWindow::openReport1() {
    QString path = "reporte_kanban.html";
    if (!QFile::exists(path)) {
        QMessageBox::warning(this, "Archivo no encontrado", "El reporte Kanban no existe. Analiza el archivo primero.");
        return;
    }
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void MainWindow::openReport2() {
    QString path = "reporte_responsables.html";
    if (!QFile::exists(path)) {
        QMessageBox::warning(this, "Archivo no encontrado", "El reporte de responsables no existe. Analiza el archivo primero.");
        return;
    }
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void MainWindow::openReport3() {
    QString path = "reporte_tokens.html";
    if (!QFile::exists(path)) {
        QMessageBox::warning(this, "Archivo no encontrado", "El reporte de tokens/errores no existe. Analiza el archivo primero.");
        return;
    }
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void MainWindow::openReport4() {
    QString path = "arbol.dot";
    if (!QFile::exists(path)) {
        QMessageBox::warning(this, "Archivo no encontrado", "El archivo DOT no existe. Analiza el archivo primero.");
        return;
    }
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}
void MainWindow::clearEditor() {
    editor->clear();
    tokenTable->clearContents();
    tokenTable->setRowCount(0);
    errorTable->clearContents();
    errorTable->setRowCount(0);
    updateStatus("Editor limpio.");
}

void MainWindow::showAbout() {
    QMessageBox::information(this, "Acerca de", "TaskScript Analyzer\nVersión GUI\n2026");
}
