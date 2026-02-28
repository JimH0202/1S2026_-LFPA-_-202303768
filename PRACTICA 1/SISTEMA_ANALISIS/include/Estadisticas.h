// ============================================================
// ARCHIVO: Estadisticas.h
// DESCRIPCION: Declara funciones para calculos estadisticos
// FUNCIONALIDADES:
//   - Realizar calculos estadisticos avanzados
//   - Procesar calificaciones numéricas
//   - Generar métricas para reportes analíticos
// ============================================================

#pragma once

#include <vector>

// Calcula promedio: suma / cantidad de elementos
double average(const std::vector<double> &vals);

// Calcula varianza: promedio de cuadrados de desviaciones
double variance(const std::vector<double> &vals);

// Calcula desviacion estandar: raiz cuadrada de varianza
double stddev(const std::vector<double> &vals);

// Calcula mediana: valor central ordenando los elementos
double median(std::vector<double> vals);
