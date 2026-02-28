# VALIDACION DE REPORTES - SISTEMA DE ANALISIS ACADEMICO

**Fecha:** 28 de Febrero de 2026  
**Estado:** TODOS LOS REPORTES CUMPLEN 100%

---

## REPORTE 1: ESTADÍSTICAS GENERALES POR CURSO

**Archivo:** `reporte_curso.html`  
**Función:** `reportStatsByCourse()`

### Especificación vs Implementación

| Campo Requerido | Especificación | Implementación | Estado |
|---|---|---|---|
| **Nombre del curso** | Mostrar nombre del curso | `c.nombre` | |
| **Cantidad de estudiantes** | Cantidad que lo han cursado | `notas.size()` | |
| **Nota promedio** | Promedio de calificaciones | `average(notas)` | |
| **Nota máxima** | Calificación más alta | `max_element(notas)` | |
| **Nota mínima** | Calificación más baja | `min_element(notas)` | |
| **Desviación estándar** | Medida de dispersión | `stddev(notas)` | |
| **Mediana** | Valor central | `median(notas)` | |

### Estructura HTML
```html
<table>
  <tr><th>Curso</th><th>Estudiantes</th><th>Promedio</th><th>Max</th>
      <th>Min</th><th>Desviación</th><th>Mediana</th></tr>
  <tr><td>Algebra</td><td>45</td><td>74.2</td><td>98</td>
      <td>52</td><td>12.3</td><td>75.5</td></tr>
</table>
```

---

## REPORTE 2: RENDIMIENTO POR ESTUDIANTE

**Archivo:** `reporte_estudiante.html`  
**Función:** `reportPerformanceByStudent()`

### Especificación vs Implementación

| Campo Requerido | Especificación | Implementación | Estado |
|---|---|---|---|
| **Nombre completo** | Nombre + Apellido | `s.nombre + " " + s.apellido` | |
| **Carnet** | ID del estudiante | `s.carnet` | |
| **Carrera** | Carrera inscrita | `s.carrera` | |
| **Semestre actual** | Semestre en que está | `s.semestre` | |
| **Promedio general** | Media de todas sus notas | `average(notas)` | |
| **Cursos aprobados** | Cantidad con nota >= 61 | `aprob` (contador) | |
| **Cursos reprobados** | Cantidad con nota < 61 | `repro` (contador) | |
| **Créditos acumulados** | Suma de créditos de cursos aprobados | `creditos` (acumulador) | |

### Criterio de Aprobación
```cpp
if (g.nota >= 61) {
    aprob++;
    creditos += credits[g.codigo_curso];  // Solo suma créditos si aprobó
} else {
    repro++;
}
```

### Estructura HTML
```html
<table>
  <tr><th>Carnet</th><th>Nombre</th><th>Carrera</th><th>Semestre</th>
      <th>Promedio</th><th>APROBADOS</th><th>REPROBADOS</th><th>Créditos</th></tr>
  <tr><td>202012345</td><td>Juan Perez</td><td>Sistemas</td><td>5</td>
      <td>78.5</td><td>18</td><td>2</td><td>56</td></tr>
</table>
```

---

## REPORTE 3: TOP 10 MEJORES ESTUDIANTES

**Archivo:** `reporte_top10.html`  
**Función:** `reportTop10()`

### Especificación vs Implementación

| Campo Requerido | Especificación | Implementación | Estado |
|---|---|---|---|
| **Posición** | Número en ranking (1-10) | `i+1` |  |
| **Carnet** | ID del estudiante | `carnet` (de ranking) | |
| **Nombre completo** | Nombre + Apellido | `nombre + " " + apellido` | |
| **Carrera** | Carrera inscrita | `carrera` | |
| **Semestre** | Semestre actual | `semestre` | |
| **Promedio** | Promedio general | `average(notas)` | |

### Ordenamiento
```cpp
// Ordenar descendente por promedio (mejor primero)
sort(avgCarnet.begin(), avgCarnet.end(), greater<>());

// Mostrar solo los primeros 10
for (size_t i=0; i<avgCarnet.size() && i<10; i++) { ... }
```

### Estructura HTML
```html
<table>
  <tr><th>Pos</th><th>Carnet</th><th>Nombre</th><th>Carrera</th>
      <th>Semestre</th><th>Promedio</th></tr>
  <tr><td>1</td><td>202001234</td><td>Laura Garcia</td><td>Ingenieria</td>
      <td>4</td><td>96.2</td></tr>
  <tr><td>2</td><td>202001235</td><td>Carlos Lopez</td><td>Sistemas</td>
      <td>5</td><td>94.8</td></tr>
</table>
```

---

## REPORTE 4: CURSOS CON MAYOR ÍNDICE DE REPROBACIÓN

**Archivo:** `reporte_reprobacion.html`  
**Función:** `reportCoursesReprobation()`

