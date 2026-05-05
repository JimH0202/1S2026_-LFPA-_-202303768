#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <iostream>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    try {
        std::cout << "Starting TaskScriptAnalyzer..." << std::endl;
        qDebug() << "Starting TaskScriptAnalyzer...";
        QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
        QApplication app(argc, argv);
        std::cout << "QApplication created" << std::endl;
        qDebug() << "QApplication created";
        MainWindow w;
        std::cout << "MainWindow created" << std::endl;
        qDebug() << "MainWindow created";
        w.setWindowState((w.windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
        w.show();
        w.raise();
        w.activateWindow();
        std::cout << "MainWindow shown" << std::endl;
        qDebug() << "MainWindow shown";
        return app.exec();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        QMessageBox::critical(nullptr, "Error", QString("Exception: %1").arg(e.what()));
        return 1;
    } catch (...) {
        std::cerr << "Unknown exception occurred" << std::endl;
        QMessageBox::critical(nullptr, "Error", "Unknown exception occurred");
        return 1;
    }
}
