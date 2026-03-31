#include "ReportGenerator.h"
#include <sstream>
#include <algorithm>
#include <iostream>

ReportGenerator::ReportGenerator() {}

void ReportGenerator::procesarTokens(const std::vector<Token>& tokens) {
    data.clear();
    extraerDatos(tokens);
    detectarConflictosCitas();
}

void ReportGenerator::extraerDatos(const std::vector<Token>& tokens) {
    int i = 0;
    while (i < tokens.size()) {
        const Token& tok = tokens[i];
        
        // Buscar sección PACIENTES
        if (tok.type == TokenType::PACIENTES) {
            i++;
            while (i < tokens.size() && tokens[i].type != TokenType::MEDICOS) {
                if (tokens[i].lexeme == "paciente" && i + 2 < tokens.size()) {
                    Paciente p;
                    // Saltar ":" y parsear STRING con nombre
                    if (tokens[i + 1].type == TokenType::SYMBOL && tokens[i + 1].lexeme == ":") {
                        i += 2;
                        if (tokens[i].type == TokenType::STRING) {
                            p.nombre = tokens[i].lexeme;
                            p.nombre = p.nombre.substr(1, p.nombre.length() - 2); // Quitar comillas
                        }
                    }
                    
                    // Buscar edad, tipo_sangre, habitacion
                    i++;
                    while (i < tokens.size() && tokens[i].lexeme != "paciente" && tokens[i].type != TokenType::MEDICOS) {
                        if (tokens[i].lexeme == "edad" && i + 2 < tokens.size() && tokens[i + 1].type == TokenType::SYMBOL) {
                            if (tokens[i + 2].type == TokenType::INTEGER) {
                                p.edad = std::stoi(tokens[i + 2].lexeme);
                                i += 2;
                            }
                        } else if (tokens[i].lexeme == "tipo_sangre" && i + 2 < tokens.size()) {
                            if (i + 2 < tokens.size() && tokens[i + 2].type == TokenType::STRING) {
                                p.tipoSangre = tokens[i + 2].lexeme;
                                p.tipoSangre = p.tipoSangre.substr(1, p.tipoSangre.length() - 2);
                                i += 2;
                            }
                        } else if (tokens[i].lexeme == "habitacion" && i + 2 < tokens.size()) {
                            if (tokens[i + 2].type == TokenType::INTEGER) {
                                p.habitacion = std::stoi(tokens[i + 2].lexeme);
                                i += 2;
                            }
                        }
                        i++;
                    }
                    i--;
                    data.pacientes.push_back(p);
                }
                i++;
            }
            // NO hacer i++, porque i ya está en MEDICOS
            continue;
        }
        
        // Buscar sección MEDICOS
        else if (tokens[i].type == TokenType::MEDICOS) {
            i++;
            while (i < tokens.size() && tokens[i].type != TokenType::CITAS) {
                if (tokens[i].lexeme == "medico" && i + 2 < tokens.size()) {
                    Medico m;
                    if (tokens[i + 1].type == TokenType::SYMBOL && tokens[i + 1].lexeme == ":") {
                        i += 2;
                        if (tokens[i].type == TokenType::STRING) {
                            m.nombre = tokens[i].lexeme;
                            m.nombre = m.nombre.substr(1, m.nombre.length() - 2);
                        }
                    }
                    
                    i++;
                    while (i < tokens.size() && tokens[i].lexeme != "medico" && tokens[i].type != TokenType::CITAS) {
                        if (tokens[i].lexeme == "especialidad" && i + 2 < tokens.size() && tokens[i + 2].type == TokenType::SPECIALTY) {
                            m.especialidad = tokens[i + 2].lexeme;
                            i += 2;
                        } else if (tokens[i].lexeme == "codigo" && i + 2 < tokens.size()) {
                            if (tokens[i + 2].type == TokenType::STRING) {
                                m.codigo = tokens[i + 2].lexeme;
                                m.codigo = m.codigo.substr(1, m.codigo.length() - 2);
                                i += 2;
                            }
                        }
                        i++;
                    }
                    i--;
                    data.medicos.push_back(m);
                }
                i++;
            }
            // NO hacer i++, porque i ya está en MEDICOS o CITAS
            continue;
        }
        
        // Buscar sección CITAS
        else if (tokens[i].type == TokenType::CITAS) {
            i++;
            while (i < tokens.size() && tokens[i].type != TokenType::DIAGNOSTICOS && tokens[i].lexeme != "}") {
                if (tokens[i].lexeme == "cita" && i + 2 < tokens.size()) {
                    Cita c;
                    if (tokens[i + 1].type == TokenType::SYMBOL && tokens[i + 1].lexeme == ":") {
                        i += 2;
                        if (tokens[i].type == TokenType::STRING) {
                            c.paciente = tokens[i].lexeme;
                            c.paciente = c.paciente.substr(1, c.paciente.length() - 2);
                        }
                    }
                    
                    i++;
                    while (i < tokens.size() && tokens[i].lexeme != "cita" && tokens[i].type != TokenType::DIAGNOSTICOS && tokens[i].lexeme != "}") {
                        if (tokens[i].lexeme == "con" && i + 1 < tokens.size()) {
                            i++;
                            if (tokens[i].type == TokenType::STRING) {
                                c.medico = tokens[i].lexeme;
                                c.medico = c.medico.substr(1, c.medico.length() - 2);
                            }
                        } else if (tokens[i].lexeme == "fecha" && i + 2 < tokens.size() && tokens[i + 2].type == TokenType::DATE) {
                            c.fecha = tokens[i + 2].lexeme;
                            i += 2;
                        } else if (tokens[i].lexeme == "hora" && i + 2 < tokens.size() && tokens[i + 2].type == TokenType::TIME) {
                            c.hora = tokens[i + 2].lexeme;
                            i += 2;
                        }
                        i++;
                    }
                    i--;
                    if (!c.paciente.empty() && !c.medico.empty() && !c.fecha.empty() && !c.hora.empty()) {
                        data.citas.push_back(c);
                    }
                }
                i++;
            }
            // NO hacer i++, porque i ya está en DIAGNOSTICOS o cierre
            continue;
        }
        
        // Buscar sección DIAGNOSTICOS
        else if (tokens[i].type == TokenType::DIAGNOSTICOS) {
            i++;
            while (i < tokens.size() && tokens[i].lexeme != "}") {
                if (tokens[i].lexeme == "diagnostico" && i + 2 < tokens.size()) {
                    Diagnostico d;
                    if (tokens[i + 1].type == TokenType::SYMBOL && tokens[i + 1].lexeme == ":") {
                        i += 2;
                        if (tokens[i].type == TokenType::STRING) {
                            d.paciente = tokens[i].lexeme;
                            d.paciente = d.paciente.substr(1, d.paciente.length() - 2);
                        }
                    }
                    
                    i++;
                    while (i < tokens.size() && tokens[i].lexeme != "diagnostico" && tokens[i].lexeme != "}") {
                        if (tokens[i].lexeme == "condicion" && i + 2 < tokens.size() && tokens[i + 2].type == TokenType::STRING) {
                            d.condicion = tokens[i + 2].lexeme;
                            d.condicion = d.condicion.substr(1, d.condicion.length() - 2);
                            i += 2;
                        } else if (tokens[i].lexeme == "medicamento" && i + 2 < tokens.size() && tokens[i + 2].type == TokenType::STRING) {
                            d.medicamento = tokens[i + 2].lexeme;
                            d.medicamento = d.medicamento.substr(1, d.medicamento.length() - 2);
                            i += 2;
                        } else if (tokens[i].lexeme == "dosis" && i + 2 < tokens.size() && tokens[i + 2].type == TokenType::DOSIS) {
                            d.dosis = tokens[i + 2].lexeme;
                            i += 2;
                        }
                        i++;
                    }
                    if (!d.paciente.empty()) {
                        data.diagnosticos.push_back(d);
                    }
                    i--;
                }
                i++;
            }
            // NO hacer i++, porque ya estamos en cierre
            continue;
        }
        
        i++;
    }
}

