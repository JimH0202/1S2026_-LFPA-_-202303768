// ============================================================
// ARCHIVO: ReporteHTML.h
// DESCRIPCION: Declara funciones para generacion de reportes HTML
// FUNCIONALIDADES:
//   - Generar 5 reportes analíticos en formato HTML
//   - Relacionar datos de tres archivos (estudiantes, cursos, notas)
//   - Calcular estadísticas integradas
//   - Almacenar reportes en archivos del sistema
// ============================================================

#pragma once

#include <vector>
#include <string>
#include "FileManager.h"

// REPORTE 1: Estadísticas por Curso
// Muestra: promedio, max, min, desviación, mediana por cada curso
void reportStatsByCourse(const std::vector<Student>& students,
                         const std::vector<Course>& courses,
                         const std::vector<Grade>& grades,
                         const std::string &outDir);

// REPORTE 2: Rendimiento por Estudiante
// Muestra: promedio, cursos aprobados/reprobados, créditos por estudiante
void reportPerformanceByStudent(const std::vector<Student>& students,
                                const std::vector<Course>& courses,
                                const std::vector<Grade>& grades,
                                const std::string &outDir);

// REPORTE 3: Top 10 Mejores Estudiantes
// Muestra: ranking de 10 estudiantes con mayores promedios
void reportTop10(const std::vector<Student>& students,
                 const std::vector<Course>& courses,
                 const std::vector<Grade>& grades,
                 const std::string &outDir);

// REPORTE 4: Cursos con Mayor Reprobación
// Muestra: porcentaje de reprobación por curso
void reportCoursesReprobation(const std::vector<Student>& students,
                              const std::vector<Course>& courses,
                              const std::vector<Grade>& grades,
                              const std::string &outDir);

// REPORTE 5: Análisis por Carrera
// Muestra: promedio de carrera, estudiantes, cursos, distribución por semestre
void reportAnalysisByCareer(const std::vector<Student>& students,
                            const std::vector<Course>& courses,
                            const std::vector<Grade>& grades,
                            const std::string &outDir);

void reportAnalysisByCareer(const std::vector<Student>& students,
                            const std::vector<Course>& courses,
                            const std::vector<Grade>& grades,
                            const std::string &outDir);
