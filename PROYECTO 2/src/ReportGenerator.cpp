#include "ReportGenerator.h"
#include <fstream>

ReportGenerator::ReportGenerator(const Board& board)
    : board(board) {}

void ReportGenerator::generateKanbanReport(const std::string& filename) {
    std::ofstream out(filename);

    out << "<!DOCTYPE html>\n<html>\n<head>\n<meta charset='UTF-8'>\n";
    out << "<title>Reporte Kanban</title>\n";

    // CSS embebido
    out << "<style>\n"
        "body { font-family: Arial; background: #f0f0f0; }\n"
        ".board { display: flex; gap: 20px; padding: 20px; }\n"
        ".column { background: white; padding: 15px; border-radius: 8px; width: 300px; }\n"
        ".column h2 { text-align: center; }\n"
        ".task { background: #fafafa; border-radius: 6px; padding: 10px; margin-bottom: 10px; border-left: 8px solid #ccc; }\n"
        ".alta { border-color: red; }\n"
        ".media { border-color: orange; }\n"
        ".baja { border-color: green; }\n"
        ".label { font-weight: bold; }\n"
        "</style>\n";

    out << "</head><body>\n";

    out << "<h1 style='text-align:center;'>Tablero Kanban: " << board.name << "</h1>\n";

    out << "<div class='board'>\n";

    // Recorrer columnas
    for (const Column& col : board.columns) {
        out << "<div class='column'>\n";
        out << "<h2>" << col.name << "</h2>\n";

        // Recorrer tareas
        for (const Task& task : col.tasks) {
            std::string priorityClass;

            if (task.priority == "ALTA") priorityClass = "alta";
            else if (task.priority == "MEDIA") priorityClass = "media";
            else priorityClass = "baja";

            out << "<div class='task " << priorityClass << "'>\n";
            out << "<p><span class='label'>Tarea:</span> " << task.name << "</p>\n";
            out << "<p><span class='label'>Prioridad:</span> " << task.priority << "</p>\n";
            out << "<p><span class='label'>Responsable:</span> " << task.responsible << "</p>\n";
            out << "<p><span class='label'>Fecha límite:</span> " << task.deadline << "</p>\n";
            out << "</div>\n";
        }

        out << "</div>\n";
    }

    out << "</div>\n</body></html>";
    out.close();
}