void ReportGenerator::detectarConflictosCitas() {
    for (size_t i = 0; i < data.citas.size(); ++i) {
        for (size_t j = i + 1; j < data.citas.size(); ++j) {
            if (data.citas[i].medico == data.citas[j].medico &&
                data.citas[i].fecha == data.citas[j].fecha &&
                data.citas[i].hora == data.citas[j].hora) {
                data.citas[i].conflicto = true;
                data.citas[j].conflicto = true;
                data.citas[i].conflictoCon.push_back(data.citas[j].paciente);
                data.citas[j].conflictoCon.push_back(data.citas[i].paciente);
            }
        }
    }
}

std::string ReportGenerator::generarReportePacientes() {
    std::stringstream ss;
    ss << "=== REPORTE DE PACIENTES ===\n\n";
    ss << "Total de Pacientes: " << data.totalPacientes() << "\n";
    ss << "Edad Promedio: " << data.edadPromedio() << " años\n\n";
    ss << "Detalle:\n";
    ss << std::string(100, '-') << "\n";
    
    for (const auto& p : data.pacientes) {
        ss << "Nombre: " << p.nombre << "\n";
        ss << "  Edad: " << p.edad << " años\n";
        ss << "  Tipo de Sangre: " << p.tipoSangre << "\n";
        ss << "  Habitación: " << p.habitacion << "\n";
        
        for (const auto& d : data.diagnosticos) {
            if (d.paciente == p.nombre) {
                ss << "  Diagnóstico: " << d.condicion << "\n";
                ss << "  Medicamento: " << d.medicamento << " (" << d.dosis << ")\n";
            }
        }
        ss << "\n";
    }
    
    return ss.str();
}

