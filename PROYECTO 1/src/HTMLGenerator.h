#ifndef HTMLGENERATOR_H
#define HTMLGENERATOR_H

#include "DataStructures.h"
#include "ErrorManager.h"
#include <string>
#include <fstream>
#include <vector>

class HTMLGenerator {
private:
    const RegistroHospitalario& data;
    const ErrorManager* errMgr;
    
    std::string getStyleSheet();
    std::string getProgressBar(int valor, int maximo);
    std::string getEstadoPaciente(const std::string& nombre);
    std::string getColorEstadoPaciente(const std::string& nombre);
    std::string getNivelCargaMedico(int citas);
    std::string getColorCarga(int citas);
    std::string getEstadoCita(const Cita& cita);
    std::string getColorEstadoCita(const Cita& cita);
    
public:
    HTMLGenerator(const RegistroHospitalario& registros, const ErrorManager* errManager = nullptr);
    
    // Reportes especificados en la tarea
    bool generarReportePacientes(const std::string& filename);        // Reporte 1
    bool generarReporteMedicos(const std::string& filename);          // Reporte 2
    bool generarReporteCitas(const std::string& filename);            // Reporte 3
    bool generarReporteEstadisticas(const std::string& filename);     // Reporte 4
    bool generarReporteErrores(const std::string& filename);          // Tabla de errores
    
    bool generarReporteCompleto(const std::string& filename);
};

#endif // HTMLGENERATOR_H
