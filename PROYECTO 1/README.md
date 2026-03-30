# Proyecto: LFPA (Lexical Analyzer + Hospital Management System)
## Lenguajes Formales y Análisis Sintáctico

**Estudiante:** jimmy Hurtarte  
**Proyecto:** 1  
**Código:** 202303768  
**Semestre:** 1S2026

---

## Descripción General

Sistema completo de análisis léxico y gestión de reportes hospitalarios implementado en **C++17**.

El proyecto se estructura en **3 FASES**:

### **FASE 1**: Fundamentos (Completada)
- Tokenización básica
- Definición de tipos de token
- Base para análisis léxico

### **FASE 2**: Motor de Análisis Léxico (Completada ✓)
- Implementación del Analizador Autómata Finito Determinista (AFD)
- Reconocimiento de 16+ tipos de tokens
- Validación de formatos (fechas, horas, códigos, tipos de sangre)
- Manejo de errores sin parar análisis
- Pruebas extensivas

### **FASE 3**: Sistema de Reportes e Interfaz (Completada ✓)
- Estructura de datos hospitalaria
- Generador de 4 reportes diferentes
- Exportación a HTML con CSS
- Visualización con Graphviz
- Interfaz interactiva

---

## Estructura de Archivos

```
.
├── Token.h / Token.cpp
│   └── Clase Token: representación de unidades léxicas
│
├── ErrorManager.h / ErrorManager.cpp
│   └── Gestión de errores léxicos
│
├── LexicalAnalyzer.h / LexicalAnalyzer.cpp
│   └── Analizador léxico con AFD
│
├── DataStructures.h / DataStructures.cpp
│   └── Estructuras para registros hospitalarios
│
├── ReportGenerator.h / ReportGenerator.cpp
│   └── Procesamiento de tokens y generación de reportes
│
├── HTMLGenerator.h / HTMLGenerator.cpp
│   └── Exportación a formato HTML with CSS
│
├── GraphvizGenerator.h / GraphvizGenerator.cpp
│   └── Generación de visualización (DOT format)
│
├── fase3_main.cpp
│   └── Programa principal (interfaz interactiva)
│
├── test.med
│   └── Archivo de entrada de ejemplo (127 tokens válidos)
│
├── test_errors.med
│   └── Archivo de prueba con errores léxicos
│
├── FASE_2_COMPLETE.md
│   └── Documentación detallada de FASE 2
│
├── FASE_3_COMPLETE.md
│   └── Documentación detallada de FASE 3
│
├── AFD_SPECIFICATION.md
│   └── Especificación del Autómata Finito
│
└── README.md (este archivo)
```

---

## Construcción

### Requisitos
- **Compilador:** g++ (GCC 9.0 o superior)
- **Estándar:** C++17
- **SO:** Windows, Linux, macOS

### Compilación Completa
```bash
g++ -std=c++17 -o fase3.exe \
    Token.cpp ErrorManager.cpp LexicalAnalyzer.cpp \
    DataStructures.cpp ReportGenerator.cpp \
    HTMLGenerator.cpp GraphvizGenerator.cpp fase3_main.cpp
```

**Resultado esperado:** `fase3.exe` compilado sin errores

### Compilar Solo FASE 2 (Lexer)
```bash
g++ -std=c++17 -o lexer.exe \
    Token.cpp ErrorManager.cpp LexicalAnalyzer.cpp \
    -Dmain_lexer -c && mv a.out lexer.exe
```

---

## Ejecución

### Opción 1: Menú Interactivo
```bash
./fase3.exe
```

Menú disponible:
```
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
```

### Opción 2: Procesamiento Automático
```bash
# Compilar y ejecutar automáticamente
python3 test_fase3.py
```

---

## Entrada de Datos

### Formato del Archivo `.med`

El archivo debe contener directivas en formato:
```
HOSPITAL "Nombre Hospital"
PACIENTE "Nombre" 45 O+ 101 "Diagnóstico" "Estable"
PACIENTE "Otra Persona" 32 AB- 205 "Otra Condición" "Crítico"
MEDICO "Dr. Pérez" "Cardiología" M001 15 45
MEDICO "Dra. García" "Neurología" M002 12 38
CITA "Paciente1" "Dr. Pérez" "2024-01-15" "09:00" "Seguimiento"
DIAGNOSTICO "Paciente1" "Hipertensión" "Medicamento1" "5mg"
```

### Formatos Válidos Reconocidos

| Tipo Token | Formato | Ejemplo |
|-----------|---------|---------|
| PALABRA CLAVE | Identificador | HOSPITAL, PACIENTE, MEDICO |
| STRING | Entre comillas | "Juan García Martínez" |
| FECHA | YYYY-MM-DD | "2024-01-15" |
| HORA | HH:MM | "09:00", "14:30" |
| TIPO SANGRE | Letra(s) + signo | O+, AB-, B- |
| CÓDIGO | Letra + dígitos | M001, P042 |
| ESPECIALIDAD | Palabra válida | Cardiología, Neurología |
| DOSIS | Número + unidad | 5mg, 500ml |
| NÚMERO | Dígitos | 45, 102, 9999 |

