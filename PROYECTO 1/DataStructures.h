#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <string>
#include <vector>
#include <map>

// Estructura para Paciente
struct Paciente {
    std::string nombre;
    int edad = 0;
    std::string tipoSangre;
    int habitacion = 0;
    std::string diagnostico;
    std::string medicamento;
    std::string dosis;
    std::string condicion;
    
    std::string toString() const {
        return nombre + " (Edad: " + std::to_string(edad) + ", Sangre: " + tipoSangre + ")";
    }
};

// Estructura para Médico
struct Medico {
    std::string nombre;
    std::string especialidad;
    std::string codigo;
    std::vector<std::string> citasAgendadas; // Nombres de pacientes
    
    std::string toString() const {
        return nombre + " (" + especialidad + ") [" + codigo + "]";
    }
};

// Estructura para Cita
struct Cita {
    std::string paciente;
    std::string medico;
    std::string fecha;   // YYYY-MM-DD
    std::string hora;    // HH:MM
    bool conflicto = false;
    std::vector<std::string> conflictoCon; // Otras citas en conflicto
    
    std::string toString() const {
        return paciente + " -> " + medico + " [" + fecha + " " + hora + "]";
    }
};

// Estructura para Diagnóstico
struct Diagnostico {
    std::string paciente;
    std::string condicion;
    std::string medicamento;
    std::string dosis;
    
    std::string toString() const {
        return paciente + ": " + condicion + " - " + medicamento;
    }
};

// Contenedor principal de datos
class RegistroHospitalario {
public:
    std::vector<Paciente> pacientes;
    std::vector<Medico> medicos;
    std::vector<Cita> citas;
    std::vector<Diagnostico> diagnosticos;
    
    // Búsquedas por nombre
    Paciente* buscarPaciente(const std::string& nombre);
    Medico* buscarMedico(const std::string& nombre);
    
    // Estadísticas
    int totalPacientes() const { return pacientes.size(); }
    int totalMedicos() const { return medicos.size(); }
    int totalCitas() const { return citas.size(); }
    double edadPromedio() const;
    
    void clear();
};

#endif // DATASTRUCTURES_H
