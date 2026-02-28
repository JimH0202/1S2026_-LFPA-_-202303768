// ============================================================
// ARCHIVO: FileManager.cpp
// DESCRIPCION: Implementacion de carga de archivos y parseo
// FUNCIONALIDADES:
//   - Leer archivos CSV del sistema operativo
//   - Procesar lineas con separacion por comas
//   - Validar y almacenar datos en estructuras
//   - Reportar cantidad de registros cargados
// ============================================================

// ============================================================
// REQUISITOS OBLIGATORIOS IMPLEMENTADOS EN ESTE ARCHIVO:
// LECTURA DE ARCHIVOS .lfp
//    - loadStudents(): Lee data/estudiantes.lfp
//    - loadCourses(): Lee data/cursos.lfp
//    - loadGrades(): Lee data/notas.lfp
//    - Cada función abre el archivo con ifstream
//    - Validación: if (!file.is_open()) para manejo de errores
//
// SEPARACION DE DATOS MEDIANTE COMAS
//    - split(const string &s, char delim) en línea 19
//    - Algoritmo: stringstream + getline(ss, item, ',')
//    - Separa cada línea del archivo por delimitador ','
//    - Retorna vector<string> con campos individuales
//    - Uso: procesa 5 campos por estudiante, curso y nota
// ============================================================

#include "../include/FileManager.h"
#include <fstream>    // Para lectura de archivos
#include <sstream>    // Para procesamiento de strings
#include <iostream>   // Para mensajes de consola

using namespace std;

// FUNCION: split()
// PROPOSITO: Procesar string separado por comas (CSV)
// PARAMETROS: s = string a procesar, delim = delimitador (',')
// RETORNA: Vector de strings separados
// USO: Implementa parseo de datos desde archivos .lfp
// IMPLEMENTACION: Usa clases nativas de C++ (stringstream, getline)
//   - stringstream: Convierte string en stream (similar a entrada/salida)
//   - getline(ss, item, delim): Lee hasta encontrar delimitador ','
//   - Emula comportamiento de split() de lenguajes como Java/Python
//   - REQUISITO TECNICO: Separación y análisis de datos
vector<string> split(const string &s, char delim) {
    vector<string> elems;                      // Colección para almacenar campos
    stringstream ss(s);                         // Stream de strings nativo C++
    string item;
    while (getline(ss, item, delim)) {         // Ciclo: procesa cada campo
        elems.push_back(item);                 // Almacena en colección
    }
    return elems;
}

// FUNCION: loadStudents()
// PROPOSITO: Cargar archivo de estudiantes desde sistema
// PARAMETROS: path = ruta del archivo estudiantes.lfp
//             students = vector para almacenar datos
// RETORNA: true si carga exitosa, false si error
// REQUISITOS TECNICOS IMPLEMENTADOS:
//   - Lectura de archivos mediante clases nativas (ifstream)
//   - Separación de datos mediante split()
//   - Estructuras de control (if para validar, while para iterar)
//   - Colecciones: vector<Student> para almacenar registros
// MANEJO DE ERRORES IMPLEMENTADO:
//   - Validación: archivo no existe
//   - Validación: archivo corrupto o vacío
//   - Validación: campos inválidos o incompletos
//   - Mensajes descriptivos de error
bool loadStudents(const string &path, vector<Student> &students) {
    // REQUISITO: Lectura de archivos mediante clases nativas del lenguaje
    // Clase nativa: ifstream (input file stream de <fstream>)
    ifstream file(path);  // Abre el archivo en modo lectura
    
    // MANEJO DE ERRORES: Verificación 1 - Archivo existe y es accesible
    if (!file.is_open()) {
        cerr << "Error critico: No se puede abrir el archivo '" << path << "'\n";
        cerr << "   Posibles causas:\n";
        cerr << "   - El archivo no existe\n";
        cerr << "   - No tienes permisos para leer el archivo\n";
        cerr << "   - La ruta es incorrecta\n";
        return false;
    }
    
    // MANEJO DE ERRORES: Verificación 2 - Archivo no está vacío
    file.peek();
    if (file.eof() && file.tellg() == 0) {
        cerr << "Error: El archivo de estudiantes está vacío\n";
        file.close();
        return false;
    }
    string line;
    int lineCount = 0;  // Contador para reportar errores
    int errorCount = 0; // Contador de errores
    
    // REQUISITO: Estructuras de control - ciclo (while)
    // Lectura nativa del archivo línea por línea
    while (getline(file, line)) {
        lineCount++;
        if (line.empty()) continue;
        
        // REQUISITO: Separación y análisis de datos usando split()
        // Invoca: split(line, ',') para dividir por comas
        auto parts = split(line, ',');
        
        // MANEJO DE ERRORES: Validación de formato
        if (parts.size() < 5) {
            cerr << "Advertencia: Línea " << lineCount << " tiene solo " << parts.size() 
                 << " campos (esperado 5). Línea ignorada.\n";
            errorCount++;
            continue;
        }
        
        // REQUISITO: Colecciones - almacenamiento en vector
        // Tipo: vector<Student> (colección de registros)
        // MANEJO DE ERRORES: Try-catch para validar conversión de tipos
        try {
            Student s;
            s.carnet = stoi(parts[0]);      // Convierte carnet a int
            s.nombre = parts[1];
            s.apellido = parts[2];
            s.carrera = parts[3];
            s.semestre = stoi(parts[4]);    // Convierte semestre a int
            
            // MANEJO DE ERRORES: Validaciones de datos
            if (s.carnet <= 0) {
                cerr << "Advertencia: Línea " << lineCount << " - Carnet debe ser positivo. Ignorada.\n";
                errorCount++;
                continue;
            }
            if (s.nombre.empty() || s.apellido.empty() || s.carrera.empty()) {
                cerr << "Advertencia: Línea " << lineCount << " - Campos de texto vacíos. Ignorada.\n";
                errorCount++;
                continue;
            }
            if (s.semestre < 1 || s.semestre > 10) {
                cerr << "Advertencia: Línea " << lineCount << " - Semestre fuera de rango (1-10). Ignorada.\n";
                errorCount++;
                continue;
            }
            
            students.push_back(s);  // Agregar a colección si validación OK
        } catch (const invalid_argument &e) {
            cerr << "Error: Línea " << lineCount << " - Campo numérico inválido: " << e.what() << "\n";
            errorCount++;
        } catch (const out_of_range &e) {
            cerr << "Error: Línea " << lineCount << " - Número fuera de rango: " << e.what() << "\n";
            errorCount++;
        } catch (const exception &e) {
            cerr << "Error inesperado en línea " << lineCount << ": " << e.what() << "\n";
            errorCount++;
        }
    }
    file.close();
    
    // MANEJO DE ERRORES: Resumen de carga
    cout << "\n========== RESUMEN CARGA ESTUDIANTES ==========\n";
    cout << "Estudiantes cargados exitosamente: " << students.size() << "\n";
    if (errorCount > 0) {
        cout << "Líneas omitidas por errores: " << errorCount << "\n";
        cout << "Total de líneas procesadas: " << lineCount << "\n";
    }
    cout << "=============================================\n\n";
    
    return !students.empty();  // Retorna true si al menos uno se cargó
}

