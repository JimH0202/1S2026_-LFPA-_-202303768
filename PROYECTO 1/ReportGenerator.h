#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include "DataStructures.h"
#include "Token.h"
#include <vector>
#include <string>
#include <map>

class ReportGenerator {
private:
    RegistroHospitalario data;
    
    void extraerDatos(const std::vector<Token>& tokens);
    void detectarConflictosCitas();
    
public:
    ReportGenerator();
    
    void procesarTokens(const std::vector<Token>& tokens);
    
    // Reportes
    std::string generarReportePacientes();
    std::string generarReporteMedicos();
    std::string generarReporteCitas();
    std::string generarReporteEstadisticas();
    
    // Acceso a datos
    const RegistroHospitalario& getDatos() const { return data; }
};

#endif // REPORTGENERATOR_H
