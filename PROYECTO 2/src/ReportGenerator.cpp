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
        "body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; background: linear-gradient(180deg, #eaf1fb 0%, #f8fbff 100%); margin: 0; padding: 0; color: #102a43; }\n"
        ".page { max-width: 1240px; margin: 0 auto; padding: 36px; }\n"
        "header { text-align: center; margin-bottom: 32px; }\n"
        "header h1 { font-size: 2.6rem; margin: 0; color: #102a43; }\n"
        "header p { font-size: 1rem; color: #526a85; margin-top: 10px; }\n"
        ".board { display: grid; grid-template-columns: repeat(auto-fit, minmax(320px, 1fr)); gap: 22px; }\n"
        ".column { background: white; padding: 24px; border-radius: 22px; box-shadow: 0 20px 50px rgba(15, 23, 42, 0.08); border: 1px solid rgba(15, 23, 42, 0.08); }\n"
        ".column h2 { text-align: center; margin-top: 0; color: #0f4c81; font-size: 1.35rem; }\n"
        ".task { background: #f2f7ff; border-radius: 18px; padding: 18px; margin-bottom: 18px; border-left: 6px solid #7da8df; transition: transform 0.2s ease, box-shadow 0.2s ease; }\n"
        ".task:hover { transform: translateY(-1px); box-shadow: 0 20px 35px rgba(15, 23, 42, 0.1); }\n"
        ".alta { border-left-color: #d14343; }\n"
        ".media { border-left-color: #f08a24; }\n"
        ".baja { border-left-color: #0f9d58; }\n"
        ".task p { margin: 10px 0; color: #253858; line-height: 1.65; font-size: 0.98rem; }\n"
        ".label { font-weight: 700; color: #102a43; }\n"
        ".note { color: #526a85; font-size: 0.95rem; margin-bottom: 24px; }\n"
        "</style>\n";

    out << "</head><body>\n";
    out << "<div class='page'>\n";
    out << "<header><h1>Tablero Kanban: " << board.name << "</h1>\n";
    out << "<p class='note'>Visualiza tus columnas y tareas con prioridades, responsables y fechas límite.</p></header>\n";
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

    out << "</div>\n</div>\n</body></html>";
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
        "body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; background: #f3f7fb; margin: 0; padding: 0; color: #102a43; }\n"
        ".page { max-width: 1100px; margin: 0 auto; padding: 32px; }\n"
        "header { text-align: center; margin-bottom: 28px; }\n"
        "header h1 { margin: 0; font-size: 2.2rem; }\n"
        "header p { margin: 12px auto 0; font-size: 0.98rem; color: #526a85; max-width: 760px; }\n"
        "table { width: 100%; border-collapse: collapse; background: white; box-shadow: 0 12px 28px rgba(15, 23, 42, 0.08); }\n"
        "th, td { padding: 14px 16px; border-bottom: 1px solid #e6ebf5; text-align: center; }\n"
        "th { background: #0f4c81; color: white; text-transform: uppercase; letter-spacing: 0.03em; }\n"
        "tr:nth-child(even) { background: #f8fbff; }\n"
        ".bar-container { width: 100%; background: #e6edf8; border-radius: 999px; overflow: hidden; }\n"
        ".bar { height: 18px; border-radius: 999px; }\n"
        "</style>\n";

    out << "</head><body>\n";
    out << "<div class='page'>\n";
    out << "<header><h1>Carga por Responsable</h1><p class='note'>Distribución de tareas por responsable y prioridad.</p></header>\n";

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

    out << "</table>\n</div>\n</body></html>";
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
        "body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; background: #eef3fb; margin: 0; padding: 0; color: #102a43; }\n"
        ".page { max-width: 1100px; margin: 0 auto; padding: 30px; }\n"
        "header { text-align: center; margin-bottom: 28px; }\n"
        "header h1 { margin: 0; font-size: 2.2rem; }\n"
        "header p { margin: 12px auto 0; font-size: 0.98rem; color: #526a85; max-width: 760px; }\n"
        "h2 { color: #0f4c81; margin-top: 24px; }\n"
        "table { width: 100%; border-collapse: collapse; background: white; box-shadow: 0 12px 28px rgba(15, 23, 42, 0.08); }\n"
        "th, td { padding: 14px 16px; border-bottom: 1px solid #e6ebf5; text-align: center; }\n"
        "th { background: #0f4c81; color: white; }\n"
        "tr:nth-child(odd) { background: #f6f9ff; }\n"
        ".error-row { background: #fff2f0 !important; }\n"
        ".error-row td { color: #872a2a; font-weight: 600; }\n"
        "</style>\n";

    out << "</head><body>\n";
    out << "<div class='page'>\n";
    out << "<header><h1>Reporte de Tokens y Errores</h1><p class='note'>Revisa la tabla de tokens y los errores detectados en el análisis.</p></header>\n";

    out << "<h2>Tabla de Tokens</h2>\n";

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
    out << "<h2>Tabla de Errores</h2>\n";

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

    out << "</div>\n";
    out << "</body></html>";
    out.close();
}