// FUNCION: loadCourses()
// PROPOSITO: Cargar archivo de cursos desde sistema
// PARAMETROS: path = ruta del archivo cursos.lfp
//             courses = vector para almacenar datos
// RETORNA: true si exitoso, false si error
// REQUISITOS TECNICOS IMPLEMENTADOS:
//   - Lectura de archivos mediante clases nativas (ifstream)
//   - Separación de datos mediante split()
//   - Estructuras de control (if para validar, while para iterar)
//   - Colecciones: vector<Course> para almacenar registros
bool loadCourses(const string &path, vector<Course> &courses) {
    // REQUISITO: Lectura de archivos mediante clases nativas (ifstream)
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Error: no se puede abrir el archivo de cursos " << path << "\n";
        return false;
    }
    string line;
    
    // REQUISITO: Estructuras de control - ciclo (while)
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        // REQUISITO: Separación y análisis de datos usando split()
        auto parts = split(line, ',');
        if (parts.size() < 5) continue; // Validar 5 campos minimo
        
        // REQUISITO: Colecciones - almacenamiento en vector
        // Tipo: vector<Course> (colección de registros)
        Course c;
        c.codigo = stoi(parts[0]);
        c.nombre = parts[1];
        c.creditos = stoi(parts[2]);
        c.semestre = stoi(parts[3]);
        c.carrera = parts[4];
        courses.push_back(c);  // Agregar elemento a colección
    }
    file.close();
    // Mostrar cantidad de registros cargados en consola
    cout << "Cursos cargados: " << courses.size() << "\n";
    return true;
}

// FUNCION: loadGrades()
// PROPOSITO: Cargar archivo de notas/calificaciones desde sistema
// PARAMETROS: path = ruta del archivo notas.lfp
//             grades = vector para almacenar datos
// RETORNA: true si exitoso, false si error
// REQUISITOS TECNICOS IMPLEMENTADOS:
//   - Lectura de archivos mediante clases nativas (ifstream)
//   - Separación de datos mediante split()
//   - Estructuras de control (if para validar, while para iterar)
//   - Colecciones: vector<Grade> para almacenar registros
bool loadGrades(const string &path, vector<Grade> &grades) {
    // REQUISITO: Lectura de archivos mediante clases nativas (ifstream)
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Error: no se puede abrir el archivo de notas " << path << "\n";
        return false;
    }
    string line;
    
    // REQUISITO: Estructuras de control - ciclo (while)
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        // REQUISITO: Separación y análisis de datos usando split()
        auto parts = split(line, ',');
        if (parts.size() < 5) continue;
        
        // REQUISITO: Colecciones - almacenamiento en vector
        // Tipo: vector<Grade> (colección de registros)
        Grade g;
        g.carnet = stoi(parts[0]);         // Relación: estudiante
        g.codigo_curso = stoi(parts[1]);   // Relación: curso
        g.nota = stod(parts[2]);           // Valor numérico 0-100
        g.ciclo = parts[3];
        g.anio = stoi(parts[4]);
        grades.push_back(g);  // Agregar elemento a colección
    }
    file.close();
    // Mostrar cantidad de registros cargados en consola
    cout << "Notas cargadas: " << grades.size() << "\n";
    return true;
}
