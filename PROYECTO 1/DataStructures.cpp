#include "DataStructures.h"

Paciente* RegistroHospitalario::buscarPaciente(const std::string& nombre) {
    for (auto& p : pacientes) {
        if (p.nombre == nombre) return &p;
    }
    return nullptr;
}

Medico* RegistroHospitalario::buscarMedico(const std::string& nombre) {
    for (auto& m : medicos) {
        if (m.nombre == nombre) return &m;
    }
    return nullptr;
}

double RegistroHospitalario::edadPromedio() const {
    if (pacientes.empty()) return 0.0;
    int suma = 0;
    for (const auto& p : pacientes) {
        suma += p.edad;
    }
    return suma / static_cast<double>(pacientes.size());
}

void RegistroHospitalario::clear() {
    pacientes.clear();
    medicos.clear();
    citas.clear();
    diagnosticos.clear();
}
