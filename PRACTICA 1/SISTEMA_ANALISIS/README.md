# Sistema de Análisis Académico - LFPA

Sistema modular en C++17 para análisis de datos académicos con generación de reportes HTML.

## Estructura del Proyecto

```
SISTEMA_ANALISIS/
├── include/              # Headers (definiciones de structs y funciones)
│   ├── FileManager.h     # I/O de archivos y definicion de estructuras
│   ├── Estadisticas.h    # Funciones de calculos estadisticos
│   └── ReporteHTML.h     # Funciones de generacion de reportes
├── src/                  # Implementaciones
│   ├── main.cpp          # Menu principal (orquestador)
│   ├── FileManager.cpp   # Carga de datos desde .lfp
│   ├── Estadisticas.cpp  # Calculos: promedio, varianza, desv. est., mediana
│   └── ReporteHTML.cpp   # Generacion de 5 reportes HTML
├── data/                 # Archivos de datos
│   ├── estudiantes.lfp   # Carnet,Nombre,Apellido,Carrera,Semestre
│   ├── cursos.lfp        # Codigo,Nombre,Creditos,Semestre,Carrera
│   └── notas.lfp         # Carnet,CodigoCurso,Nota,Ciclo,Anio
├── reportes/             # Reportes generados (HTML)
└── app.exe               # Ejecutable compilado
```

## Compilacion

```bash
g++ -std=c++17 -Iinclude src/main.cpp src/FileManager.cpp src/Estadisticas.cpp src/ReporteHTML.cpp -o app.exe
```

## Uso

```bash
./app.exe
```

El menu permite:

1. Cargar archivo de estudiantes (estudiantes.lfp)
2. Cargar archivo de cursos (cursos.lfp)
3. Cargar archivo de notas (notas.lfp)
4. Reporte: Estadisticas por Curso
5. Reporte: Rendimiento por Estudiante
6. Reporte: Top 10 Mejores Estudiantes
7. Reporte: Cursos con Mayor Reprobacion
8. Reporte: Analisis por Carrera
9. Salir

## Formato de Archivos .lfp

Los archivos usan formato CSV (separado por comas):

### estudiantes.lfp
```
Carnet,Nombre,Apellido,Carrera,Semestre
123001,Juan,Perez,Ingenieria,2
```

### cursos.lfp
```
Codigo,Nombre,Creditos,Semestre,Carrera
1001,Algebra,4,1,Ingenieria
```

### notas.lfp
```
Carnet,CodigoCurso,Nota,Ciclo,Anio
123001,1001,85,1,2023
```

## Modulos

- **FileManager**: Carga datos de archivos .lfp a vectores
- **Estadisticas**: Calcula promedio, varianza, desviacion estandar, mediana
- **ReporteHTML**: Genera 5 reportes con tablas HTML formateadas
- **main**: Menu interactivo que orquesta llamadas a modulos

## Estadisticas Calculadas

Para cada analisis se generan:
- Promedio (average)
- Varianza (variance)
- Desviacion estandar (stddev)
- Mediana (median)
- Maximo y minimo

## Requisitos

- C++17 o superior
- g++ compilador
- Windows 10+ o Linux/macOS
