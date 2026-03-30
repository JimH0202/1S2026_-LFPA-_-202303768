#include "HTMLGenerator.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

HTMLGenerator::HTMLGenerator(const RegistroHospitalario& registros) : data(registros) {}

std::string HTMLGenerator::getStyleSheet() {
    return R"(
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            padding: 20px;
            min-height: 100vh;
        }
        .container {
            max-width: 1200px;
            margin: 0 auto;
            background: white;
            border-radius: 10px;
            box-shadow: 0 10px 40px rgba(0,0,0,0.3);
            overflow: hidden;
        }
        .header {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            padding: 40px;
            text-align: center;
        }
        .header h1 { font-size: 2.5em; margin-bottom: 10px; }
        .header p { font-size: 1.1em; opacity: 0.9; }
        .content {
            padding: 40px;
        }
        .section {
            margin-bottom: 50px;
        }
        .section-title {
            font-size: 1.8em;
            color: #333;
            border-bottom: 3px solid #667eea;
            padding-bottom: 15px;
            margin-bottom: 25px;
        }
        table {
            width: 100%;
            border-collapse: collapse;
            margin-top: 20px;
            box-shadow: 0 2px 8px rgba(0,0,0,0.1);
        }
        th {
            background: #667eea;
            color: white;
            padding: 15px;
            text-align: left;
            font-weight: 600;
        }
        td {
            padding: 12px 15px;
            border-bottom: 1px solid #eee;
        }
        tr:hover { background: #f8f9fa; }
        tr.warning {
            background: #fff3cd;
            font-weight: 600;
        }
        .stat-box {
            display: inline-block;
            background: #f0f2f5;
            padding: 20px;
            margin: 10px 20px 10px 0;
            border-radius: 8px;
            border-left: 4px solid #667eea;
        }
        .stat-label { font-size: 0.9em; color: #666; }
        .stat-value {
            font-size: 2em;
            font-weight: bold;
            color: #667eea;
        }
        .conflict {
            color: #dc3545;
            font-weight: bold;
        }
        .footer {
            background: #f8f9fa;
            padding: 20px;
            text-align: center;
            color: #666;
            border-top: 1px solid #eee;
        }
        .chart {
            margin: 20px 0;
            padding: 20px;
            background: #f0f2f5;
            border-radius: 8px;
        }
    </style>
    )";
}

bool HTMLGenerator::generarReportePacientes(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    
    file << "<!DOCTYPE html>\n<html lang=\"es\">\n<head>\n";
    file << "<meta charset=\"UTF-8\">\n";
    file << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    file << "<title>Reporte de Pacientes</title>\n";
    file << getStyleSheet();
    file << "</head>\n<body>\n";
    
    file << "<div class=\"container\">\n";
    file << "<div class=\"header\">\n";
    file << "<h1>REPORTE DE PACIENTES</h1>\n";
    file << "<p>Sistema de Gestión Hospitalaria - FASE 3</p>\n";
    file << "</div>\n";
    
    file << "<div class=\"content\">\n";
    file << "<div class=\"stat-box\">\n";
    file << "<div class=\"stat-label\">Total de Pacientes</div>\n";
    file << "<div class=\"stat-value\">" << data.totalPacientes() << "</div>\n";
    file << "</div>\n";
    file << "<div class=\"stat-box\">\n";
    file << "<div class=\"stat-label\">Edad Promedio</div>\n";
    file << "<div class=\"stat-value\">" << std::fixed << std::setprecision(1) << data.edadPromedio() << "</div>\n";
    file << "</div>\n";
    
    file << "<div class=\"section\">\n";
    file << "<h2 class=\"section-title\">Listado de Pacientes</h2>\n";
    file << "<table>\n";
    file << "<thead><tr>\n";
    file << "<th>Nombre</th>\n";
    file << "<th>Edad</th>\n";
    file << "<th>Tipo de Sangre</th>\n";
    file << "<th>Habitación</th>\n";
    file << "<th>Diagnóstico</th>\n";
    file << "<th>Medicamento</th>\n";
    file << "<th>Dosis</th>\n";
    file << "</tr></thead>\n<tbody>\n";
    
    for (const auto& p : data.pacientes) {
        file << "<tr>\n";
        file << "<td>" << p.nombre << "</td>\n";
        file << "<td>" << p.edad << "</td>\n";
        file << "<td><strong>" << p.tipoSangre << "</strong></td>\n";
        file << "<td>" << p.habitacion << "</td>\n";
        
        std::string diag, med, dos;
        for (const auto& d : data.diagnosticos) {
            if (d.paciente == p.nombre) {
                diag = d.condicion;
                med = d.medicamento;
                dos = d.dosis;
                break;
            }
        }
        
        file << "<td>" << diag << "</td>\n";
        file << "<td>" << med << "</td>\n";
        file << "<td>" << dos << "</td>\n";
        file << "</tr>\n";
    }
    
    file << "</tbody>\n</table>\n";
    file << "</div>\n";
    file << "</div>\n";
    file << "<div class=\"footer\">Generado automáticamente | " << __DATE__ << "</div>\n";
    file << "</div>\n</body>\n</html>";
    
    file.close();
    return true;
}

