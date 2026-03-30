#ifndef GRAPHVIZGENERATOR_H
#define GRAPHVIZGENERATOR_H

#include "DataStructures.h"
#include <string>

class GraphvizGenerator {
private:
    const RegistroHospitalario& data;
    
public:
    GraphvizGenerator(const RegistroHospitalario& registros);
    
    bool generarGrafo(const std::string& filename);
};

#endif // GRAPHVIZGENERATOR_H
