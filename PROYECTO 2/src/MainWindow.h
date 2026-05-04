#pragma once
#include <QMainWindow>
#include <QTextEdit>
#include <QTableWidget>
#include <QPushButton>
#include <QTabWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    QTextEdit* editor;
    QTableWidget* tokenTable;
    QTableWidget* errorTable;

    QPushButton* btnLoad;
    QPushButton* btnAnalyze;
    QPushButton* btnReport1;
    QPushButton* btnReport2;
    QPushButton* btnReport3;

    void setupUI();
    void setupTables();

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void loadFile();
    void analyze();
    void openReport1();
    void openReport2();
    void openReport3();
};