### Especificación vs Implementación

| Campo Requerido | Especificación | Implementación | Estado |
|---|---|---|---|
| **Código del curso** | Código único del curso | `code` | |
| **Nombre del curso** | Nombre del curso | `it->nombre` (búsqueda) | |
| **Total de estudiantes** | Cantidad total | `st.total` | |
| **Cantidad aprobados** | Count con nota >= 61 | `st.apr` | |
| **Cantidad reprobados** | Count con nota < 61 | `st.rep` | |
| **Porcentaje reprobación** | % de estudiantes reprobados | `(100.0*st.rep/st.total)` | |

### Fórmula de Cálculo
```cpp
double perc = st.total>0 ? (100.0*st.rep/st.total) : 0;
// Porcentaje = (Reprobados / Total) * 100
```

### Ordenamiento
```cpp
// Ordenar descendente por % reprobacion (mayor primero)
sort(order.begin(), order.end(), greater<>());
```

### Estructura HTML
```html
<table>
  <tr><th>Código</th><th>Curso</th><th>Total</th><th>Aprobados</th>
      <th>Reprobados</th><th>% Reprobación</th></tr>
  <tr><td>1005</td><td>Calculo II</td><td>52</td><td>35</td>
      <td>17</td><td>32.69%</td></tr>
</table>
```

---

## REPORTE 5: ANÁLISIS POR CARRERA

**Archivo:** `reporte_carrera.html`  
**Función:** `reportAnalysisByCareer()`

### Especificación vs Implementación

| Campo Requerido | Especificación | Implementación | Estado |
|---|---|---|---|
| **Nombre de carrera** | Nombre de la carrera | `carrera` | |
| **Cantidad total de estudiantes** | Total en la carrera | `studentsByCareer[carrera].size()` | |
| **Promedio general de carrera** | Promedio de todas sus notas | `average(careerGrades[carrera])` | |
| **Cantidad de cursos disponibles** | Total de cursos | `careerCourses[carrera].size()` | |
| **Distribución por semestre** | Estudiantes por semestre | `distribution[carrera][semestre]` ||

### Mapeos de Datos
```cpp
// Mapeo 1: Carrera -> Vector de carnets de estudiantes
map<string, vector<int>> studentsByCareer;

// Mapeo 2: Carrera -> Vector de todas las notas
map<string, vector<double>> careerGrades;

// Mapeo 3: Carrera -> Set de códigos de cursos (sin duplicados)
map<string,set<int>> careerCourses;

// Mapeo 4: Carrera -> (Semestre -> Cantidad estudiantes)
map<string,map<int,int>> distribution;
```

### Estructura HTML
```html
<table>
  <tr><th>Carrera</th><th>Estudiantes</th><th>Promedio</th><th>Cursos</th>
      <th>Distribución por semestre</th></tr>
  <tr><td>Ingenieria</td><td>120</td><td>75.3</td><td>48</td>
      <td>1:45 2:38 3:20 4:12 5:5</td></tr>
</table>
```

---

## VALIDACIÓN GENERAL

### Funciones Estadísticas Utilizadas
| Función | Ubicación | Uso |
|---|---|---|
| `average(vals)` | Estadisticas.cpp | Calcula promedio aritmético |
| `variance(vals)` | Estadisticas.cpp | Calcula varianza |
| `stddev(vals)` | Estadisticas.cpp | Calcula desviación estándar |
| `median(vals)` | Estadisticas.cpp | Calcula mediana |

### Relaciones de Datos Correctamente Implementadas
- Estudiantes-Notas: Relación por `carnet`  
- Cursos-Notas: Relación por `codigo_curso`  
- Estudiantes-Carrera: A través del campo `carrera`  
- Estudiantes-Semestre: A través del campo `semestre`  
- Cursos-Carrera: A través del campo `carrera`  

### Archivos Generados
| # | Reporte | Archivo | Ruta |
|---|---|---|---|
| 1 | Estadísticas por Curso | `reporte_curso.html` | `reportes/` |
| 2 | Rendimiento por Estudiante | `reporte_estudiante.html` | `reportes/` |
| 3 | Top 10 Mejores | `reporte_top10.html` | `reportes/` |
| 4 | Mayor Reprobación | `reporte_reprobacion.html` | `reportes/` |
| 5 | Análisis Carrera | `reporte_carrera.html` | `reportes/` |

### Criterios de Aprobación
**Aprobado:** nota >= 61  
**Reprobado:** nota < 61  

---

## CONCLUSIÓN

TODOS LOS 5 REPORTES CUMPLEN 100% CON LAS ESPECIFICACIONES

Cada reporte incluye:
- Todos los campos requeridos
- Cálculos estadísticos correctos
- Relaciones de datos adecuadas
- Ordenamiento según especificación
- Formato HTML con tablas
- Guardado en archivo del sistema
