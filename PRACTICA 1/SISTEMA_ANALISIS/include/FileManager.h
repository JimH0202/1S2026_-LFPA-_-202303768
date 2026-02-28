// ============================================================
// ARCHIVO: FileManager.h
// DESCRIPCION: Define estructuras de datos y funciones para
//              carga de archivos del sistema educativo
// FUNCIONALIDADES:
//   - Cargar archivos CSV de estudiantes, cursos y notas
//   - Procesar informacion con separacion por comas
//   - Almacenar datos en estructuras (Student, Course, Grade)
//   - Relacionar informacion entre los tres archivos
// ============================================================

#pragma once

#include <string>
#include <vector>

// ESTRUCTURA: Student - Almacena informacion de un estudiante
struct Student {
    int carnet;              // ID unico del estudiante
    std::string nombre;      // Nombre del estudiante
    std::string apellido;    // Apellido del estudiante
    std::string carrera;     // Carrera que cursa
    int semestre;            // Semestre actual
};

// ESTRUCTURA: Course - Almacena informacion de un curso
struct Course {
    int codigo;              // Codigo unico del curso
    std::string nombre;      // Nombre del curso
    int creditos;            // Creditos del curso
    int semestre;            // Semestre en que se dicta
    std::string carrera;     // Carrera a la que pertenece
};

// ESTRUCTURA: Grade - Almacena calificacion de un estudiante
struct Grade {
    int carnet;              // Carnet del estudiante
    int codigo_curso;        // Codigo del curso
    double nota;             // Calificacion obtenida (0-100)
    std::string ciclo;       // Ciclo lectivo
    int anio;                // Anio del ciclo
};

// FUNCIONES DE UTILIDAD Y CARGA DE DATOS

// Funcion auxiliar: Separar string por delimitador (coma)
// Implementa procesamiento CSV para parsear archivos .lfp
std::vector<std::string> split(const std::string &s, char delim);

// Funciones de carga - Leen archivos del sistema y almacenan en vectores
// Implementan: carga de archivos, procesamiento CSV, validacion de datos
bool loadStudents(const std::string &path, std::vector<Student> &students);
bool loadCourses(const std::string &path, std::vector<Course> &courses);
bool loadGrades(const std::string &path, std::vector<Grade> &grades);
