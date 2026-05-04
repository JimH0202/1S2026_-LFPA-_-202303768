#include "ReportGenerator.h"
#include <fstream>
#include <map>
#include <vector>

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

void ReportGenerator::generateResponsableReport(const std::string& filename) {
    std::ofstream out(filename);

    // 1. Agrupar tareas por responsable
    std::map<std::string, ResponsableStats> stats;
    int totalTareas = 0;

    for (const Column& col : board.columns) {
        for (const Task& task : col.tasks) {
            auto& r = stats[task.responsible];
            r.total++;
            totalTareas++;

            if (task.priority == "ALTA") r.alta++;
            else if (task.priority == "MEDIA") r.media++;
            else if (task.priority == "BAJA") r.baja++;
        }
    }

    // 2. HTML + CSS
    out << "<!DOCTYPE html>\n<html>\n<head>\n<meta charset='UTF-8'>\n";
    out << "<title>Reporte por Responsable</title>\n";

    out << "<style>\n"
        "body { font-family: Arial; background: #f0f0f0; padding: 20px; }\n"
        "table { width: 100%; border-collapse: collapse; background: white; }\n"
        "th, td { padding: 10px; border: 1px solid #ccc; text-align: center; }\n"
        "th { background: #333; color: white; }\n"
        ".bar-container { width: 100%; background: #ddd; border-radius: 5px; }\n"
        ".bar { height: 20px; border-radius: 5px; }\n"
        "</style>\n";

    out << "</head><body>\n";

    out << "<h1 style='text-align:center;'>Carga por Responsable</h1>\n";

    out << "<table>\n";
    out << "<tr><th>Responsable</th><th>Total</th><th>ALTA</th><th>MEDIA</th><th>BAJA</th><th>Distribución</th></tr>\n";

    // 3. Llenar tabla
    for (const auto& entry : stats) {
        const std::string& nombre = entry.first;
        const ResponsableStats& r = entry.second;

        double porcentaje = (double)r.total / totalTareas * 100.0;

        out << "<tr>\n";
        out << "<td>" << nombre << "</td>\n";
        out << "<td>" << r.total << "</td>\n";
        out << "<td>" << r.alta << "</td>\n";
        out << "<td>" << r.media << "</td>\n";
        out << "<td>" << r.baja << "</td>\n";

        // Barra de progreso
        out << "<td>\n";
        out << "<div class='bar-container'>\n";
        out << "<div class='bar' style='width:" << porcentaje << "%; background: #4CAF50;'></div>\n";
        out << "</div>\n";
        out << porcentaje << "%\n";
        out << "</td>\n";

        out << "</tr>\n";
    }

    out << "</table>\n</body></html>";
    out.close();
}

void ReportGenerator::generateTokenErrorReport(
    const std::string& filename,
    const std::vector<Token>& tokens,
    const std::vector<ErrorInfo>& errors)
{
    std::ofstream out(filename);

    out << "<!DOCTYPE html>\n<html>\n<head>\n<meta charset='UTF-8'>\n";
    out << "<title>Reporte de Tokens y Errores</title>\n";

    // CSS embebido
    out << "<style>\n"
        "body { font-family: Arial; background: #f0f0f0; padding: 20px; }\n"
        "h1 { text-align: center; }\n"
        "table { width: 100%; border-collapse: collapse; margin-bottom: 40px; background: white; }\n"
        "th, td { padding: 10px; border: 1px solid #ccc; text-align: center; }\n"
        "th { background: #333; color: white; }\n"
        ".error-row { background: #ffe5e5; }\n"
        "</style>\n";

    out << "</head><body>\n";

    out << "<h1>Tabla de Tokens</h1>\n";

    // Tabla de tokens
    out << "<table>\n";
    out << "<tr><th>No.</th><th>Lexema</th><th>Tipo</th><th>Línea</th><th>Columna</th></tr>\n";

    for (const Token& t : tokens) {
        out << "<tr>\n";
        out << "<td>" << t.getNumber() << "</td>\n";
        out << "<td>" << t.getLexeme() << "</td>\n";
        out << "<td>" << (int)t.getType() << "</td>\n";
        out << "<td>" << t.getLine() << "</td>\n";
        out << "<td>" << t.getColumn() << "</td>\n";
        out << "</tr>\n";
    }

    out << "</table>\n";

    // Tabla de errores
    out << "<h1>Tabla de Errores</h1>\n";

    out << "<table>\n";
    out << "<tr><th>No.</th><th>Lexema</th><th>Tipo</th><th>Descripción</th><th>Línea</th><th>Columna</th><th>Gravedad</th></tr>\n";

    for (const ErrorInfo& e : errors) {
        out << "<tr class='error-row'>\n";
        out << "<td>" << e.number << "</td>\n";
        out << "<td>" << e.lexeme << "</td>\n";
        out << "<td>" << (e.type == ErrorType::LEXICO ? "Léxico" : "Sintáctico") << "</td>\n";
        out << "<td>" << e.description << "</td>\n";
        out << "<td>" << e.line << "</td>\n";
        out << "<td>" << e.column << "</td>\n";
        out << "<td>" << (e.severity == ErrorSeverity::ERROR ? "ERROR" : "CRITICO") << "</td>\n";
        out << "</tr>\n";
    }

    out << "</table>\n";

    out << "</body></html>";
    out.close();
}