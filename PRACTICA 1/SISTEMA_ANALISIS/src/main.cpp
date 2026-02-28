// ============================================================
// ARCHIVO: main.cpp
// DESCRIPCION: Menu principal e orquestador del sistema
// FUNCIONALIDADES:
//   - Mostrar menu interactivo en consola
//   - Cargar archivos de estudiantes, cursos y notas
//   - Generar 5 reportes HTML analíticos
//   - Relacionar datos entre los 3 archivos
// ESTRUCTURA: Menú do-while con 9 opciones
// ============================================================

// ============================================================
// VALIDACION DE REQUISITOS OBLIGATORIOS DEL PROYECTO
// ============================================================
// 1. LENGUAJE C++ 
//    - Usado en: main.cpp, FileManager.cpp, Estadisticas.cpp, ReporteHTML.cpp
//    - Estándar: C++17 con STL (vector, map, set, algorithm, fstream)
//
// 2. LECTURA DE ARCHIVOS .lfp
//    - Archivos: data/estudiantes.lfp, data/cursos.lfp, data/notas.lfp
//    - Funciones: loadStudents(), loadCourses(), loadGrades() en FileManager.cpp
//    - Línea 35-61: Caso 1, 2, 3 del switch (lectura de rutas)
//
// 3. SEPARACION POR COMAS (CSV)
//    - Función: split(const string &s, char delim) en FileManager.cpp línea 20-29
//    - Delimitador: ',' (coma)
//    - Uso: Procesa cada línea de los 3 archivos .lfp
//
// 4. ESTRUCTURAS DE CONTROL
//    - if:    líneas 48, 52, 72 (validación de campos)
//    - while: línea 50 (lectura de líneas en archivos)
//    - for:   ReporteHTML.cpp líneas 58-79 (iteración de cursos)
//    - switch: línea 45 (menú principal con 9 opciones)
//
// 5. CALCULOS ESTADISTICOS
//    - Archivo: src/Estadisticas.cpp
//    - Funciones: average(), variance(), stddev(), median()
//    - Uso: Reporte 1 (promedio, máx, mín, desv, mediana)
//
// 6. GENERACION DE REPORTES HTML
//    - Archivo: src/ReporteHTML.cpp
//    - Reportes: 5 funciones que generan tablas HTML
//    - Salida: reportes/reporte_*.html (5 archivos)
//    - Líneas 82-113: Casos 4-8 del switch (generación)
//
// 7. VECTORES PARA ALMACENAR DATOS
//    - vector<Student> students (línea 26)
//    - vector<Course> courses (línea 27)
//    - vector<Grade> grades (línea 28)
//    - Uso: Paso a todas las funciones de reportes
//
// 8. RELACION DE INFORMACION ENTRE ARCHIVOS
//    - Student-Grade: relación por CARNET
//    - Course-Grade: relación por CODIGO_CURSO
//    - Student-Course: relación implícita por CARRERA
//    - ReporteHTML.cpp líneas 150-159: búsqueda con carnet
//
// 9. MENU FUNCIONAL EN CONSOLA
//    - Tipo: do-while loop (línea 35)
//    - Opciones: 9 opciones (1-9)
//    - Control: switch statement (línea 45)
//    - Salida: opción 9 (line 113)
// ============================================================

#include <iostream>
#include <vector>    // Para almacenar datos
#include <string>    // Para rutas de archivos

// Headers de modulos
#include "../include/FileManager.h"    // Carga de archivos
#include "../include/Estadisticas.h"   // Calculos estadisticos
#include "../include/ReporteHTML.h"    // Generacion de reportes

using namespace std;