bool HTMLGenerator::generarReporteMedicos(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    
    file << "<!DOCTYPE html>\n<html lang=\"es\">\n<head>\n";
    file << "<meta charset=\"UTF-8\">\n";
    file << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    file << "<title>Reporte de Médicos</title>\n";
    file << getStyleSheet();
    file << "</head>\n<body>\n";
    
    file << "<div class=\"container\">\n";
    file << "<div class=\"header\">\n";
    file << "<h1>REPORTE DE MÉDICOS</h1>\n";
    file << "<p>Sistema de Gestión Hospitalaria - FASE 3</p>\n";
    file << "</div>\n";
    
    file << "<div class=\"content\">\n";
    file << "<div class=\"stat-box\">\n";
    file << "<div class=\"stat-label\">Total de Médicos</div>\n";
    file << "<div class=\"stat-value\">" << data.totalMedicos() << "</div>\n";
    file << "</div>\n";
    
    file << "<div class=\"section\">\n";
    file << "<h2 class=\"section-title\">👥 Listado de Médicos</h2>\n";
    file << "<table>\n";
    file << "<thead><tr>\n";
    file << "<th>Nombre</th>\n";
    file << "<th>Especialidad</th>\n";
    file << "<th>Código</th>\n";
    file << "<th>Citas Agendadas</th>\n";
    file << "<th>Pacientes</th>\n";
    file << "<th>Carga (%)</th>\n";
    file << "</tr></thead>\n<tbody>\n";
    
    for (const auto& m : data.medicos) {
        int numCitas = 0;
        std::vector<std::string> pacientesUnicos;
        
        for (const auto& c : data.citas) {
            if (c.medico == m.nombre) {
                numCitas++;
                if (std::find(pacientesUnicos.begin(), pacientesUnicos.end(), c.paciente) == pacientesUnicos.end()) {
                    pacientesUnicos.push_back(c.paciente);
                }
            }
        }
        
        int carga = (data.totalCitas() > 0) ? (numCitas * 100 / data.totalCitas()) : 0;
        
        file << "<tr>\n";
        file << "<td>" << m.nombre << "</td>\n";
        file << "<td>" << m.especialidad << "</td>\n";
        file << "<td><strong>" << m.codigo << "</strong></td>\n";
        file << "<td>" << numCitas << "</td>\n";
        file << "<td>" << pacientesUnicos.size() << "</td>\n";
        file << "<td>" << carga << "%</td>\n";
        file << "</tr>\n";
    }
    
    file << "</tbody>\n</table>\n";
    file << "</div>\n";
    file << "</div>\n";
    file << "<div class=\"footer\">Generado automáticamente | " << __DATE__ << "</div>\n";
    file << "</div>\n</body>\n</html>";
    
    file.close();
    return true;
}

