#ifndef HTMLGENERATOR_H
#define HTMLGENERATOR_H

#include "DataStructures.h"
#include <string>
#include <fstream>

class HTMLGenerator {
private:
    const RegistroHospitalario& data;
    
    std::string getStyleSheet();
    
public:
    HTMLGenerator(const RegistroHospitalario& registros);
    
    bool generarReportePacientes(const std::string& filename);
    bool generarReporteMedicos(const std::string& filename);
    bool generarReporteCitas(const std::string& filename);
    bool generarReporteEstadisticas(const std::string& filename);
    bool generarReporteCompleto(const std::string& filename);
};

#endif // HTMLGENERATOR_H
