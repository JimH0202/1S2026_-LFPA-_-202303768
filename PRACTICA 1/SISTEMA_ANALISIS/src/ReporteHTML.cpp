// ============================================================
// ARCHIVO: ReporteHTML.cpp
// DESCRIPCION: Implementacion de 5 reportes HTML analíticos
// FUNCIONALIDADES:
//   - Relacionar datos de 3 archivos (estudiantes, cursos, notas)
//   - Calcular estadísticas integradas (promedio, varianza, etc)
//   - Generar tablas HTML formateadas
//   - Almacenar reportes a archivos del sistema
// REPORTES: 5 análisis diferentes del sistema académico
// ============================================================

// ============================================================
// REQUISITOS OBLIGATORIOS IMPLEMENTADOS EN ESTE ARCHIVO:
// GENERACION DE REPORTES HTML
//    - reportStatsByCourse(): Línea 47-85
//      Genera: reportes/reporte_curso.html
//      Campos: Curso, Estudiantes, Promedio, Max, Min, Desv, Mediana
//    - reportPerformanceByStudent(): Línea 88-150
//      Genera: reportes/reporte_estudiante.html
//      Campos: Carnet, Nombre, Carrera, Semestre, Promedio, Aprob, Reprob, Creditos
//    - reportTop10(): Línea 153-210
//      Genera: reportes/reporte_top10.html
//      Campos: Posición, Carnet, Nombre, Carrera, Semestre, Promedio (descendente)
//    - reportCoursesReprobation(): Línea 213-275
//      Genera: reportes/reporte_reprobacion.html
//      Campos: Código, Curso, Total, Aprobados, Reprobados, % (descendente)
//    - reportAnalysisByCareer(): Línea 278-285
//      Genera: reportes/reporte_carrera.html
//      Campos: Carrera, Estudiantes, Promedio, Cursos, Distribución
//
// RELACION DE INFORMACION ENTRE MULTIPLES ARCHIVOS
//    - Student → Grade: Relación por CARNET (línea 150-159)
//    - Course → Grade: Relación por CODIGO_CURSO (línea 62-68)
//    - Student → Course: Relación implícita por CARRERA
//    - Algoritmo: Búsqueda lineal en vectores de datos
// ============================================================

#include "../include/ReporteHTML.h"
#include "../include/Estadisticas.h"  // Para calculos estadisticos
#include <fstream>      // Para escribir archivos HTML
#include <algorithm>    // Para funciones de busqueda y ordenamiento
#include <map>          // Para mapas de datos agregados
#include <set>          // Para conjuntos unicos (sin duplicados)
#include <iostream>     // Para mensajes de consola

using namespace std;

// FUNCION AUXILIAR: joinPath()
// PROPOSITO: Construir rutas de archivos OS-independientes
// PARAMETROS: dir = directorio, file = nombre archivo
// RETORNA: Ruta completa con separador apropiado (Windows: \, Unix: /)
// USO: Crear rutas para guardar reportes HTML
static string joinPath(const string &dir, const string &file) {
    if (dir.empty()) return file;               // Si dir vacío, retornar solo filename
    char sep = '\\';                             // Separador Windows
    string out = dir;
    if (out.back() != sep && out.back() != '/') out += sep;  // Agregar separador si falta
    out += file;
    return out;
}