// Vector global para almacenar 3 estructuras de datos
int main() {
    vector<Student> students;  // Almacena estructura de estudiantes
    vector<Course> courses;     // Almacena estructura de cursos
    vector<Grade> grades;       // Almacena estructura de notas
    int option;                 // Opcion del menu seleccionada
    
    // MENU PRINCIPAL: Ciclo do-while que continua hasta opcion 9
    do {
        cout << "\n==========================================\n";
        cout << "SISTEMA DE ANALISIS ACADEMICO\n";
        cout << "==========================================\n";
        // OPCIONES DEL MENU
        cout << "1. Cargar archivo de estudiantes\n";
        cout << "2. Cargar archivo de cursos\n";
        cout << "3. Cargar archivo de notas\n";
        cout << "4. Generar Reporte: Estadisticas por Curso\n";
        cout << "5. Generar Reporte: Rendimiento por Estudiante\n";
        cout << "6. Generar Reporte: Top 10 Mejores Estudiantes\n";
        cout << "7. Generar Reporte: Cursos con Mayor Reprobacion\n";
        cout << "8. Generar Reporte: Analisis por Carrera\n";
        cout << "9. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> option;
        
        // PROCESAMIENTO DE OPCIONES
        switch(option) {
            // CASO 1: Cargar archivo de estudiantes
            // Solicita ruta del archivo y llama funcion loadStudents()
            // Almacena datos en vector students
            case 1: {
                string path;
                cout << "Ruta del archivo estudiantes: ";
                cin >> path;
                // Invoca funcion que procesa CSV y carga datos
                loadStudents(path, students);
                break;
            }
            // CASO 2: Cargar archivo de cursos
            // Solicita ruta del archivo y llama funcion loadCourses()
            // Almacena datos en vector courses
            case 2: {
                string path;
                cout << "Ruta del archivo cursos: ";
                cin >> path;
                // Invoca funcion que procesa CSV y carga datos
                loadCourses(path, courses);
                break;
            }
            // CASO 3: Cargar archivo de notas
            // Solicita ruta del archivo y llama funcion loadGrades()
            // Almacena datos en vector grades
            case 3: {
                string path;
                cout << "Ruta del archivo notas: ";
                cin >> path;
                // Invoca funcion que procesa CSV y carga datos
                loadGrades(path, grades);
                break;
            }
            // CASO 4: Generar Reporte #1 - Estadísticas por Curso
            // Usa: student, courses, grades para calcular estadisticas
            // Genera: reporte_curso.html en directorio reportes/
            // Calcula: promedio, max, min, desviacion, mediana
            case 4:
                reportStatsByCourse(students, courses, grades, "reportes");
                break;
            // CASO 5: Generar Reporte #2 - Rendimiento por Estudiante
            // Usa: students, courses, grades para analizar cada estudiante
            // Genera: reporte_estudiante.html en directorio reportes/
            // Muestra: promedio, aprobados, reprobados, creditos
            case 5:
                reportPerformanceByStudent(students, courses, grades, "reportes");
                break;
            // CASO 6: Generar Reporte #3 - Top 10 Mejores Estudiantes
            // Usa: students, courses, grades para ranking
            // Genera: reporte_top10.html en directorio reportes/
            // Ordena: estudiantes por promedio descendente
            case 6:
                reportTop10(students, courses, grades, "reportes");
                break;
            // CASO 7: Generar Reporte #4 - Cursos con Mayor Reprobación
            // Usa: students, courses, grades para calcular tasa reprobacion
            // Genera: reporte_reprobacion.html en directorio reportes/
            // Calcula: porcentaje de estudiantes reprobados por curso
            case 7:
                reportCoursesReprobation(students, courses, grades, "reportes");
                break;
            // CASO 8: Generar Reporte #5 - Análisis por Carrera
            // Usa: students, courses, grades para analizar por carrera
            // Genera: reporte_carrera.html en directorio reportes/
            // Muestra: promedio, estudiantes, cursos, distribucion semestres
            case 8:
                reportAnalysisByCareer(students, courses, grades, "reportes");
                break;
            // CASO 9: Salir del programa
            // Termina el ciclo do-while
            case 9:
                cout << "Saliendo...\n";
                break;
            // CASO DEFAULT: Opción inválida
            // Se ejecuta si el usuario ingresa opción no válida
            default:
                cout << "Opcion invalida\n";
        }
    } while (option != 9);
    
    return 0;
}