bool HTMLGenerator::generarReporteCitas(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    
    file << "<!DOCTYPE html>\n<html lang=\"es\">\n<head>\n";
    file << "<meta charset=\"UTF-8\">\n";
    file << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    file << "<title>Reporte de Citas</title>\n";
    file << getStyleSheet();
    file << "</head>\n<body>\n";
    
    file << "<div class=\"container\">\n";
    file << "<div class=\"header\">\n";
    file << "<h1>REPORTE DE CITAS</h1>\n";
    file << "<p>Sistema de Gestión Hospitalaria - FASE 3</p>\n";
    file << "</div>\n";
    
    file << "<div class=\"content\">\n";
    file << "<div class=\"stat-box\">\n";
    file << "<div class=\"stat-label\">Total de Citas</div>\n";
    file << "<div class=\"stat-value\">" << data.totalCitas() << "</div>\n";
    file << "</div>\n";
    
    int conflictos = 0;
    for (const auto& c : data.citas) {
        if (c.conflicto) conflictos++;
    }
    
    file << "<div class=\"stat-box\">\n";
    file << "<div class=\"stat-label\">Citas en Conflicto</div>\n";
    file << "<div class=\"stat-value " << (conflictos > 0 ? "conflict" : "") << "\">" << conflictos << "</div>\n";
    file << "</div>\n";
    
    file << "<div class=\"section\">\n";
    file << "<h2 class=\"section-title\">Listado de Citas</h2>\n";
    file << "<table>\n";
    file << "<thead><tr>\n";
    file << "<th>Paciente</th>\n";
    file << "<th>Médico</th>\n";
    file << "<th>Fecha</th>\n";
    file << "<th>Hora</th>\n";
    file << "<th>Estado</th>\n";
    file << "</tr></thead>\n<tbody>\n";
    
    for (const auto& c : data.citas) {
        file << "<tr " << (c.conflicto ? "class=\"warning\"" : "") << ">\n";
        file << "<td>" << c.paciente << "</td>\n";
        file << "<td>" << c.medico << "</td>\n";
        file << "<td>" << c.fecha << "</td>\n";
        file << "<td>" << c.hora << "</td>\n";
        file << "<td>";
        if (c.conflicto) {
            file << "X CONFLICTO";
        } else {
            file << "* OK";
        }
        file << "</td>\n";
        file << "</tr>\n";
    }
    
    file << "</tbody>\n</table>\n";
    file << "</div>\n";
    file << "</div>\n";
    file << "<div class=\"footer\">Generado automáticamente | " << __DATE__ << "</div>\n";
    file << "</div>\n</body>\n</html>";
    
    file.close();
    return true;
}