// ============================================================
// REPORTE #1: reportStatsByCourse()
// PROPOSITO: Generar estadísticas por cada curso
// DATOS RELACIONADOS:
//   - students: obtener enrolled students por curso (relacion indirecta)
//   - courses: iterar cada curso disponible
//   - grades: buscar todas las notas del curso
// CALCULOS: Para cada curso - promedio, max, min, desviacion, mediana
// ARCHIVO GENERADO: reporte_curso.html
// TABLA HTML: Curso | Estudiantes | Promedio | Max | Min | Desv | Mediana
// ============================================================
void reportStatsByCourse(const vector<Student>& students, const vector<Course>& courses, const vector<Grade>& grades, const string &outDir) {
    // Construir ruta del archivo de salida
    string filename = joinPath(outDir, "reporte_curso.html");
    // Abrir archivo para escritura
    ofstream out(filename);
    // Escribir encabezado HTML con title y encoding
    out << "<html><head><meta charset=\"utf-8\"><title>Estadísticas por Curso</title></head><body>";
    out << "<h1>Estadísticas Generales por Curso</h1>";
    // Crear tabla HTML con encabezados
    out << "<table border=\"1\"><tr><th>Curso</th><th>Estudiantes</th><th>Promedio</th><th>Max</th><th>Min</th><th>Desviación</th><th>Mediana</th></tr>";
    
    // Iterar cada curso disponible en el vector courses
    for (const auto &c : courses) {
        // Buscar todas las notas de este curso (relacion codigo_curso)
        vector<double> notas;
        for (const auto &g : grades) {
            // Si la nota pertenece a este curso, agregar a lista
            if (g.codigo_curso == c.codigo) {
                notas.push_back(g.nota);
            }
        }
        // Si el curso no tiene notas, no mostrar en reporte
        if (notas.empty()) continue;
        
        // Calcular estadísticas usando funciones de Estadisticas.cpp
        double avg = average(notas);    // Promedio
        double mx = *max_element(notas.begin(), notas.end());   // Maximo
        double mn = *min_element(notas.begin(), notas.end());   // Minimo
        double sd = stddev(notas);      // Desviacion estandar
        double med = median(notas);     // Mediana
        
        // Escribir fila de tabla HTML con datos del curso
        out << "<tr><td>" << c.nombre << "</td><td>" << notas.size() << "</td><td>" << avg << "</td><td>" << mx << "</td><td>" << mn << "</td><td>" << sd << "</td><td>" << med << "</td></tr>";
    }
    
    // Cerrar tabla y documento HTML
    out << "</table></body></html>";
    // Mostrar path de archivo generado en consola
    cout << "Reporte generado: " << filename << "\n";
}

// ============================================================
// REPORTE #2: reportPerformanceByStudent()
// PROPOSITO: Analizar rendimiento academico por estudiante
// DATOS RELACIONADOS:
//   - students: iterar cada estudiante
//   - courses: obtener creditos por curso
//   - grades: buscar notas del estudiante (relacion carnet)
// CALCULOS: Para cada estudiante - promedio, aprobados, reprobados, creditos
// ARCHIVO GENERADO: reporte_estudiante.html
// TABLA HTML: Carnet | Nombre | Carrera | Semestre | Prom | Aprob | Reprob | Creditos
// CRITERIO APROBACION: nota >= 61
// ============================================================
void reportPerformanceByStudent(const vector<Student>& students, const vector<Course>& courses, const vector<Grade>& grades, const string &outDir) {
    // Construir ruta del archivo
    string filename = joinPath(outDir, "reporte_estudiante.html");
    // Abrir archivo para escritura
    ofstream out(filename);
    // Escribir encabezado HTML
    out << "<html><head><meta charset=\"utf-8\"><title>Rendimiento por Estudiante</title></head><body>";
    out << "<h1>Rendimiento por Estudiante</h1>";
    // Crear tabla HTML con encabezados
    out << "<table border=\"1\"><tr><th>Carnet</th><th>Nombre</th><th>Carrera</th><th>Semestre</th><th>Promedio</th><th>APROBADOS</th><th>REPROBADOS</th><th>Créditos</th></tr>";
    
    // Mapeo: codigo_curso -> creditos (para calcular creditos aprobados)
    map<int,int> credits;
    for (auto &c : courses) 
        credits[c.codigo] = c.creditos;  // Relacion: codigo curso -> creditos
    
    // Iterar cada estudiante
    for (const auto &s : students) {
        // Buscar todas las notas del estudiante (relacion carnet)
        vector<double> notas;
        int aprob = 0;       // Contador cursos aprobados
        int repro = 0;       // Contador cursos reprobados
        int creditos = 0;    // Suma de creditos aprobados
        
        // Buscar todas las calificaciones del estudiante
        for (auto &g : grades) {
            if (g.carnet == s.carnet) {  // Relacionar por carnet
                notas.push_back(g.nota);
                // Contar aprobados (nota >= 61) y reprobados
                if (g.nota >= 61) {
                    aprob++;
                    creditos += credits[g.codigo_curso];  // Sumar creditos
                } else 
                    repro++;
            }
        }
        
        // Si no tiene notas, no mostrar en reporte
        if (notas.empty()) continue;
        
        // Calcular promedio del estudiante
        double avg = average(notas);
        
        // Escribir fila de tabla HTML con datos del estudiante
        out << "<tr><td>"<< s.carnet <<"</td><td>"<< s.nombre <<" "<< s.apellido <<"</td><td>"<< s.carrera <<"</td><td>"<< s.semestre <<"</td><td>"<< avg <<"</td><td>"<< aprob <<"</td><td>"<< repro <<"</td><td>"<< creditos <<"</td></tr>";
    }
    
    // Cerrar tabla y documento HTML
    out << "</table></body></html>";
    // Mostrar path de archivo generado en consola
    cout << "Reporte generado: " << filename << "\n";
}

