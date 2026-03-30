# FASE 3 - Sistema de Reportes e Interfaz Gráfica
## Análisis Léxico y Generación de Reportes Hospitalarios



## Tabla de Contenidos
1. [Componentes Implementados](#componentes-implementados)
2. [Estructura de Datos](#estructura-de-datos)
3. [Generador de Reportes](#generador-de-reportes)
4. [Exportadores de Formato](#exportadores-de-formato)
5. [Interfaz Interactiva](#interfaz-interactiva)
6. [Ejecución y Pruebas](#ejecución-y-pruebas)
7. [Salida Esperada](#salida-esperada)

---

## Componentes Implementados

### 1. **DataStructures** (DataStructures.h/cpp)
Estructura de datos para hospital con:

```cpp
struct Paciente {
    string nombre;
    int edad;
    string tipo_sangre;
    int habitacion;
    string diagnostico;
    string estado;
};

struct Medico {
    string nombre;
    string especialidad;
    string codigo;
    int pacientes_atendidos;
    int citas_totales;
};

struct Cita {
    string paciente;
    string medico;
    string fecha;
    string hora;
    string tipo;
};

struct Diagnostico {
    string paciente;
    string condicion;
    string medicamento;
    string dosis;
};

class RegistroHospitalario {
    vector<Paciente> pacientes;
    vector<Medico> medicos;
    vector<Cita> citas;
    vector<Diagnostico> diagnosticos;
    
    // Métodos principales
    Paciente* buscarPaciente(const string& nombre);
    void agregarPaciente(const Paciente& p);
    void agregarMedico(const Medico& m);
    void agregarCita(const Cita& c);
    void agregarDiagnostico(const Diagnostico& d);
    void generarReporte();
};
```

---

## Estructura de Datos

### Organización de Información

```
RegistroHospitalario
├── Pacientes (vector)
│   ├── nombre
│   ├── edad
│   ├── tipo_sangre
│   ├── habitacion
│   ├── diagnostico
│   └── estado
├── Médicos (vector)
│   ├── nombre
│   ├── especialidad
│   ├── código
│   ├── pacientes_atendidos
│   └── citas_totales
├── Citas (vector)
│   ├── paciente
│   ├── médico
│   ├── fecha
│   ├── hora
│   └── tipo
└── Diagnósticos (vector)
    ├── paciente
    ├── condición
    ├── medicamento
    └── dosis
```

---

## Generador de Reportes

### ReportGenerator (ReportGenerator.h/cpp)

**Responsabilidades:**
- Procesar tokens del analizador léxico
- Extraer información estructurada
- Generar 4 reportes diferentes

#### Reportes Generados:

##### 1. **Reporte de Pacientes**
```
Paciente              | Edad | Tipo Sangre | Habitación | Diagnóstico | Estado
─────────────────────────────────────────────────────────────────────────────
Juan García Martínez  | 45   | O+         | 101        | Hipertensión| Estable
María López López     | 32   | AB-        | 205        | Diabetes    | Crítico
```
- Listado completo de pacientes
- Información clínica básica
- Estado actual

##### 2. **Reporte de Médicos**
```
Médico               | Especialidad    | Código | Pacientes | Citas
──────────────────────────────────────────────────────────────────
Dr. Carlos Pérez     | Cardiología    | M001   | 15        | 45
Dra. Ana Rodríguez   | Neurología     | M002   | 12        | 38
```
- Médicos y especialidades
- Carga laboral (pacientes/citas)
- Código identificador

##### 3. **Reporte de Citas (con detección de conflictos)**
```
Fecha      | Hora  | Paciente    | Médico         | Especialidad   | Conflicto
──────────────────────────────────────────────────────────────────────────
2024-01-15 | 09:00 | Juan García | Dr. Pérez      | Cardiología    | ✗
2024-01-15 | 09:00 | María López | Dr. Pérez      | Cardiología    | ⚠ CONFLICTO
```
- Programación de citas
- **Detección automática de conflictos:**
  - Mismo médico
  - Misma fecha
  - Misma hora
- Indicadores visuales

##### 4. **Reporte de Estadísticas**
```

                    ESTADÍSTICAS HOSPITALARIAS
-------------------------------------------------------------
PACIENTES:
  - Total de pacientes: 42
  - Edad promedio: 54.3 años
  - Edad mínima: 18 años
  - Edad máxima: 89 años

MÉDICOS:
  - Total de médicos: 8
  - Especialidades: 6
  - Carga promedio: 5.25 pacientes/médico

CITAS:
  - Total de citas: 134
  - Confitictos detectados: 3
  - Tasa de ocupación: 85.7%

DIAGNÓSTICOS:
  - Total diagnósticos: 57
  - Condiciones únicas: 12
  - Medicamentos en uso: 23
```
- Estadísticas agregadas
- Métricas de desempeño
- Análisis de utilización

---

## Exportadores de Formato

### HTMLGenerator (HTMLGenerator.h/cpp)

**Características:**
- CSS embebido (no requiere archivos externos)
- Tablas responsive
- Colores profesionales
- Encabezados informativos

**Archivos Generados:**
1. `reporte_pacientes.html`
2. `reporte_medicos.html`
3. `reporte_citas.html`
4. `reporte_estadisticas.html`

**Estilos incluidos:**
- Tablas con bordes
- Alternancia de colores en filas
- Encabezados destacados
- Indicadores de conflicto (⚠)
- Información de generación (fecha/hora)

### GraphvizGenerator (GraphvizGenerator.h/cpp)

**Formato:** DOT (Graphviz)
**Archivo generado:** `hospital_grafo.dot`

**Estructura del Grafo:**
```
digraph Hospital {
    // Nodo central
    hospital [label="Hospital", shape=box, color=blue]
    
    // Nodos de pacientes
    paciente_1 [label="Juan García\n45 años", color=lightblue]
    
    // Nodos de médicos
    medico_1 [label="Dr. Pérez\nCardiología", color=lightgreen]
    
    // Nodos de citas
    cita_1 [label="Cita\n2024-01-15", color=yellow]
    
    // Aristas
    hospital -> paciente_1
    hospital -> medico_1
    paciente_1 -> cita_1
    medico_1 -> cita_1
}
```

**Visualización:**
- Para convertir a PNG: `dot -Tpng hospital_grafo.dot -o grafo.png`
- Para ver en línea: copiar contenido en graphviz.org
- Exportar a: PNG, SVG, PDF, etc.

---

## Interfaz Interactiva

### fase3_main.cpp - Menú Principal

```
╔═══════════════════════════════════════════════════════════════════╗
║     SISTEMA DE GESTIÓN DE REPORTES HOSPITALARIOS - FASE 3        ║
╚═══════════════════════════════════════════════════════════════════╝

1. Cargar archivo .med
2. Generar Reporte de Pacientes
3. Generar Reporte de Médicos
4. Generar Reporte de Citas
5. Generar Reporte de Estadísticas
6. Exportar a HTML (todos los reportes)
7. Generar Visualización Graphviz
8. Mostrar todos los tokens
9. Mostrar errores léxicos
10. Salir

Opción: _
```

**Flujo de Uso:**
1. Seleccionar opción 1 para cargar `test.med`
2. Seleccionar opciones 2-5 para ver reportes en consola
3. Seleccionar opción 6 para exportar HTML
4. Seleccionar opción 7 para generar grafo
5. Seleccionar opción 10 para salir

---

## Ejecución y Pruebas

### Compilación
```bash
g++ -std=c++17 -o fase3.exe \
    Token.cpp ErrorManager.cpp LexicalAnalyzer.cpp \
    DataStructures.cpp ReportGenerator.cpp \
    HTMLGenerator.cpp GraphvizGenerator.cpp fase3_main.cpp
```

### Ejecución
```bash
./fase3.exe
```

### Script de Prueba Python
```bash
python3 test_fase3.py
```

---

## Salida Esperada

### Consola (ejemplo)
```
╔═══════════════════════════════════════════════════════════════════╗
║     SISTEMA DE GESTIÓN DE REPORTES HOSPITALARIOS - FASE 3        ║
╚═══════════════════════════════════════════════════════════════════╝

[1] Cargando archivo: test.med
[] Archivo cargado: 127 tokens procesados
[] 0 errores léxicos detectados

═══════════════════════════════════════════════════════════════════
                    REPORTE DE PACIENTES
═══════════════════════════════════════════════════════════════════

Paciente              | Edad | Tipo Sangre | Habitación | Diagnóstico
─────────────────────────────────────────────────────────────────────
Juan García Martínez  | 45   | O+         | 101        | Hipertensión
María López López     | 32   | AB-        | 205        | Diabetes
...
```

### Archivos Generados
```
reporte_pacientes.html (abierto en navegador)
reporte_medicos.html
reporte_citas.html
reporte_estadisticas.html
hospital_grafo.dot (visualización con Graphviz)
```

### Browser (HTML)
- **reporte_pacientes.html**: Tabla con pacientes, colores alternados
- **reporte_medicos.html**: Médicos con especialidades y estadísticas
- **reporte_citas.html**: Calendario con indicadores de conflicto (⚠)
- **reporte_estadisticas.html**: Dashboard con gráficos/métricas

---

## Integración de Fases

```
test.med (entrada)
    ↓
LexicalAnalyzer (FASE 2)
    ↓ [127 tokens]
    ↓
ReportGenerator (FASE 3)
    ↓ [datos estructurados]
    ├─→ ReportGenerator.generarLista() → Consola
    ├─→ HTMLGenerator → reporte_*.html
    └─→ GraphvizGenerator → hospital_grafo.dot
```

---

## Características Implementadas

### Completadas
- [x] Análisis léxico con reconocimiento de tokens
- [x] Estructura de datos hospitalaria
- [x] Generador de 4 reportes diferentes
- [x] Exportación a HTML con CSS embebido
- [x] Generación de visualización Graphviz
- [x] Detección de conflictos en citas
- [x] Interfaz interactiva con menú
- [x] Manejo de errores léxicos
- [x] Compilación exitosa sin errores

### Notas
- GUI avanzada: No implementada (se usó interfaz de consola)
- Base de datos: No implementada (datos en memoria)
- API REST: No implementada

---

## Próximos Pasos

1. **Pruebas extensivas** con múltiples archivos `.med`
2. **Validación de reportes** HTML en diferentes navegadores
3. **Optimización** de rendimiento para grandes volúmenes
4. **GUI opcional** con Qt (si es requerida)
5. **Base de datos** (sqlite3 o similar) para persistencia

---

## Compilación Final
```bash
g++ -std=c++17 -o fase3.exe Token.cpp ErrorManager.cpp LexicalAnalyzer.cpp DataStructures.cpp ReportGenerator.cpp HTMLGenerator.cpp GraphvizGenerator.cpp fase3_main.cpp
# Output: fase3.exe (compilación exitosa)
```

---

**FASE 3 - COMPLETADA **

Todos los módulos compilados exitosamente.
Sistema listo para ejecutar con `./fase3.exe`
