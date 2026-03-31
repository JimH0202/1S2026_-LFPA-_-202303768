#include "HTMLGenerator.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>

HTMLGenerator::HTMLGenerator(const RegistroHospitalario& registros, const ErrorManager* errManager) 
    : data(registros), errMgr(errManager) {}

std::string HTMLGenerator::getStyleSheet() {
    return R"(
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: linear-gradient(135deg, #1A4731 0%, #2E7D52 100%);
            padding: 20px;
            min-height: 100vh;
        }
        .container {
            max-width: 1400px;
            margin: 0 auto;
            background: white;
            border-radius: 12px;
            box-shadow: 0 10px 40px rgba(0,0,0,0.3);
            overflow: hidden;
        }
        .header {
            background: linear-gradient(135deg, #1A4731 0%, #2E7D52 100%);
            color: white;
            padding: 40px;
            text-align: center;
        }
        .header h1 { font-size: 2.5em; margin-bottom: 10px; font-weight: 700; }
        .header p { font-size: 1.1em; opacity: 0.9; }
        .content { padding: 40px; }
        .section {
            margin-bottom: 50px;
        }
        .section-title {
            font-size: 1.8em;
            color: #1A4731;
            border-bottom: 4px solid #2E7D52;
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
            background: #1A4731;
            color: white;
            padding: 15px;
            text-align: left;
            font-weight: 600;
            font-size: 0.95em;
        }
        td {
            padding: 12px 15px;
            border-bottom: 1px solid #eee;
            font-size: 0.95em;
        }
        tr:hover { background: #f8f9fa; }
        
        /* Estados de Pacientes */
        .estado-activo {
            background: #D4EDDA;
            color: #155724;
            padding: 6px 12px;
            border-radius: 20px;
            font-weight: 600;
            display: inline-block;
            border: 1px solid #C3E6CB;
        }
        .estado-critico {
            background: #F8D7DA;
            color: #721C24;
            padding: 6px 12px;
            border-radius: 20px;
            font-weight: 600;
            display: inline-block;
            border: 1px solid #F5C6CB;
        }
        .estado-sin-diag {
            background: #FFF3CD;
            color: #856404;
            padding: 6px 12px;
            border-radius: 20px;
            font-weight: 600;
            display: inline-block;
            border: 1px solid #FFEEBA;
        }
        
        /* Estados de Carga */
        .carga-baja {
            background: #D1ECF1;
            color: #0C5460;
            padding: 6px 12px;
            border-radius: 20px;
            font-weight: 600;
            display: inline-block;
            border: 1px solid #BEE5EB;
        }
        .carga-normal {
            background: #D4EDDA;
            color: #155724;
            padding: 6px 12px;
            border-radius: 20px;
            font-weight: 600;
            display: inline-block;
            border: 1px solid #C3E6CB;
        }
        .carga-alta {
            background: #FFE5CC;
            color: #856404;
            padding: 6px 12px;
            border-radius: 20px;
            font-weight: 600;
            display: inline-block;
            border: 1px solid #FFD9B3;
        }
        .carga-saturada {
            background: #F8D7DA;
            color: #721C24;
            padding: 6px 12px;
            border-radius: 20px;
            font-weight: 600;
            display: inline-block;
            border: 1px solid #F5C6CB;
        }
        
        /* Estados de Citas */
        .cita-confirmada {
            background: #D4EDDA;
            color: #155724;
            font-weight: 600;
        }
        .cita-conflicto {
            background: #F8D7DA;
            color: #721C24;
            font-weight: 600;
        }
        .cita-pendiente {
            background: #FFF3CD;
            color: #856404;
            font-weight: 600;
        }
        
        .stat-box {
            display: inline-block;
            background: linear-gradient(135deg, #E8F5E9 0%, #C8E6C9 100%);
            padding: 25px;
            margin: 10px 15px 10px 0;
            border-radius: 10px;
            border-left: 5px solid #2E7D52;
            min-width: 200px;
            box-shadow: 0 2px 8px rgba(0,0,0,0.1);
        }
        .stat-label {
            font-size: 0.85em;
            color: #1A4731;
            font-weight: 500;
            text-transform: uppercase;
            margin-bottom: 8px;
        }
        .stat-value {
            font-size: 2.2em;
            font-weight: 700;
            color: #1A4731;
        }
        
        /* Barras de progreso */
        .progress-bar {
            width: 100%;
            height: 24px;
            background: #e3e6e8;
            border-radius: 12px;
            overflow: hidden;
            display: inline-flex;
            align-items: center;
            margin: 5px 0;
            font-size: 0.8em;
            font-weight: 600;
            color: white;
        }
        .progress-fill {
            height: 100%;
            display: flex;
            align-items: center;
            justify-content: center;
            background: linear-gradient(90deg, #2E7D52, #4CAF50);
            color: white;
            font-weight: 600;
            padding: 0 8px;
        }
        
        .error-table-critical {
            background: #F8D7DA;
        }
        
        .footer {
            background: #f8f9fa;
            padding: 20px;
            text-align: center;
            color: #666;
            border-top: 1px solid #eee;
        }
        
        .kpi-panel {
            background: linear-gradient(135deg, #E8F5E9 0%, #C8E6C9 100%);
            padding: 30px;
            border-radius: 12px;
            margin-bottom: 30px;
            box-shadow: 0 4px 12px rgba(0,0,0,0.1);
        }
        
        .specialty-row {
            display: flex;
            align-items: center;
            margin: 15px 0;
            gap: 15px;
        }
        
        .specialty-label {
            min-width: 180px;
            font-weight: 600;
            color: #1A4731;
        }
        
        .warning-row {
            background: #FFF3CD !important;
        }
        
        .critical-row {
            background: #F8D7DA !important;
        }
    </style>
    )";
}

std::string HTMLGenerator::getProgressBar(int valor, int maximo) {
    if (maximo == 0) maximo = 1;
    int porcentaje = (valor * 100) / maximo;
    if (porcentaje > 100) porcentaje = 100;
    
    std::stringstream ss;
    ss << "<div class=\"progress-bar\">";
    ss << "<div class=\"progress-fill\" style=\"width: " << porcentaje << "%;\">";
    ss << "";
    for (int i = porcentaje; i < 100; i += 10) {
        ss << "";
    }
    ss << " " << porcentaje << "%";
    ss << "</div></div>";
    return ss.str();
}

std::string HTMLGenerator::getEstadoPaciente(const std::string& nombre) {
    // Contar diagnósticos del paciente
    int diagCount = 0;
    for (const auto& d : data.diagnosticos) {
        if (d.paciente == nombre) diagCount++;
    }
    
    if (diagCount == 0) {
        return "SIN DIAG.";
    } else if (diagCount > 1) {
        return "CRÍTICO";
    } else {
        return "ACTIVO";
    }
}

std::string HTMLGenerator::getColorEstadoPaciente(const std::string& nombre) {
    std::string estado = getEstadoPaciente(nombre);
    if (estado == "ACTIVO") return "estado-activo";
    else if (estado == "CRÍTICO") return "estado-critico";
    else return "estado-sin-diag";
}

std::string HTMLGenerator::getNivelCargaMedico(int citas) {
    if (citas <= 3) return "BAJA";
    else if (citas <= 6) return "NORMAL";
    else if (citas <= 8) return "ALTA";
    else return "SATURADA";
}

std::string HTMLGenerator::getColorCarga(int citas) {
    if (citas <= 3) return "carga-baja";
    else if (citas <= 6) return "carga-normal";
    else if (citas <= 8) return "carga-alta";
    else return "carga-saturada";
}

std::string HTMLGenerator::getEstadoCita(const Cita& cita) {
    if (cita.conflicto) return "CONFLICTO";
    // Aquí se podría añadir lógica para PENDIENTE si la cita es futura
    return "CONFIRMADA";
}

std::string HTMLGenerator::getColorEstadoCita(const Cita& cita) {
    if (cita.conflicto) return "cita-conflicto";
    return "cita-confirmada";
}

bool HTMLGenerator::generarReportePacientes(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    
    file << "<!DOCTYPE html>\n<html lang=\"es\">\n<head>\n";
    file << "<meta charset=\"UTF-8\">\n";
    file << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    file << "<title>Reporte 1 - Historial de Pacientes</title>\n";
    file << getStyleSheet();
    file << "</head>\n<body>\n";
    
    file << "<div class=\"container\">\n";
    file << "<div class=\"header\">\n";
    file << "<h1>REPORTE 1 - HISTORIAL DE PACIENTES</h1>\n";
    file << "<p>Registro completo de todos los pacientes del hospital</p>\n";
    file << "</div>\n";
    
    file << "<div class=\"content\">\n";
    
    // Estadísticas generales
    int conDiag = 0;
    for (const auto& p : data.pacientes) {
        for (const auto& d : data.diagnosticos) {
            if (d.paciente == p.nombre) { conDiag++; break; }
        }
    }
    
    file << "<div class=\"stat-box\">\n";
    file << "<div class=\"stat-label\">Total de Pacientes</div>\n";
    file << "<div class=\"stat-value\">" << data.totalPacientes() << "</div>\n";
    file << "</div>\n";
    
    file << "<div class=\"stat-box\">\n";
    file << "<div class=\"stat-label\">Con Diagnóstico</div>\n";
    file << "<div class=\"stat-value\">" << conDiag << "/" << data.totalPacientes() << "</div>\n";
    file << "</div>\n";
    
    file << "<div class=\"stat-box\">\n";
    file << "<div class=\"stat-label\">Edad Promedio</div>\n";
    file << "<div class=\"stat-value\">" << std::fixed << std::setprecision(1) << data.edadPromedio() << " años</div>\n";
    file << "</div>\n";
    
    file << "<div class=\"section\">\n";
    file << "<h2 class=\"section-title\">Listado de Pacientes</h2>\n";
    file << "<table>\n";
    file << "<thead><tr>\n";
    file << "<th>Paciente</th>\n";
    file << "<th>Edad</th>\n";
    file << "<th>Sangre</th>\n";
    file << "<th>Hab.</th>\n";
    file << "<th>Diagnóstico Activo</th>\n";
    file << "<th>Medicamento / Dosis</th>\n";
    file << "<th>Estado</th>\n";
    file << "</tr></thead>\n<tbody>\n";
    
    for (const auto& p : data.pacientes) {
        file << "<tr>\n";
        file << "<td><strong>" << p.nombre << "</strong></td>\n";
        file << "<td>" << p.edad << "</td>\n";
        file << "<td>" << p.tipoSangre << "</td>\n";
        file << "<td>" << p.habitacion << "</td>\n";
        
        // Buscar diagnóstico
        bool encontrado = false;
        for (const auto& d : data.diagnosticos) {
            if (d.paciente == p.nombre) {
                file << "<td>" << d.condicion << "</td>\n";
                file << "<td>" << d.medicamento << " / " << d.dosis << "</td>\n";
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            file << "<td><em>Sin diagnóstico</em></td>\n";
            file << "<td>—</td>\n";
        }
        
        std::string estado = getEstadoPaciente(p.nombre);
        std::string color = getColorEstadoPaciente(p.nombre);
        file << "<td><span class=\"" << color << "\">" << estado << "</span></td>\n";
        file << "</tr>\n";
    }
    
    file << "</tbody>\n</table>\n";
    file << "</div>\n";
    file << "</div>\n";
    
    file << "<div class=\"footer\">\n";
    file << "Generado automáticamente | Sistema de Gestión Hospitalaria FASE 3\n";
    file << "</div>\n";
    
    file << "</div>\n</body>\n</html>\n";
    file.close();
    return true;
}

bool HTMLGenerator::generarReporteMedicos(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    
    file << "<!DOCTYPE html>\n<html lang=\"es\">\n<head>\n";
    file << "<meta charset=\"UTF-8\">\n";
    file << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    file << "<title>Reporte 2 - Carga de Médicos por Especialidad</title>\n";
    file << getStyleSheet();
    file << "</head>\n<body>\n";
    
    file << "<div class=\"container\">\n";
    file << "<div class=\"header\">\n";
    file << "<h1>REPORTE 2 - CARGA DE MÉDICOS POR ESPECIALIDAD</h1>\n";
    file << "<p>Perfil de médicos y nivel de carga de trabajo</p>\n";
    file << "</div>\n";
    
    file << "<div class=\"content\">\n";
    
    file << "<div class=\"stat-box\">\n";
    file << "<div class=\"stat-label\">Total de Médicos</div>\n";
    file << "<div class=\"stat-value\">" << data.totalMedicos() << "</div>\n";
    file << "</div>\n";
    
    file << "<div class=\"stat-box\">\n";
    file << "<div class=\"stat-label\">Total de Citas</div>\n";
    file << "<div class=\"stat-value\">" << data.totalCitas() << "</div>\n";
    file << "</div>\n";
    
    file << "<div class=\"section\">\n";
    file << "<h2 class=\"section-title\">Médicos y Carga de Trabajo</h2>\n";
    file << "<table>\n";
    file << "<thead><tr>\n";
    file << "<th>Médico</th>\n";
    file << "<th>Código</th>\n";
    file << "<th>Especialidad</th>\n";
    file << "<th>Citas Prog.</th>\n";
    file << "<th>Pacientes Únicos</th>\n";
    file << "<th>% Carga Total</th>\n";
    file << "<th>Nivel de Carga</th>\n";
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
        
        int porciento = (data.totalCitas() > 0) ? (numCitas * 100 / data.totalCitas()) : 0;
        std::string nivel = getNivelCargaMedico(numCitas);
        std::string color = getColorCarga(numCitas);
        
        file << "<tr>\n";
        file << "<td><strong>" << m.nombre << "</strong></td>\n";
        file << "<td>" << m.codigo << "</td>\n";
        file << "<td>" << m.especialidad << "</td>\n";
        file << "<td>" << numCitas << "</td>\n";
        file << "<td>" << pacientesUnicos.size() << "</td>\n";
        file << "<td>" << porciento << "%</td>\n";
        file << "<td><span class=\"" << color << "\">" << nivel << "</span></td>\n";
        file << "</tr>\n";
    }
    
    file << "</tbody>\n</table>\n";
    file << "</div>\n";
    file << "</div>\n";
    
    file << "<div class=\"footer\">\n";
    file << "Umbrales: BAJA (1-3) | NORMAL (4-6) | ALTA (7-8) | SATURADA (9+)\n";
    file << "</div>\n";
    
    file << "</div>\n</body>\n</html>\n";
    file.close();
    return true;
}

bool HTMLGenerator::generarReporteCitas(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    
    // Ordenar citas cronológicamente
    std::vector<Cita> citasOrdenadas = data.citas;
    std::sort(citasOrdenadas.begin(), citasOrdenadas.end(),
        [](const Cita& a, const Cita& b) {
            if (a.fecha != b.fecha) return a.fecha < b.fecha;
            return a.hora < b.hora;
        }
    );
    
    file << "<!DOCTYPE html>\n<html lang=\"es\">\n<head>\n";
    file << "<meta charset=\"UTF-8\">\n";
    file << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    file << "<title>Reporte 3 - Agenda de Citas con Detección de Conflictos</title>\n";
    file << getStyleSheet();
    file << "</head>\n<body>\n";
    
    file << "<div class=\"container\">\n";
    file << "<div class=\"header\">\n";
    file << "<h1>REPORTE 3 - AGENDA DE CITAS</h1>\n";
    file << "<p>Detección automática de conflictos de horario</p>\n";
    file << "</div>\n";
    
    file << "<div class=\"content\">\n";
    
    int conflictos = 0;
    for (const auto& c : citasOrdenadas) {
        if (c.conflicto) conflictos++;
    }
    
    file << "<div class=\"stat-box\">\n";
    file << "<div class=\"stat-label\">Total de Citas</div>\n";
    file << "<div class=\"stat-value\">" << citasOrdenadas.size() << "</div>\n";
    file << "</div>\n";
    
    if (conflictos > 0) {
        file << "<div class=\"stat-box\" style=\"border-left-color: #dc3545;\">\n";
        file << "<div class=\"stat-label\">⚠ CITAS EN CONFLICTO</div>\n";
        file << "<div class=\"stat-value\" style=\"color: #dc3545;\">" << conflictos << "</div>\n";
        file << "</div>\n";
    }
    
    file << "<div class=\"section\">\n";
    file << "<h2 class=\"section-title\">Agenda Cronológica</h2>\n";
    file << "<table>\n";
    file << "<thead><tr>\n";
    file << "<th>Fecha</th>\n";
    file << "<th>Hora</th>\n";
    file << "<th>Paciente</th>\n";
    file << "<th>Médico</th>\n";
    file << "<th>Especialidad</th>\n";
    file << "<th>Estado</th>\n";
    file << "</tr></thead>\n<tbody>\n";
    
    for (const auto& c : citasOrdenadas) {
        // Buscar especialidad del médico
        std::string especialidad = "N/A";
        for (const auto& m : data.medicos) {
            if (m.nombre == c.medico) {
                especialidad = m.especialidad;
                break;
            }
        }
        
        std::string estado = getEstadoCita(c);
        std::string color = getColorEstadoCita(c);
        
        file << "<tr class=\"" << color << "\">\n";
        file << "<td><strong>" << c.fecha << "</strong></td>\n";
        file << "<td>" << c.hora << "</td>\n";
        file << "<td>" << c.paciente << "</td>\n";
        file << "<td>" << c.medico << "</td>\n";
        file << "<td>" << especialidad << "</td>\n";
        file << "<td><span class=\"" << color << "\" style=\"padding: 4px 8px; border-radius: 4px;\">" << estado << "</span></td>\n";
        file << "</tr>\n";
    }
    
    file << "</tbody>\n</table>\n";
    file << "</div>\n";
    file << "</div>\n";
    
    file << "<div class=\"footer\">\n";
    file << "Los conflictos se detectan automáticamente cuando el mismo médico tiene múltiples citas en la misma hora\n";
    file << "</div>\n";
    
    file << "</div>\n</body>\n</html>\n";
    file.close();
    return true;
}

bool HTMLGenerator::generarReporteEstadisticas(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    
    // Calcular estadísticas por especialidad
    std::map<std::string, std::pair<int, std::set<std::string>>> especialidades;
    
    for (const auto& m : data.medicos) {
        int citasDelMedico = 0;
        std::set<std::string> pacientes;
        
        for (const auto& c : data.citas) {
            if (c.medico == m.nombre) {
                citasDelMedico++;
                pacientes.insert(c.paciente);
            }
        }
        
        if (especialidades.find(m.especialidad) == especialidades.end()) {
            especialidades[m.especialidad] = {0, {}};
        }
        especialidades[m.especialidad].first += citasDelMedico;
        for (const auto& p : pacientes) {
            especialidades[m.especialidad].second.insert(p);
        }
    }
    
    file << "<!DOCTYPE html>\n<html lang=\"es\">\n<head>\n";
    file << "<meta charset=\"UTF-8\">\n";
    file << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    file << "<title>Reporte 4 - Estadísticas Generales</title>\n";
    file << getStyleSheet();
    file << "</head>\n<body>\n";
    
    file << "<div class=\"container\">\n";
    file << "<div class=\"header\">\n";
    file << "<h1>REPORTE 4 - ESTADÍSTICAS GENERALES</h1>\n";
    file << "<p>Indicadores clave (KPIs) del hospital</p>\n";
    file << "</div>\n";
    
    file << "<div class=\"content\">\n";
    
    // SECCIÓN A: KPIs
    file << "<div class=\"section\">\n";
    file << "<h2 class=\"section-title\">Sección A - Panel de Indicadores Clave (KPIs)</h2>\n";
    
    // Calcular medicamento más prescrito
    std::map<std::string, int> medicamentos;
    for (const auto& d : data.diagnosticos) {
        medicamentos[d.medicamento]++;
    }
    std::string medMasPrescrito = "N/A";
    int maxMed = 0;
    for (const auto& m : medicamentos) {
        if (m.second > maxMed) {
            maxMed = m.second;
            medMasPrescrito = m.first + " (" + std::to_string(m.second) + " pacientes)";
        }
    }
    
    // Contar conflictos
    int conflictos = 0;
    for (const auto& c : data.citas) {
        if (c.conflicto) conflictos++;
    }
    
    // Contar pacientes con diagnóstico
    int pacientesConDiag = 0;
    for (const auto& p : data.pacientes) {
        for (const auto& d : data.diagnosticos) {
            if (d.paciente == p.nombre) {
                pacientesConDiag++;
                break;
            }
        }
    }

    // Especialidad y médico con mayor carga de citas
    std::map<std::string, int> citasPorMedico;
    for (const auto& c : data.citas) {
        citasPorMedico[c.medico]++;
    }

    std::string especialidadMayorCarga = "N/A";
    std::string medicoMayorCarga = "N/A";
    int maxCitasEspecialidad = 0;
    int maxCitasMedico = 0;

    for (const auto& espec : especialidades) {
        int citasEspec = espec.second.first;
        if (citasEspec > maxCitasEspecialidad) {
            maxCitasEspecialidad = citasEspec;
            especialidadMayorCarga = espec.first;
        }
    }

    for (const auto& med : data.medicos) {
        if (med.especialidad == especialidadMayorCarga) {
            int citasMed = citasPorMedico[med.nombre];
            if (citasMed > maxCitasMedico) {
                maxCitasMedico = citasMed;
                medicoMayorCarga = med.nombre;
            }
        }
    }

    file << "<div class=\"kpi-panel\">\n";
    file << "<table style=\"width: auto;\">\n";
    
    file << "<tr><td><strong>Total de pacientes registrados</strong></td><td style=\"text-align: right; font-size: 1.3em; font-weight: 700; color: #1A4731;\">" << data.totalPacientes() << "</td></tr>\n";
    file << "<tr><td><strong>Total de médicos activos</strong></td><td style=\"text-align: right; font-size: 1.3em; font-weight: 700; color: #1A4731;\">" << data.totalMedicos() << "</td></tr>\n";
    file << "<tr><td><strong>Total de citas programadas</strong></td><td style=\"text-align: right; font-size: 1.3em; font-weight: 700; color: #1A4731;\">" << data.totalCitas() << "</td></tr>\n";
    file << "<tr><td><strong>Citas con conflicto de horario</strong></td><td style=\"text-align: right; font-size: 1.3em; font-weight: 700; color: #dc3545;\">" << conflictos << "</td></tr>\n";
    file << "<tr><td><strong>Pacientes con diagnóstico activo</strong></td><td style=\"text-align: right; font-size: 1.3em; font-weight: 700; color: #1A4731;\">" << pacientesConDiag << " de " << data.totalPacientes() << " (" << (data.totalPacientes() > 0 ? (pacientesConDiag * 100 / data.totalPacientes()) : 0) << "%)</td></tr>\n";
    file << "<tr><td><strong>Medicamento más prescrito</strong></td><td style=\"text-align: right; font-size: 1.1em; font-weight: 600; color: #1A4731;\">" << medMasPrescrito << "</td></tr>\n";
    file << "<tr><td><strong>Especialidad con mayor carga de citas</strong></td><td style=\"text-align: right; font-size: 1.1em; font-weight: 600; color: #2E7D52;\">" << especialidadMayorCarga << " (" << maxCitasEspecialidad << " citas)</td></tr>\n";
    file << "<tr><td><strong>Médico con mayor carga de citas</strong></td><td style=\"text-align: right; font-size: 1.1em; font-weight: 600; color: #2E7D52;\">" << medicoMayorCarga << " (" << maxCitasMedico << " citas)</td></tr>\n";
    file << "<tr><td><strong>Promedio de edad de pacientes</strong></td><td style=\"text-align: right; font-size: 1.3em; font-weight: 700; color: #1A4731;\">" << std::fixed << std::setprecision(1) << data.edadPromedio() << " años</td></tr>\n";
    
    file << "</table>\n";
    file << "</div>\n";
    file << "</div>\n";
    
    // SECCIÓN B: Distribución de especialidades
    file << "<div class=\"section\">\n";
    file << "<h2 class=\"section-title\">Sección B - Distribución de Carga por Especialidad</h2>\n";
    file << "<table>\n";
    file << "<thead><tr>\n";
    file << "<th>Especialidad</th>\n";
    file << "<th>Médicos</th>\n";
    file << "<th>Citas</th>\n";
    file << "<th>Pacientes</th>\n";
    file << "<th>Barra de Ocupación</th>\n";
    file << "</tr></thead>\n<tbody>\n";
    
    int totalCitas = data.totalCitas();
    
    for (const auto& espec : especialidades) {
        int citasEspec = espec.second.first;
        int pacientesEspec = espec.second.second.size();
        int medicos = 0;
        for (const auto& m : data.medicos) {
            if (m.especialidad == espec.first) medicos++;
        }
        
        int porcentaje = (totalCitas > 0) ? (citasEspec * 100 / totalCitas) : 0;
        
        std::string rowClass = "";
        if (porcentaje > 80) {
            rowClass = " class=\"warning-row\"";
        }
        
        file << "<tr" << rowClass << ">\n";
        file << "<td><strong>" << espec.first << "</strong></td>\n";
        file << "<td>" << medicos << "</td>\n";
        file << "<td>" << citasEspec << "</td>\n";
        file << "<td>" << pacientesEspec << "</td>\n";
        file << "<td>" << getProgressBar(citasEspec, totalCitas) << "</td>\n";
        file << "</tr>\n";
    }
    
    file << "</tbody>\n</table>\n";
    file << "</div>\n";
    
    file << "</div>\n";
    
    file << "<div class=\"footer\">\n";
    file << "Alerta: Especialidades con ocupación > 80% están marcadas en naranja\n";
    file << "</div>\n";
    
    file << "</div>\n</body>\n</html>\n";
    file.close();
    return true;
}

bool HTMLGenerator::generarReporteErrores(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    
    file << "<!DOCTYPE html>\n<html lang=\"es\">\n<head>\n";
    file << "<meta charset=\"UTF-8\">\n";
    file << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    file << "<title>Tabla de Errores Léxicos</title>\n";
    file << getStyleSheet();
    file << "</head>\n<body>\n";
    
    file << "<div class=\"container\">\n";
    file << "<div class=\"header\">\n";
    file << "<h1>TABLA DE ERRORES LÉXICOS</h1>\n";
    file << "<p>Errores encontrados durante el análisis léxico</p>\n";
    file << "</div>\n";
    
    file << "<div class=\"content\">\n";
    
    if (!errMgr || !errMgr->hasErrors()) {
        file << "<div class=\"stat-box\" style=\"border-left-color: #28a745;\">\n";
        file << "<div class=\"stat-label\">✓ Sin errores</div>\n";
        file << "<div class=\"stat-value\" style=\"color: #28a745;\">0</div>\n";
        file << "</div>\n";
        file << "<p style=\"margin-top: 20px; font-size: 1.1em; color: #333;\">El archivo fue procesado sin errores léxicos.</p>\n";
    } else {
        const auto& errors = errMgr->getErrors();
        
        file << "<div class=\"stat-box\" style=\"border-left-color: #dc3545;\">\n";
        file << "<div class=\"stat-label\">Total de Errores</div>\n";
        file << "<div class=\"stat-value\" style=\"color: #dc3545;\">" << errors.size() << "</div>\n";
        file << "</div>\n";
        
        file << "<div class=\"section\">\n";
        file << "<table>\n";
        file << "<thead><tr>\n";
        file << "<th>No.</th>\n";
        file << "<th>Lexema</th>\n";
        file << "<th>Tipo de Error</th>\n";
        file << "<th>Descripción</th>\n";
        file << "<th>Línea</th>\n";
        file << "<th>Columna</th>\n";
        file << "<th>Gravedad</th>\n";
        file << "</tr></thead>\n<tbody>\n";
        
        for (const auto& err : errors) {
            std::string rowClass = (err.severity == "CRÍTICO") ? " class=\"error-table-critical\"" : "";
            
            file << "<tr" << rowClass << ">\n";
            file << "<td>" << err.id << "</td>\n";
            file << "<td><code>\"" << err.lexeme << "\"</code></td>\n";
            file << "<td>" << err.errorType << "</td>\n";
            file << "<td>" << err.description << "</td>\n";
            file << "<td>" << err.line << "</td>\n";
            file << "<td>" << err.column << "</td>\n";
            file << "<td><strong>" << err.severity << "</strong></td>\n";
            file << "</tr>\n";
        }
        
        file << "</tbody>\n</table>\n";
        file << "</div>\n";
    }
    
    file << "</div>\n";
    
    file << "<div class=\"footer\">\n";
    file << "Análisis léxico completo | Recuperación de errores habilitada\n";
    file << "</div>\n";
    
    file << "</div>\n</body>\n</html>\n";
    file.close();
    return true;
}

bool HTMLGenerator::generarReporteCompleto(const std::string& filename) {
    // Generar todos los reportes
    std::string base = filename.substr(0, filename.find_last_of("."));
    std::string ext = filename.substr(filename.find_last_of("."));
    
    generarReportePacientes(base + "_1_pacientes" + ext);
    generarReporteMedicos(base + "_2_medicos" + ext);
    generarReporteCitas(base + "_3_citas" + ext);
    generarReporteEstadisticas(base + "_4_estadisticas" + ext);
    
    if (errMgr) {
        generarReporteErrores(base + "_5_errores" + ext);
    }
    
    return true;
}