// ============================================================
// REPORTE #3: reportTop10()
// PROPOSITO: Ranking de los 10 mejores estudiantes
// DATOS RELACIONADOS:
//   - students: en el ranking
//   - grades: buscar notas (relacion carnet)
// CALCULOS: Para cada estudiante - promedio global
// PROCESAMIENTO: Ordenar descendente, mostrar top 10
// ARCHIVO GENERADO: reporte_top10.html
// TABLA HTML: Posicion | Carnet | Nombre | Carrera | Semestre | Promedio
// ORDENAMIENTO: Promedio descendente (mejor primero)
// ============================================================
void reportTop10(const vector<Student>& students, const vector<Course>& courses, const vector<Grade>& grades, const string &outDir) {
    // Vector de pares: (promedio, carnet) para ranking
    vector<pair<double,int>> avgCarnet;
    
    // Calcular promedio de cada estudiante
    for (auto &s : students) {
        // Buscar todas las notas del estudiante
        vector<double> notas;
        for (auto &g: grades) 
            if (g.carnet == s.carnet)  // Relacionar por carnet
                notas.push_back(g.nota);
        
        // Si tiene notas, agregar a ranking
        if (!notas.empty()) {
            avgCarnet.push_back({average(notas), s.carnet});
        }
    }
    
    // Ordenar por promedio descendente (mayor primero)
    // IMPLEMENTACION: ALGORITMO DE ORDENAMIENTO EFICIENTE
    // Algoritmo: IntroSort (Introspective Sort) de STL
    // Complejidad: O(n log n) en la mayoría de casos
    // Mecanismo: Híbrido que combina QuickSort + HeapSort + InsertionSort
    // Ventaja: Evita degradación a O(n²) de QuickSort con datos patologicos
    // Parámetro: greater<>() = Ordena descendente (mayor a menor)
    // Uso: Limitar a top 10 después del ordenamiento
    sort(avgCarnet.begin(), avgCarnet.end(), greater<>());
    
    // Construir ruta del archivo
    string filename = joinPath(outDir, "reporte_top10.html");
    // Abrir archivo para escritura
    ofstream out(filename);
    // Escribir encabezado HTML con gráfico Chart.js
    out << "<html><head><meta charset=\"utf-8\"><title>Top 10</title>";
    out << "<script src=\"https://cdn.jsdelivr.net/npm/chart.js\"></script>";  // CDN Chart.js
    out << "</head><body>";
    out << "<h1>Top 10 Mejores Estudiantes</h1>";
    // Crear tabla HTML con encabezados
    out << "<table border=\"1\"><tr><th>Pos</th><th>Carnet</th><th>Nombre</th><th>Carrera</th><th>Semestre</th><th>Promedio</th></tr>";
    
    // Variables para gráfico Chart.js
    string chartLabels = "[";
    string chartData = "[";
    int posicion = 0;
    
    // Iterar solo los primeros 10 estudiantes
    for (size_t i=0;i<avgCarnet.size() && i<10;i++) {
        posicion = i + 1;
        int carnet = avgCarnet[i].second;
        double avg = avgCarnet[i].first;
        
        // Agregar datos para gráfico
        if (i > 0) { chartLabels += ","; chartData += ","; }
        chartLabels += "\"Pos " + to_string(posicion) + "\"";
        chartData += to_string(avg);
        
        // Buscar informacion del estudiante en vector students
        auto it = find_if(students.begin(), students.end(), 
                          [&](const Student &st){ return st.carnet == carnet; });
        
        if (it!=students.end()) {
        // Escribir fila de tabla HTML con datos del estudiante
            out << "<tr><td>"<<posicion<<"</td><td>"<<it->carnet<<"</td><td>"<<it->nombre<<" "<<it->apellido<<"</td><td>"<<it->carrera<<"</td><td>"<<it->semestre<<"</td><td>"<<avg<<"</td></tr>";
        }
    }
    
    chartLabels += "]";
    chartData += "]";
    
    // Cerrar tabla y agregar gráfico Chart.js
    out << "</table><br>";
    out << "<h2>Gráfico: Promedio de Top 10 Estudiantes</h2>";
    out << "<canvas id=\"topChart\" width=\"400\" height=\"100\"></canvas>";
    out << "<script>";
    out << "const ctx = document.getElementById('topChart').getContext('2d');";
    out << "const topChart = new Chart(ctx, {";
    out << "  type: 'bar',";
    out << "  data: {";
    out << "    labels: " << chartLabels << ",";
    out << "    datasets: [{";
    out << "      label: 'Promedio de Calificación',";
    out << "      data: " << chartData << ",";
    out << "      backgroundColor: 'rgba(75, 192, 192, 0.5)',";
    out << "      borderColor: 'rgba(75, 192, 192, 1)',";
    out << "      borderWidth: 1";
    out << "    }]";
    out << "  },";
    out << "  options: { responsive: true, scales: { y: { beginAtZero: true, max: 100 } } }";
    out << "});";
    out << "</script>";
    out << "</body></html>";
    
    // Mostrar path de archivo generado en consola
    cout << "Reporte generado: " << filename << " (con gráfico Chart.js)\n";
}