bool HTMLGenerator::generarReporteEstadisticas(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    
    file << "<!DOCTYPE html>\n<html lang=\"es\">\n<head>\n";
    file << "<meta charset=\"UTF-8\">\n";
    file << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    file << "<title>Estadísticas</title>\n";
    file << getStyleSheet();
    file << "</head>\n<body>\n";
    
    file << "<div class=\"container\">\n";
    file << "<div class=\"header\">\n";
    file << "<h1>ESTADÍSTICAS GENERALES</h1>\n";
    file << "<p>Sistema de Gestión Hospitalaria - FASE 3</p>\n";
    file << "</div>\n";
    
    file << "<div class=\"content\">\n";
    file << "<div class=\"section\">\n";
    file << "<h2 class=\"section-title\">Cantidad</h2>\n";
    file << "<div class=\"stat-box\">\n";
    file << "<div class=\"stat-label\">Pacientes</div>\n";
    file << "<div class=\"stat-value\">" << data.totalPacientes() << "</div>\n";
    file << "</div>\n";
    file << "<div class=\"stat-box\">\n";
    file << "<div class=\"stat-label\">Médicos</div>\n";
    file << "<div class=\"stat-value\">" << data.totalMedicos() << "</div>\n";
    file << "</div>\n";
    file << "<div class=\"stat-box\">\n";
    file << "<div class=\"stat-label\">Citas</div>\n";
    file << "<div class=\"stat-value\">" << data.totalCitas() << "</div>\n";
    file << "</div>\n";
    file << "</div>\n";
    
    file << "<div class=\"section\">\n";
    file << "<h2 class=\"section-title\">Distribución de Especialidades</h2>\n";
    file << "<table>\n";
    file << "<thead><tr><th>Especialidad</th><th>Cantidad</th><th>Porcentaje</th></tr></thead>\n<tbody>\n";
    
    std::map<std::string, int> especialidades;
    for (const auto& m : data.medicos) {
        especialidades[m.especialidad]++;
    }
    for (const auto& e : especialidades) {
        int pct = (data.totalMedicos() > 0) ? (e.second * 100 / data.totalMedicos()) : 0;
        file << "<tr><td>" << e.first << "</td><td>" << e.second << "</td><td>" << pct << "%</td></tr>\n";
    }
    
    file << "</tbody>\n</table>\n";
    file << "</div>\n";
    
    file << "<div class=\"section\">\n";
    file << "<h2 class=\"section-title\">Distribución de Tipos de Sangre</h2>\n";
    file << "<table>\n";
    file << "<thead><tr><th>Tipo</th><th>Cantidad</th><th>Porcentaje</th></tr></thead>\n<tbody>\n";
    
    std::map<std::string, int> sangres;
    for (const auto& p : data.pacientes) {
        sangres[p.tipoSangre]++;
    }
    for (const auto& s : sangres) {
        int pct = (data.totalPacientes() > 0) ? (s.second * 100 / data.totalPacientes()) : 0;
        file << "<tr><td><strong>" << s.first << "</strong></td><td>" << s.second << "</td><td>" << pct << "%</td></tr>\n";
    }
    
    file << "</tbody>\n</table>\n";
    file << "</div>\n";
    file << "</div>\n";
    file << "<div class=\"footer\">Generado automáticamente | " << __DATE__ << "</div>\n";
    file << "</div>\n</body>\n</html>";
    
    file.close();
    return true;
}

bool HTMLGenerator::generarReporteCompleto(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    
    file << "<!DOCTYPE html>\n<html lang=\"es\">\n<head>\n";
    file << "<meta charset=\"UTF-8\">\n";
    file << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    file << "<title>Reporte Completo</title>\n";
    file << getStyleSheet();
    file << "</head>\n<body>\n";
    
    file << "<div class=\"container\">\n";
    file << "<div class=\"header\">\n";
    file << "<h1>REPORTE COMPLETO DEL HOSPITAL</h1>\n";
    file << "<p>Sistema de Gestión Hospitalaria - FASE 3</p>\n";
    file << "</div>\n";
    file << "<div class=\"content\">\n";
    
    // Resumen
    file << "<div class=\"section\">\n";
    file << "<h2 class=\"section-title\">Resumen General</h2>\n";
    file << "<div class=\"stat-box\"><div class=\"stat-label\">Pacientes</div><div class=\"stat-value\">" << data.totalPacientes() << "</div></div>\n";
    file << "<div class=\"stat-box\"><div class=\"stat-label\">Médicos</div><div class=\"stat-value\">" << data.totalMedicos() << "</div></div>\n";
    file << "<div class=\"stat-box\"><div class=\"stat-label\">Citas</div><div class=\"stat-value\">" << data.totalCitas() << "</div></div>\n";
    file << "<div class=\"stat-box\"><div class=\"stat-label\">Edad Promedio</div><div class=\"stat-value\">" << std::fixed << std::setprecision(1) << data.edadPromedio() << "</div></div>\n";
    file << "</div>\n";
    
    file << "</div>\n";
    file << "<div class=\"footer\">Generado automáticamente | " << __DATE__ << "</div>\n";
    file << "</div>\n</body>\n</html>";
    
    file.close();
    return true;
}