---

## Salida Generada

### Reportes en Consola
```
═══════════════════════════════════════════════════════════════════
                    REPORTE DE PACIENTES
═══════════════════════════════════════════════════════════════════

Paciente              | Edad | Tipo Sangre | Habitación | Diagnóstico
─────────────────────────────────────────────────────────────────────
Juan García Martínez  | 45   | O+         | 101        | Hipertensión
```

### Reportes en HTML
- `reporte_pacientes.html`
- `reporte_medicos.html`
- `reporte_citas.html`
- `reporte_estadisticas.html`

Características:
- CSS embebido
- Tablas responsivas
- Colores profesionales
- Timestamp de generación

### Visualización Graphviz
- Archivo: `hospital_grafo.dot`
- Formato: DOT (Graphviz)
- Conversión: `dot -Tpng hospital_grafo.dot -o grafo.png`

---

## Características Principales

### FASE 2: Análisis Léxico
- ✓ Autómata Finito Determinista (AFD) manual
- ✓ 16+ tipos de tokens reconocidos
- ✓ Validación de formatos complejos
- ✓ Manejo de errores sin parar análisis
- ✓ Mensajes de error descriptivos
- ✓ Rastreo de línea y columna

### FASE 3: Generación de Reportes
- ✓ 4 tipo de reportes diferentes
- ✓ Detección de conflictos en citas
- ✓ Estadísticas agregadas
- ✓ Exportación a HTML with CSS
- ✓ Visualización con Graphviz
- ✓ Interfaz interactiva de menú

---

## Pruebas

### Archivo de Prueba: `test.med`
- **Tokens:** 127 válidos
- **Errores:** 0
- **Estado:**  Pasa

### Archivo con Errores: `test_errors.med`
- **Tokens:** Válidos + Inválidos
- **Errores Detectados:** 3
- **Estado:**  Pasa (error detection funciona)

### Test Automático
```bash
python3 test_fase3.py
```

---

## Ejemplos de Uso

### Ejemplo 1: Cargar y Analizar
```cpp
LexicalAnalyzer lexer("test.med");
vector<Token> tokens = lexer.getTokens();
cout << "Tokens: " << tokens.size() << endl;
```

### Ejemplo 2: Generar Reportes
```cpp
ReportGenerator gen;
RegistroHospitalario reg = gen.procesarTokens(tokens);
gen.generarReportePacientes(reg);
gen.generarReporteMedicos(reg);
```

### Ejemplo 3: Exportar a HTML
```cpp
HTMLGenerator html;
html.exportarTodo(reg, ".");
// Genera 4 archivos HTML
```

### Ejemplo 4: Graphviz
```cpp
GraphvizGenerator grafo;
grafo.generarGrafo(reg, "hospital_grafo.dot");
// Genera archivo DOT para visualización
```

---

## Detección de Errores

### Errores Léxicos Detectables
1. **Strings no cerrados** → `Error: String sin cerrar`
2. **Fechas inválidas** → `Error: Fecha inválida (YYYY-MM-DD)`
3. **Horas inválidas** → `Error: Hora inválida (HH:MM)`
4. **Tipos de sangre inválidos** → `Error: Tipo de sangre desconocido`
5. **Códigos malformados** → `Error: Código debe ser letra + dígitos`
6. **Dosis incorrecta** → `Error: Dosis debe ser número + unidad`

**Todos los errores se reportan sin pausar el análisis**

---

## Estadísticas del Proyecto

| Métrica | Valor |
|---------|-------|
| Líneas de Código | ~2000+ |
| Archivos Fuente | 8 |
| Tipos de Tokens | 16+ |
| Reportes Generados | 4 |
| Formatos Soportados | 3 (Texto, HTML, DOT) |
| Compilación |  Sin errores |
| Tokens Procesados (prueba) | 127 |

---

## Requisitos Cumplidos

- FASE 1: Fundamentos completados
- FASE 2: Análisis léxico completo con validaciones
- FASE 3: Reportes + Exportación + Visualización
- Manejo de errores robusto
- Interfaz interactiva
- Documentación completa
- Compilación sin errores
- Pruebas funcionales

---

## Documentación Adicional

- [FASE_2_COMPLETE.md](FASE_2_COMPLETE.md) - Especificación del Lexer
- [FASE_3_COMPLETE.md](FASE_3_COMPLETE.md) - Sistema de Reportes
- [AFD_SPECIFICATION.md](AFD_SPECIFICATION.md) - Detalles del Autómata

---

## Compilación Rápida

```bash
# Uno-liner para compilar y ejecutar
g++ -std=c++17 -o fase3.exe Token.cpp ErrorManager.cpp LexicalAnalyzer.cpp DataStructures.cpp ReportGenerator.cpp HTMLGenerator.cpp GraphvizGenerator.cpp fase3_main.cpp && ./fase3.exe
```
