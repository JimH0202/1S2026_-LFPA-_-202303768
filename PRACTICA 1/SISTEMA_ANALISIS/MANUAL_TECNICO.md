# Manual Técnico

Este documento describe la arquitectura, diseño y detalles de implementación del
Sistema de Análisis Académico desarrollado en C++.

## Estructura del proyecto

```text
SISTEMA_ANALISIS/
├── include/              # Cabeceras (structs y prototipos)
│   ├── FileManager.h     # Definición de estructuras de datos y lectura de .lfp
│   ├── Estadisticas.h    # Funciones de cálculo estadístico
│   └── ReporteHTML.h     # Prototipos para generar reportes HTML
├── src/                  # Código fuente de cada módulo
│   ├── main.cpp          # Orquestador y menú interactivo
│   ├── FileManager.cpp   # Implementación de carga y parseo CSV
│   ├── Estadisticas.cpp  # Implementación de funciones matemáticas
│   └── ReporteHTML.cpp   # Generación de los cinco reportes HTML
├── data/                 # Archivos de datos de entrada (.lfp)
├── reportes/             # Salida de los reportes generados
└── app.exe               # Ejecutable compilado (Windows)
```

## Módulos principales

### FileManager
- Define las estructuras `Student`, `Course`, `Grade`.
- Proporciona `split()` para separar cadenas por comas.
- Funciones `loadStudents()`, `loadCourses()`, `loadGrades()` que leen
  archivos CSV (`.lfp`) usando `ifstream` y almacenan los registros en vectores.
- Manejo de errores: archivos no existentes, formato incorrecto, conversión de
  tipos, líneas vacías.

### Estadisticas
- Contiene los cálculos estadísticos necesarios en los reportes:
  `average()`, `variance()`, `stddev()`, `median()`.
- Recibe vectores de `double` y devuelve los resultados.

### ReporteHTML
- Cinco funciones para generar contenido HTML tabulado:
  1. `reportStatsByCourse` – estadísticas por curso.
  2. `reportPerformanceByStudent` – rendimiento por estudiante.
  3. `reportTop10` – ranking de los 10 mejores alumnos.
  4. `reportCoursesReprobation` – cursos con mayor reprobación.
  5. `reportAnalysisByCareer` – análisis por carrera.
- Cada función recibe referencias a los vectores de datos y un directorio de
  salida, crea un archivo en `reportes/` y escribe encabezados, tablas y filas.

### main.cpp
- Implementa el menú interactivo y orquesta las llamadas a los módulos.
- Nueva función auxiliar `getMenuOption()` que valida la entrada numérica y
  asegura que el valor esté entre 1 y 9 (mejora de robustez).
- Control de flujo `do { ... } while(option != 9)`.
- Cada opción del menú solicita rutas de archivos o genera reportes.

## Compilación

Requisitos:
- Compilador C++ con soporte C++17 (`g++`, `clang++` o similar).
- Windows, Linux o macOS.

Comando de compilación puede ser:

```bash
cd "SISTEMA_ANALISIS"
g++ -std=c++17 -Iinclude src/FileManager.cpp src/Estadisticas.cpp \
    src/ReporteHTML.cpp src/main.cpp -o app.exe
```

En Windows el ejecutable resultante será `app.exe`. En otros sistemas se
puede omitir la extensión.

## Dependencias y estándares

- Lenguaje: C++ (estándar C++17).
- STL usada: `vector`, `string`, `map`, `set`, `sstream`, `fstream`, `iostream`.
- No se requieren librerías externas.

## Extensión y mantenimiento

- Para agregar nuevos reportes, crear una función en `ReporteHTML.cpp` y añadir
  un caso en el `switch` del menú.
- La validación de entrada se centraliza en `getMenuOption()`; puede adaptarse
  para aceptar rangos distintos.
- Los archivos de datos pueden modificarse siempre que respeten el formato CSV
  de 5 campos; las funciones `load*` ya verifican la cantidad mínima de campos.

## Notas de diseño

- Separar en módulos facilita el cumplimiento de requisitos de la práctica y la
  reutilización de código.
- El formato CSV simple hace posible usar `split()` genérico para cualquier
  archivo con comas.
- El uso de vectores permite almacenar cantidades arbitrarias de registros sin
  gestionar memoria manualmente.