std::string ReportGenerator::generarReporteMedicos() {
    std::stringstream ss;
    ss << "=== REPORTE DE MÉDICOS ===\n\n";
    ss << "Total de Médicos: " << data.totalMedicos() << "\n\n";
    ss << "Detalle:\n";
    ss << std::string(100, '-') << "\n";
    
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
        
        ss << "Nombre: " << m.nombre << "\n";
        ss << "  Especialidad: " << m.especialidad << "\n";
        ss << "  Código: " << m.codigo << "\n";
        ss << "  Citas Agendadas: " << numCitas << "\n";
        ss << "  Pacientes Atendidos: " << pacientesUnicos.size() << "\n";
        ss << "  Carga Promedio: " << (data.totalCitas() > 0 ? (numCitas * 100 / data.totalCitas()) : 0) << "%\n";
        ss << "\n";
    }
    
    return ss.str();
}

std::string ReportGenerator::generarReporteCitas() {
    std::stringstream ss;
    ss << "=== REPORTE DE CITAS ===\n\n";
    ss << "Total de Citas: " << data.totalCitas() << "\n";
    
    int conflictos = 0;
    for (const auto& c : data.citas) {
        if (c.conflicto) conflictos++;
    }
    ss << "Citas en Conflicto: " << conflictos << "\n\n";
    
    ss << "Listado de Citas:\n";
    ss << std::string(100, '-') << "\n";
    
    for (const auto& c : data.citas) {
        ss << "Paciente: " << c.paciente << "\n";
        ss << "  Médico: " << c.medico << "\n";
        ss << "  Fecha: " << c.fecha << " " << c.hora << "\n";
        if (c.conflicto) {
            ss << " X CONFLICTO: Coincide con cita(s) de ";
            for (const auto& conf : c.conflictoCon) {
                ss << conf << ", ";
            }
            ss << "\n";
        }
        ss << "\n";
    }
    
    return ss.str();
}

std::string ReportGenerator::generarReporteEstadisticas() {
    std::stringstream ss;
    ss << "=== ESTADÍSTICAS GENERALES ===\n\n";
    ss << "CANTIDAD:\n";
    ss << "  Pacientes: " << data.totalPacientes() << "\n";
    ss << "  Médicos: " << data.totalMedicos() << "\n";
    ss << "  Especialidades: " << data.medicos.size() << "\n";
    ss << "  Citas: " << data.totalCitas() << "\n";
    ss << "  Diagnósticos: " << data.diagnosticos.size() << "\n\n";
    
    ss << "PROMEDIOS:\n";
    ss << "  Edad Promedio Pacientes: " << data.edadPromedio() << " años\n";
    ss << "  Citas por Médico: " << (data.totalMedicos() > 0 ? (data.totalCitas() / data.totalMedicos()) : 0) << "\n\n";
    
    ss << "DISTRIBUCIÓN:\n";
    std::map<std::string, int> especialidades;
    for (const auto& m : data.medicos) {
        especialidades[m.especialidad]++;
    }
    for (const auto& e : especialidades) {
        ss << "  " << e.first << ": " << e.second << " (" << (e.second * 100 / data.totalMedicos()) << "%)\n";
    }
    
    ss << "\nDISTRIBUCIÓN TIPOS SANGRE:\n";
    std::map<std::string, int> sangres;
    for (const auto& p : data.pacientes) {
        sangres[p.tipoSangre]++;
    }
    for (const auto& s : sangres) {
        ss << "  " << s.first << ": " << s.second << " (" << (data.totalPacientes() > 0 ? (s.second * 100 / data.totalPacientes()) : 0) << "%)\n";
    }
    
    return ss.str();
}
