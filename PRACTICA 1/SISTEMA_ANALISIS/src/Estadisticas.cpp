// ============================================================
// ARCHIVO: Estadisticas.cpp
// DESCRIPCION: Implementacion de funciones estadisticas
// FUNCIONALIDADES:
//   - Procesar arrays de calificaciones numericas
//   - Realizar calculos avanzados (promedio, varianza, desvio)
//   - Usar librerias estandar (algorithm, cmath)
// ============================================================

// ============================================================
// REQUISITOS OBLIGATORIOS IMPLEMENTADOS EN ESTE ARCHIVO:
// CALCULOS ESTADISTICOS
//    - average(): Promedio = suma / cantidad
//    - variance(): Varianza = Σ(xi - promedio)² / n
//    - stddev(): Desviación = √varianza
//    - median(): Mediana = valor central (datos ordenados)
//    - Uso: En todos los 5 reportes HTML (ReporteHTML.cpp)
//    - Líneas 19-27: average() - promedio aritmético
//    - Líneas 32-44: variance() - dispersión de datos
//    - Líneas 49-55: stddev() - desviación estándar
//    - Líneas 60-73: median() - valor medio ordenado
// ============================================================

#include "../include/Estadisticas.h"
#include <algorithm>  // Para funciones sort, max_element
#include <cmath>       // Para funcion sqrt (raiz cuadrada)

using namespace std;

// FUNCION: average()
// PROPOSITO: Calcular promedio aritmetico de notas
// CALCULO: suma de elementos / cantidad de elementos
// RETORNA: 0.0 si vector vacio, promedio si tiene datos
// USO: Se invoca para cada grupo de datos (curso, estudiante, etc)
double average(const vector<double> &vals) {
    if (vals.empty()) return 0.0;    // Validar vector no vacio
    double sum = 0;
    // Sumar todos los valores
    for (auto v : vals) sum += v;
    // Retornar suma / cantidad
    return sum / vals.size();
}

// FUNCION: variance()
// PROPOSITO: Calcular varianza (dispersion de datos)
// CALCULO: promedio de cuadrados de desviaciones
// FORMULA: suma((xi - promedio)^2) / n
// RETORNA: 0 si vector vacio, varianza si tiene datos
// USO: Medida de dispersion de notas alrededor del promedio
double variance(const vector<double> &vals) {
    double avg = average(vals);      // Calcular promedio primero
    double var = 0;
    // Calcular suma de desviaciones al cuadrado
    for (auto v : vals) var += (v - avg) * (v - avg);
    // Retornar promedio de desviaciones
    return vals.empty() ? 0 : var / vals.size();
}

// FUNCION: stddev()
// PROPOSITO: Calcular desviacion estandar
// CALCULO: raiz cuadrada de la varianza
// FORMULA: sqrt(varianza)
// RETORNA: Desviacion estandar (unidades de medida originales)
// USO: Mide cuanto varían las notas respecto al promedio
double stddev(const vector<double> &vals) {
    // Usa sqrt de libreria cmath
    return sqrt(variance(vals));
}

// FUNCION: median()
// PROPOSITO: Calcular mediana (valor central ordenado)
// CALCULO: si cantidad impar -> elemento central
//          si cantidad par -> promedio de 2 elementos centrales
// NOTA: Recibe copia del vector (se ordena sin afectar original)
// RETORNA: 0 si vacio, mediana si tiene datos
// USO: Valor representativo no afectado por extremos
double median(vector<double> vals) {
    if (vals.empty()) return 0;
    // Ordenar los valores (usa algoritmo sort de libreria)
    sort(vals.begin(), vals.end());
    size_t n = vals.size();
    // Si cantidad es impar, retornar elemento del medio
    if (n % 2 == 1) return vals[n/2];
    // Si cantidad es par, retornar promedio de 2 elementos del medio
    return (vals[n/2 -1] + vals[n/2]) / 2.0;
}