void reportCoursesReprobation(const vector<Student>& students, const vector<Course>& courses, const vector<Grade>& grades, const string &outDir) {
    struct Stats { int total=0, apr=0, rep=0; };
    map<int,Stats> data;
    for (auto &g : grades) {
        auto &st = data[g.codigo_curso];
        st.total++;
        if (g.nota >= 61) st.apr++; else st.rep++;
    }
    vector<pair<double,int>> order;
    for (auto &p: data) {
        double perc = p.second.total>0 ? (100.0*p.second.rep/p.second.total) : 0;
        order.push_back({perc,p.first});
    }
    
    // IMPLEMENTACION: ALGORITMO DE ORDENAMIENTO EFICIENTE
    // Algoritmo: IntroSort (Introspective Sort) de STL
    // Complejidad: O(n log n) en promedio y O(n log n) en peor caso
    // Mecanismo: Combina QuickSort + HeapSort + InsertionSort inteligentemente
    // Criterio: Ordena por porcentaje de reprobación (descendente)
    // Parámetro: greater<>() = Mayor porcentaje primero
    sort(order.begin(), order.end(), greater<>());
    
    string filename = joinPath(outDir, "reporte_reprobacion.html");
    ofstream out(filename);
    out << "<html><head><meta charset=\"utf-8\"><title>Reprobación</title>";
    out << "<script src=\"https://cdn.jsdelivr.net/npm/chart.js\"></script>";  // CDN Chart.js
    out << "</head><body>";
    out << "<h1>Cursos con Mayor Índice de Reprobación</h1>";
    out << "<table border=\"1\"><tr><th>Código</th><th>Curso</th><th>Total</th><th>Aprobados</th><th>Reprobados</th><th>% Reprobación</th></tr>";
    
    // Variables para gráfico Chart.js
    string chartLabels = "[";
    string chartData = "[";
    bool first = true;
    
    for (auto &pr : order) {
        int code = pr.second;
        auto it = find_if(courses.begin(), courses.end(), [&](const Course &c){ return c.codigo==code; });
        if (it==courses.end()) continue;
        auto &st = data[code];
        double perc = st.total>0 ? (100.0*st.rep/st.total) : 0;
        
        // Agregar datos para gráfico (límite: 10 cursos)
        if (chartData.length() < 500) {
            if (!first) { chartLabels += ","; chartData += ","; }
            chartLabels += "\"" + it->nombre + "\"";
            chartData += to_string((int)perc);
            first = false;
        }
        
        out << "<tr><td>"<<code<<"</td><td>"<<it->nombre<<"</td><td>"<<st.total<<"</td><td>"<<st.apr<<"</td><td>"<<st.rep<<"</td><td>"<<perc<<"%</td></tr>";
    }
    
    chartLabels += "]";
    chartData += "]";
    
    // Agregar gráfico Chart.js
    out << "</table><br>";
    out << "<h2>Gráfico: Índice de Reprobación por Curso</h2>";
    out << "<canvas id=\"repChart\" width=\"400\" height=\"100\"></canvas>";
    out << "<script>";
    out << "const ctx2 = document.getElementById('repChart').getContext('2d');";
    out << "const repChart = new Chart(ctx2, {";
    out << "  type: 'bar',";
    out << "  data: {";
    out << "    labels: " << chartLabels << ",";
    out << "    datasets: [{";
    out << "      label: '% Reprobación',";
    out << "      data: " << chartData << ",";
    out << "      backgroundColor: 'rgba(255, 99, 132, 0.5)',";
    out << "      borderColor: 'rgba(255, 99, 132, 1)',";
    out << "      borderWidth: 1";
    out << "    }]";
    out << "  },";
    out << "  options: { responsive: true, scales: { y: { beginAtZero: true, max: 100 } } }";
    out << "});";
    out << "</script>";
    out << "</body></html>";
    cout << "Reporte generado: " << filename << " (con gráfico Chart.js de reprobación)\n";
}

