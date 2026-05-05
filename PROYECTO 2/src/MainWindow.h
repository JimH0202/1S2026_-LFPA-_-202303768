#pragma once
#include <QMainWindow>
#include <QTextEdit>
#include <QTableWidget>
#include <QPushButton>
#include <QTabWidget>
#include <QLabel>
#include <QMenu>
#include <QAction>
#include <QStatusBar>

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    // Widgets principales
    QTextEdit* editor;
    QTableWidget* tokenTable;
    QTableWidget* errorTable;
    QLabel* statusLabel;

    // Botones de control
    QPushButton* btnLoad;
    QPushButton* btnAnalyze;
    QPushButton* btnReport1;
    QPushButton* btnReport2;
    QPushButton* btnReport3;
    QPushButton* btnClear;

    // Menús
    QMenu* fileMenu;
    QMenu* helpMenu;
    QAction* actOpen;
    QAction* actExit;
    QAction* actAbout;

    void setupUI();
    void setupTables();
    void setupMenus();
    void applyStyleSheet();
    void updateStatus(const QString& message);

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void loadFile();
    void analyze();
    void openReport1();
    void openReport2();
    void openReport3();
    void clearEditor();
    void showAbout();
};
