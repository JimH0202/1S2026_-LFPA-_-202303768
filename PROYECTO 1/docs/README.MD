# Proyecto: LFPA - Hospital Management System
## Lenguajes Formales y De Programación

**Estudiante:** jimmy Hurtarte 
**Código:** 202303768  
**Proyecto:** 1  
**Semestre:** 1S2026  


---

## Tabla de Contenidos

1. [Descripción General](#descripción-general)
2. [Fases del Proyecto](#fases-del-proyecto)
3. [Documentación (FASE 4)](#documentación-fase-4)
4. [Compilación](#compilación)
5. [Ejecución](#ejecución)
6. [Estructura de Archivos](#estructura-de-archivos)
7. [Ejemplos de Uso](#ejemplos-de-uso)
8. [Validaciones](#validaciones)
9. [Solución de Problemas](#solución-de-problemas)

---

## escripción General

Sistema **PROFESIONAL Y COMPLETO** de análisis léxico manual (sin regex) y gestión integral de reportes hospitalarios.

### Características Principales

- **Analizador Léxico Avanzado:** Autómata Finito Determinista (AFD) implementado manualmente
- **16+ Tipos de Tokens:** Palabras clave, strings, fechas, horas, tipos sangre, códigos, dosis
- **Validación Inteligente:** Constexto-aware para cada tipo de datos
- **4 Reportes HTML:** Pacientes, Médicos, Citas (con detección de conflictos), Estadísticas
- **Visualización Graphviz:** Grafo de relaciones hospitalarias
- **Interfaz Interactiva:** Menú completo con 11 opciones
- **Manejo de Errores Robusto:** Continúa análisis después de errores

---

## Fases del Proyecto

### FASE 1: Fundamentos
- Tokenización básica
- Definición de tipos de token
- Base para análisis léxico

### FASE 2: Motor de Análisis Léxico
-  AFD manual sin regex
-  16+ tipos de tokens reconocidos
-  Validación de fechas, horas, códigos, tipos sangre, dosis
-  Manejo de errores sin parar análisis
-  127 tokens procesados correctamente (test.med)

### FASE 3: Sistema de Reportes e Interfaz
-  Estructura de datos hospitalaria completa
-  4 tipos de reportes diferentes
-  Exportación HTML con CSS embebido
-  Visualización con Graphviz (DOT format)
-  Interfaz interactiva con menú

### FASE 4: Pruebas y Documentación 
-  **10 casos de prueba** (todos al 100%)
-  **Manual Técnico** con UML, AFD, tabla de transiciones
-  **Manual de Usuario** con ejemplos prácticos
-  **Documento Formal de Pruebas** por casos
-  **Compilación verificada** sin errores
-  **Documentación completa** del proyecto

---

## Documentación (FASE 4)

### Guías Disponibles

| Documento | Propósito | Destinatario |
|-----------|----------|-------------|
| **MANUAL_USUARIO.md** | Guía paso a paso | Usuario Final |
| **MANUAL_TECNICO.md** | Diseño internoyyyy | Desarrollador |
| **PRUEBAS_FORMALES.md** | 10 casos documentados | QA / Auditor |
| **FASE_2_COMPLETE.md** | Especificación FASE 2 | Referencia |
| **FASE_3_COMPLETE.md** | Especificación FASE 3 | Referencia |
| **DATA_STRUCTURES_SPECIFICATION.md** | API de datos | Desarrollador |
| **AFD_SPECIFICATION.md** | Especificación del autómata | Referencia |
| **README.md** | Este archivo | General |

### Lectura Recomendada

**Para usuarios nuevos:**
1. Leer este README (contexto)
2. Leer MANUAL_USUARIO.md (instrucciones)
3. Ejecutar ejemplo en 5 minutos

**Para desarrolladores:**
1. MANUAL_TECNICO.md (arquitectura)
2. PRUEBAS_FORMALES.md (validación)
3. Código fuente comentado

---

## Compilación

### Requisitos del Sistema

| Componente | Mínimo | Recomendado |
|-----------|--------|-------------|
| **SO** | Windows 7 | Windows 10+ |
| **Compilador** | g++ 7.0 | g++ 9.0+ |
| **Estándar** | C++17 | C++17 |
| **RAM** | 512 MB | 2 GB+ |
| **Espacio** | 50 MB | 100 MB+ |

### Verificar Compilador

```bash
g++ --version

# Salida esperada:
# g++ (GCC) 9.3.0
```

Si no está instalado, descargar desde:
- MinGW: https://www.mingw-w64.org/
- MSYS2: https://www.msys2.org/

### Paso a Paso: Compilación

```bash
# 1. Navegar a directorio
cd "c:\Users\jimhu\Desktop\1S2026_-LFPA-_-202303768\PROYECTO 1"

# 2. Compilar
g++ -std=c++17 -o fase3.exe \
    Token.cpp ErrorManager.cpp LexicalAnalyzer.cpp \
    DataStructures.cpp ReportGenerator.cpp \
    HTMLGenerator.cpp GraphvizGenerator.cpp fase3_main.cpp

# 3. Verificar ejecutable creado
dir fase3.exe

# 4. Resultado esperado
# fase3.exe (500-800 KB)
```

** Compilación exitosa - No hay errores**

---

## Ejecución

### Opción 1: Ejecución Normal

```bash
cd "PROYECTO 1"
.\fase3.exe
```

### Opción 2: Doble-clic

1. Abrir explorador de archivos
2. Navegar a `PROYECTO 1`
3. Doble-clic en `fase3.exe`

### Opción 3: Acceso Directo

1. Click derecho en `fase3.exe`
2. Enviar a → Escritorio (crear acceso directo)
3. Doble-clic en acceso directo desde escritorio

### Menú Interactivo

```
╔═══════════════════════════════════════════════════════════════╗
║   SISTEMA DE GESTIÓN HOSPITALARIA - FASE 3                    ║
║   Analizador Léxico + Generador de Reportes                   ║
╚═══════════════════════════════════════════════════════════════╝

1. Cargar archivo (.med)
2. Analizar léxico
3. Ver tokens
4. Ver errores
5. Generar Reporte de Pacientes (HTML)
6. Generar Reporte de Médicos (HTML)
7. Generar Reporte de Citas (HTML)
8. Generar Estadísticas (HTML)
9. Generar Grafo (Graphviz)
10. Generar TODOS los reportes
11. Ver Reportes en Consola
0. Salir

Opción: _
```

---

## Estructura de Archivos

### Código Fuente

```
Token.h / Token.cpp               → Clase Token (tokenización)
ErrorManager.h / ErrorManager.cpp → Gestión de errores
LexicalAnalyzer.h/cpp            → Analizador léxico (AFD)
DataStructures.h/cpp             → Estructuras de datos
ReportGenerator.h/cpp            → Generador de reportes
HTMLGenerator.h /cpp             → Exportador HTML
GraphvizGenerator.h/cpp          → Generador DOT
fase3_main.cpp                   → Programa principal
```

### Archivos Generados (en tiempo de ejecución)

```
fase3.exe                       → Ejecutable
reporte_pacientes.html          → Reporte HTML
reporte_medicos.html            → Reporte HTML
reporte_citas.html              → Reporte HTML
reporte_estadisticas.html       → Reporte HTML
hospital_grafo.dot              → Visualización Graphviz
```

### Casos de Prueba

```
test.med                        → Test básico (127 tokens ✓)
test_errors.med                 → Test con errores (3 errores ✓)
test_caso_1_basico.med          → Caso simple
test_caso_2_multiples.med       → Múltiples registros
test_caso_3_edades_extremas.med → Límites de edad
test_caso_4_valores_borde.med   → Boundary values
test_caso_5_conflictos_citas.med → Detección de conflictos
test_caso_6_tipos_sangre.med    → Todos los tipos sangre
test_caso_7_especialidades.med  → Todas las especialidades
test_caso_8_errores_lexicos.md  → Con errores (continúa análisis)
test_caso_9_dosis_variadas.med  → Diferentes unidades
test_caso_10_hospital_grande.med → Volumen alto (250+ tokens)
```

---

## Ejemplos de Uso

### Ejemplo 1: Inicio Rápido (5 minutos)

```bash
# 1. Compilar
g++ -std=c++17 -o fase3.exe Token.cpp ErrorManager.cpp LexicalAnalyzer.cpp DataStructures.cpp ReportGenerator.cpp HTMLGenerator.cpp GraphvizGenerator.cpp fase3_main.cpp

# 2. Ejecutar
.\fase3.exe

# 3. En menú:
# Opción 1: test.med
# Opción 10: Generar todos los reportes
# Esperar 2 segundos...

# 4. Resultado
# Abiertos 4 archivos HTML en navegador
```

### Ejemplo 2: Crear Archivo Personalizado

**Archivo: mi_hospital.med**
```
HOSPITAL "Hospital Santa María"
PACIENTE "Juan García" 45 O+ 101 "Hipertensión" "Estable"
MEDICO "Dr. López" "Cardiología" M001 1 5
CITA "Juan García" "Dr. López" "2024-01-15" "09:00" "Consulta"
DIAGNOSTICO "Juan García" "Hipertensión" "Losartán" "50mg"
```

**Ejecutar:**
```bash
.\fase3.exe
# Opción 1 → mi_hospital.med
# Opción 10 → Generar reportes
```

---

##  Validaciones (FASE 4)

### 10 Casos de Prueba - 100% Exitosos

| Caso | Descripción | Tokens | Resultado |
|------|-------------|--------|-----------|
| 1 | Caso básico | 31 |  PASÓ |
| 2 | Múltiples registros | 90 |  PASÓ |
| 3 | Edades extremas | 61 |  PASÓ |
| 4 | Valores borde | 49 |  PASÓ |
| 5 | Conflictos de citas | 56 |  PASÓ |
| 6 | Tipos de sangre | 245 |  PASÓ |
| 7 | Especialidades | 92 |  PASÓ |
| 8 | Errores léxicos | 42 |  PASÓ |
| 9 | Dosis variadas | 87 |  PASÓ |
| 10 | Hospital grande | 250 |  PASÓ |

**Resultado Total: 10/10 PASÓ (100%)**

### Validaciones Completadas

- Análisis léxico (tokenización)
- Validación de formatos (fechas, horas, códigos)
- Detección de errores (sin parar análisis)
- Generación de reportes
- Exportación HTML
- Visualización Graphviz
- Detección de conflictos
- Rendimiento (250+ tokens en <1 segundo)

---

## Solución de Problemas

### P: Error "g++ no se reconoce"

**Solución:**
```bash
# Opción 1: Verificar instalación
where g++

# Opción 2: Agregar a PATH
# Settings > System > Advanced > Environment Variables
# Agregar C:\mingw-w64\bin a Path
# Reiniciar terminal
```

### P: "File not found" para .med

**Solución:**
- Asegurarse que archivo .med está en mismo directorio que fase3.exe
- Usar nombre exacto: `test.med` (no `Test.med`)
- Usar ruta completa si está en otro directorio

### P: HTML no abre automáticamente

**Solución:**
- Abrir manualmente en navegador
- Click derecho > Abrir con > Chrome/Firefox
- Arrastrar archivo a navegador abierto

### P: Caracteres especiales se ven mal

**Solución:**
- El programa utiiza UTF-8 (ya configurado)
- HTML generados tienen `<meta charset="UTF-8">`
- Si persiste, abrir con navegador diferente

---

##  Estadísticas del Proyecto

| Métrica | Valor |
|---------|-------|
| **Líneas de Código** | ~2500+ |
| **Archivos Fuente** | 8 (C++) |
| **Tokens Soportados** | 16+ tipos |
| **Reportes HTML** | 4 tipos |
| **Casos de Prueba** | 10 (100% exitosos) |
| **Documentación** | ~5000 líneas |
| **Compilación** | Sin errores |
| **Tiempo de ejecución** | <1 segundo |

---

## Requisitos Cumplidos

### FASE 1
-  Tokenización básica
-  Definición de tipos de token

### FASE 2
-  AFD manual (sin regex)
-  Validación de datos
-  Manejo de errores
-  Pruebas extensivas

### FASE 3
-  Estructura de datos completa
-  4 reportes diferentes
-  Exportación HTML+CSS
-  Visualización Graphviz
-  Interfaz interactiva

### FASE 4
-  10 casos de prueba documentados
-  Manual Técnico (UML, AFD, algoritmos)
-  Manual de Usuario (guías prácticas)
-  Documento Formal de Pruebas
-  Compilación verificada
-  Documentación completa

---

## Notas Técnicas

### Implementación Especial

- **AFD Manual:** Sin usar regex o librerías de parsing
- **Memory Management:** Uso correcto de punteros y referencias
- **Error Recovery:** Continúa análisis tras errores
- **UTF-8 Support:** Maneja caracteres especiales
- **Cross-platform:** Compatible Windows, Linux, Mac

### Características Avanzadas

- Detección automática de conflictos en citas
- Validación context-aware de tokens
- Estadísticas agregadas y calculadas
- Visualización de relaciones con Graphviz
- CSS profesional embebido en HTML

---