void reportAnalysisByCareer(const vector<Student>& students, const vector<Course>& courses, const vector<Grade>& grades, const string &outDir) {
    map<string, vector<int>> studentsByCareer;
    map<string, vector<double>> careerGrades;
    map<string,set<int>> careerCourses;
    map<string,map<int,int>> distribution;
    for (auto &s: students) {
        studentsByCareer[s.carrera].push_back(s.carnet);
        distribution[s.carrera][s.semestre]++;
    }
    for (auto &g: grades) {
        auto it = find_if(students.begin(), students.end(), [&](const Student &s){ return s.carnet==g.carnet; });
        if (it!=students.end()) {
            careerGrades[it->carrera].push_back(g.nota);
        }
    }
    for (auto &c : courses) {
        careerCourses[c.carrera].insert(c.codigo);
    }
    string filename = joinPath(outDir, "reporte_carrera.html");
    ofstream out(filename);
    out << "<html><head><meta charset=\"utf-8\"><title>Análisis por Carrera</title></head><body>";
    out << "<h1>Análisis por Carrera</h1>";
    out << "<table border=\"1\"><tr><th>Carrera</th><th>Estudiantes</th><th>Promedio</th><th>Cursos</th><th>Distribución por semestre</th></tr>";
    for (auto &p : studentsByCareer) {
        string carrera = p.first;
        int total = p.second.size();
        double avg = average(careerGrades[carrera]);
        int cursosCount = careerCourses[carrera].size();
        string dist="";
        for (auto &d : distribution[carrera]) {
            dist += to_string(d.first) + ":" + to_string(d.second) + " ";
        }
        out << "<tr><td>"<<carrera<<"</td><td>"<<total<<"</td><td>"<<avg<<"</td><td>"<<cursosCount<<"</td><td>"<<dist<<"</td></tr>";
    }
    out << "</table></body></html>";
    cout << "Reporte generado: " << filename << "\n";
}
