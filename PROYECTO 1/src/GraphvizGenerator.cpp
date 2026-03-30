#include "GraphvizGenerator.h"
#include <fstream>
#include <sstream>
#include <algorithm>

GraphvizGenerator::GraphvizGenerator(const RegistroHospitalario& registros) : data(registros) {}

bool GraphvizGenerator::generarGrafo(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    
    file << "digraph Hospital {\n";
    file << "  rankdir=LR;\n";
    file << "  node [shape=box, style=rounded, color=\"#667eea\", fontname=\"Arial\"];\n";
    file << "  edge [color=\"#666\", fontname=\"Arial\"];\n\n";
    
    // Nodo hospital central
    file << "  hospital [label=\"\nHOSPITAL\", shape=ellipse, color=\"#ff6b6b\", fontcolor=white, style=filled];\n\n";
    
    // Nodos de Pacientes
    file << "  subgraph cluster_pacientes {\n";
    file << "    label=\"PACIENTES\";\n";
    file << "    color=\"#4ecdc4\";\n";
    file << "    style=filled;\n";
    file << "    fillcolor=\"#e8f8f5\";\n";
    
    for (const auto& p : data.pacientes) {
        std::string nodeName = "pac_" + std::to_string(std::hash<std::string>{}(p.nombre) % 10000);
        file << "    " << nodeName << " [label=\"\\n" << p.nombre << "\\nEdad: " << p.edad << "\\nSangre: " << p.tipoSangre << "\"];\n";
        file << "    hospital -> " << nodeName << ";\n";
    }
    file << "  }\n\n";
    
    // Nodos de Médicos
    file << "  subgraph cluster_medicos {\n";
    file << "    label=\"MÉDICOS\";\n";
    file << "    color=\"#95e1d3\";\n";
    file << "    style=filled;\n";
    file << "    fillcolor=\"#f0fdf4\";\n";
    
    for (const auto& m : data.medicos) {
        std::string nodeName = "med_" + std::to_string(std::hash<std::string>{}(m.nombre) % 10000);
        file << "    " << nodeName << " [label=\"\\n" << m.nombre << "\\n" << m.especialidad << "\\n" << m.codigo << "\"];\n";
        file << "    hospital -> " << nodeName << ";\n";
    }
    file << "  }\n\n";
    
    // Relaciones de Citas (conexiones entre pacientes y médicos)
    file << "  subgraph cluster_citas {\n";
    file << "    label=\"CITAS\";\n";
    file << "    color=\"transparent\";\n";
    
    for (const auto& c : data.citas) {
        std::string pacNode = "pac_" + std::to_string(std::hash<std::string>{}(c.paciente) % 10000);
        std::string medNode = "med_" + std::to_string(std::hash<std::string>{}(c.medico) % 10000);
        
        std::string label = c.fecha + " " + c.hora;
        std::string color = c.conflicto ? "red" : "green";
        std::string style = c.conflicto ? "bold" : "solid";
        
        file << "    " << pacNode << " -> " << medNode << " [label=\"" << label << "\", color=\"" << color << "\", style=\"" << style << "\"];\n";
    }
    file << "  }\n\n";
    
    // Especialidades (información adicional)
    file << "  subgraph cluster_especialidades {\n";
    file << "    label=\"ESPECIALIDADES\";\n";
    file << "    color=\"#ffeaa7\";\n";
    file << "    style=filled;\n";
    file << "    fillcolor=\"#fffaed\";\n";
    
    std::vector<std::string> especialidades;
    for (const auto& m : data.medicos) {
        if (std::find(especialidades.begin(), especialidades.end(), m.especialidad) == especialidades.end()) {
            especialidades.push_back(m.especialidad);
            std::string nodeId = "esp_" + std::to_string(std::hash<std::string>{}(m.especialidad) % 10000);
            file << "    " << nodeId << " [label=\"" << m.especialidad << "\"];\n";
        }
    }
    file << "  }\n\n";
    
    // Tipos de Sangre (información adicional)
    file << "  subgraph cluster_sangre {\n";
    file << "    label=\"TIPOS DE SANGRE\";\n";
    file << "    color=\"#ff7675\";\n";
    file << "    style=filled;\n";
    file << "    fillcolor=\"#ffebee\";\n";
    
    std::vector<std::string> tiposSangre;
    for (const auto& p : data.pacientes) {
        if (std::find(tiposSangre.begin(), tiposSangre.end(), p.tipoSangre) == tiposSangre.end()) {
            tiposSangre.push_back(p.tipoSangre);
            std::string nodeId = "sangre_" + std::to_string(std::hash<std::string>{}(p.tipoSangre) % 10000);
            file << "    " << nodeId << " [label=\"" << p.tipoSangre << "\", shape=oval];\n";
        }
    }
    file << "  }\n\n";
    
    file << "  // Leyenda\n";
    file << "  subgraph cluster_legend {\n";
    file << "    label=\"Leyenda\";\n";
    file << "    color=\"gray\";\n";
    file << "    ok_edge [label=\"Cita OK\", color=\"green\"];\n";
    file << "    conflict_edge [label=\"Cita en conflicto\", color=\"red\"];\n";
    file << "  }\n";
    
    file << "}\n";
    
    file.close();
    return true;
}
