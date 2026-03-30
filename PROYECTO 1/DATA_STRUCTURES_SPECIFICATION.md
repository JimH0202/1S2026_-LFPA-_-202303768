# Especificación de Estructuras de Datos - FASE 3

**Documento:** API de Datos Hospitalarios  
**Versión:** 1.0  
**Fecha:** 2026

---

## Tabla de Contenidos
1. [Estructuras Base](#estructuras-base)
2. [Clase Principal](#clase-principal)
3. [Métodos Disponibles](#métodos-disponibles)
4. [Relaciones](#relaciones)
5. [Ejemplo de Uso](#ejemplo-de-uso)

---

## Estructuras Base

### 1. Paciente

```cpp
struct Paciente {
    string nombre;           // Nombre completo del paciente
    int edad;               // Edad en años (0-150)
    string tipo_sangre;     // Tipo: O+, O-, A+, A-, B+, B-, AB+, AB-
    int habitacion;         // Número de habitación
    string diagnostico;     // Diagnóstico principal
    string estado;          // Estado: Estable, Crítico, Recuperación, Alta
};
```

**Validaciones:**
- `nombre`: Válido entre comillas, 1-100 caracteres
- `edad`: Número entero 0-150
- `tipo_sangre`: O+, O-, A+, A-, B+, B-, AB+, AB-
- `habitacion`: Número entero > 0
- `diagnostico`: Válido entre comillas
- `estado`: Estable, Crítico, Recuperación, Alta

**Ejemplo JSON:**
```json
{
  "nombre": "Juan García Martínez",
  "edad": 45,
  "tipo_sangre": "O+",
  "habitacion": 101,
  "diagnostico": "Hipertensión",
  "estado": "Estable"
}
```

---

### 2. Médico

```cpp
struct Medico {
    string nombre;              // Nombre completo
    string especialidad;        // Especialidad médica
    string codigo;              // Código único (e.g., M001)
    int pacientes_atendidos;    // Número de pacientes en cuidado
    int citas_totales;          // Total de citas realizadas
};
```

**Validaciones:**
- `nombre`: Válido entre comillas
- `especialidad`: Cardiología, Neurología, Pediatría, etc.
- `codigo`: Formato: Letra + dígitos (M001, D042, etc.)
- `pacientes_atendidos`: Número entero >= 0
- `citas_totales`: Número entero >= 0

**Especialidades Válidas:**
- Cardiología
- Neurología
- Pediatría
- Cirugía
- Oftalmología
- Dermatología
- Psiquiatría
- Oncología
- Radiología
- Gastroenterología

**Ejemplo JSON:**
```json
{
  "nombre": "Dr. Carlos Pérez",
  "especialidad": "Cardiología",
  "codigo": "M001",
  "pacientes_atendidos": 15,
  "citas_totales": 45
}
```

---

### 3. Cita

```cpp
struct Cita {
    string paciente;    // Nombre del paciente
    string medico;      // Nombre del médico
    string fecha;       // Formato: YYYY-MM-DD
    string hora;        // Formato: HH:MM (00:00-23:59)
    string tipo;        // Tipo: Consulta, Seguimiento, Urgencia, Revisión
};
```

**Validaciones:**
- `paciente`: Nombre válido (debe existir en registro)
- `medico`: Nombre válido (debe existir en registro)
- `fecha`: YYYY-MM-DD (validar rango de dias por mes)
- `hora`: HH:MM (00:00 - 23:59)
- `tipo`: Consulta, Seguimiento, Urgencia, Revisión

**Tipos de Citas:**
- `Consulta`: Primera consulta
- `Seguimiento`: Control de evolución
- `Urgencia`: Cita de emergencia
- `Revisión`: Revisión post-tratamiento

**Ejemplo JSON:**
```json
{
  "paciente": "Juan García Martínez",
  "medico": "Dr. Carlos Pérez",
  "fecha": "2024-01-15",
  "hora": "09:00",
  "tipo": "Consulta"
}
```

**Detección de Conflictos:**
```
CONFLICTO si: mismo_medico AND misma_fecha AND misma_hora
Ejemplo:
  Cita 1: Dr. Pérez + 2024-01-15 + 09:00  (válida)
  Cita 2: Dr. Pérez + 2024-01-15 + 09:00  (CONFLICTO)
  Cita 3: Dr. Pérez + 2024-01-15 + 10:00  (diferente hora)
```

---

### 4. Diagnóstico

```cpp
struct Diagnostico {
    string paciente;      // Nombre del paciente
    string condicion;     // Condición médica
    string medicamento;   // Nombre del medicamento
    string dosis;        // Dosis: número + unidad (mg, ml, g, etc.)
};
```

**Validaciones:**
- `paciente`: Nombre válido (debe existir en registro)
- `condicion`: Condición médica válida
- `medicamento`: Nombre del medicamento
- `dosis`: Formato número + unidad (5mg, 500ml, 2g, 0.5mg, etc.)

**Condiciones Médicas Válidas:**
- Hipertensión
- Diabetes
- Asma
- Epilepsia
- Artritis
- Migraña
- Depresión
- Ansiedad
- Gastritis
- Influenza

**Unidades de Dosis Aceptadas:**
- mg (miligramos)
- g (gramos)
- ml (mililitros)
- L (litros)
- mcg (microgramos)
- UI (unidades internacionales)
- % (porcentaje)

**Ejemplo JSON:**
```json
{
  "paciente": "Juan García Martínez",
  "condicion": "Hipertensión",
  "medicamento": "Losartán",
  "dosis": "50mg"
}
```

---

## Clase Principal

### RegistroHospitalario

```cpp
class RegistroHospitalario {
private:
    vector<Paciente> pacientes;
    vector<Medico> medicos;
    vector<Cita> citas;
    vector<Diagnostico> diagnosticos;
    
public:
    // Búsqueda
    Paciente* buscarPaciente(const string& nombre);
    Medico* buscarMedico(const string& nombre);
    
    // Inserción
    void agregarPaciente(const Paciente& p);
    void agregarMedico(const Medico& m);
    void agregarCita(const Cita& c);
    void agregarDiagnostico(const Diagnostico& d);
    
    // Consulta
    vector<Paciente> obtenerPacientes() const;
    vector<Medico> obtenerMedicos() const;
    vector<Cita> obtenerCitas() const;
    vector<Diagnostico> obtenerDiagnosticos() const;
    
    // Generación de reportes
    void generarReporte();
};
```

---

## Métodos Disponibles

### Búsqueda

#### `buscarPaciente(const string& nombre)`
```cpp
Paciente* buscarPaciente(const string& nombre);
```
- **Parámetro:** Nombre del paciente a buscar
- **Retorna:** Puntero a Paciente si existe, nullptr si no
- **Complejidad:** O(n) - búsqueda lineal

#### `buscarMedico(const string& nombre)`
```cpp
Medico* buscarMedico(const string& nombre);
```
- **Parámetro:** Nombre del médico a buscar
- **Retorna:** Puntero a Médico si existe, nullptr si no
- **Complejidad:** O(n) - búsqueda lineal

---

### Inserción

#### `agregarPaciente(const Paciente& p)`
```cpp
void agregarPaciente(const Paciente& p);
```
- **Descripción:** Agrega nuevo paciente al registro
- **Validación:** Verifica que nombre sea único
- **Excepción:** Lanza excepción si ya existe paciente con ese nombre

#### `agregarMedico(const Medico& m)`
```cpp
void agregarMedico(const Medico& m);
```
- **Descripción:** Agrega nuevo médico al registro
- **Validación:** Verifica que código sea único
- **Excepción:** Lanza excepción si ya existe médico con ese código

#### `agregarCita(const Cita& c)`
```cpp
void agregarCita(const Cita& c);
```
- **Descripción:** Agrega nueva cita
- **Validación:** 
  - Paciente y médico deben existir
  - Detecta conflictos (mismo médico + fecha + hora)
- **Nota:** Citas con conflicto se marcan pero se aceptan

#### `agregarDiagnostico(const Diagnostico& d)`
```cpp
void agregarDiagnostico(const Diagnostico& d);
```
- **Descripción:** Agrega diagnóstico a paciente
- **Validación:** Paciente debe existir
- **Excepción:** Error si paciente no existe

---

### Consulta

#### `obtenerPacientes()`
```cpp
vector<Paciente> obtenerPacientes() const;
```
- **Retorna:** Vector de todos los pacientes
- **Complejidad:** O(1) amortizado

#### `obtenerMedicos()`
```cpp
vector<Medico> obtenerMedicos() const;
```
- **Retorna:** Vector de todos los médicos
- **Complejidad:** O(1) amortizado

#### `obtenerCitas()`
```cpp
vector<Cita> obtenerCitas() const;
```
- **Retorna:** Vector de todas las citas
- **Complejidad:** O(1) amortizado

#### `obtenerDiagnosticos()`
```cpp
vector<Diagnostico> obtenerDiagnosticos() const;
```
- **Retorna:** Vector de todos los diagnósticos
- **Complejidad:** O(1) amortizado

---

### Reportes

#### `generarReporte()`
```cpp
void generarReporte();
```
- **Descripción:** Imprime resumen del registro en consola
- **Salida:** Estadísticas básicas a stdout

---

## Relaciones

### Diagrama Entidad-Relación

```
┌──────────────┐
│  Paciente    │
│──────────────│
│ nombre (PK)  │ 1
│ edad         │ ├─── N ┬──── 1 ┌──────────┐
│ tipo_sangre  │        │       │ Diagnóstico
│ habitacion   │        │       └──────────┘
│ diagnostico  │        │
│ estado       │        └──── N ┌──────────┐
└──────────────┘                │ Cita     │
                            M ──┤──────────├── 1 ┌──────────┐
                            1 ──┤ paciente │     │ Médico   │
                                │ medico   │     │──────────│
                                │ fecha    │     │ nombre   │
                                │ hora     │     │ código   │
                                │ tipo     │     │especialid│
                                └──────────┘     └──────────┘
```

### Flujo de Datos

```
Token Stream
    ↓
ReportGenerator.procesarTokens()
    ↓
RegistroHospitalario (datos cargados)
    ↓
┌────────────────────────────────────┐
├────────────────────────────────────┤
│ Pacientes (vector)                 │
│ Médicos (vector)                   │
│ Citas (vector)                     │
│ Diagnósticos (vector)              │
└────────────────────────────────────┘
    │
    ├─→ ReportGenerator (procesar datos)
    ├─→ HTMLGenerator (exportar a HTML)
    └─→ GraphvizGenerator (crear grafo)
```

---

## Ejemplo de Uso

### Código Completo

```cpp
#include "DataStructures.h"
#include "ReportGenerator.h"
#include "HTMLGenerator.h"
#include "GraphvizGenerator.h"
#include <vector>
using namespace std;

int main() {
    // 1. Crear registro
    RegistroHospitalario registro;
    
    // 2. Agregar pacientes
    Paciente p1 = {"Juan García", 45, "O+", 101, "Hipertensión", "Estable"};
    Paciente p2 = {"María López", 32, "AB-", 205, "Diabetes", "Crítico"};
    registro.agregarPaciente(p1);
    registro.agregarPaciente(p2);
    
    // 3. Agregar médicos
    Medico m1 = {"Dr. Pérez", "Cardiología", "M001", 15, 45};
    Medico m2 = {"Dra. García", "Endocrinología", "M002", 12, 38};
    registro.agregarMedico(m1);
    registro.agregarMedico(m2);
    
    // 4. Agregar citas
    Cita c1 = {"Juan García", "Dr. Pérez", "2024-01-15", "09:00", "Consulta"};
    Cita c2 = {"María López", "Dra. García", "2024-01-15", "10:30", "Seguimiento"};
    registro.agregarCita(c1);
    registro.agregarCita(c2);
    
    // 5. Agregar diagnósticos
    Diagnostico d1 = {"Juan García", "Hipertensión", "Losartán", "50mg"};
    Diagnostico d2 = {"María López", "Diabetes", "Metformina", "500mg"};
    registro.agregarDiagnostico(d1);
    registro.agregarDiagnostico(d2);
    
    // 6. Generar reportes
    ReportGenerator gen;
    gen.generarReportePacientes(registro);
    gen.generarReporteMedicos(registro);
    gen.generarReporteCitas(registro);
    gen.generarReporteEstadisticas(registro);
    
    // 7. Exportar a HTML
    HTMLGenerator html;
    html.exportarTodo(registro, ".");
    
    // 8. Generar visualización
    GraphvizGenerator grafo;
    grafo.generarGrafo(registro, "hospital_grafo.dot");
    
    cout << "✓ Procesamiento completado" << endl;
    return 0;
}
```

---

**Especificación Completa de Estructuras de Datos - FASE 3**
