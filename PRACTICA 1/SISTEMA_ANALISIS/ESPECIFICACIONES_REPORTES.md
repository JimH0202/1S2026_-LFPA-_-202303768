# ESPECIFICACIONES DE REPORTES - VALIDACION FINAL

## REPORTE 1: ESTADÍSTICAS GENERALES POR CURSO

```
Especificación del Usuario:
- nombre del curso ✅
- cantidad de estudiantes que lo han cursado ✅
- nota promedio ✅
- nota máxima ✅
- nota mínima ✅
- desviación estándar ✅
- mediana de las calificaciones ✅

Implementación:
┌─────────────────┬──────────────┬──────────────────────────┐
│ Campo           │ Requerido    │ Implementado             │
├─────────────────┼──────────────┼──────────────────────────┤
│ Curso           │ SI           │ c.nombre                 │
│ Estudiantes     │ SI           │ notas.size()             │
│ Promedio        │ SI           │ average(notas)           │
│ Max             │ SI           │ *max_element(...)        │
│ Min             │ SI           │ *min_element(...)        │
│ Desviación      │ SI           │ stddev(notas)            │
│ Mediana         │ SI           │ median(notas)            │
└─────────────────┴──────────────┴──────────────────────────┘

Archivo: reportes/reporte_curso.html
```

---

## REPORTE 2: RENDIMIENTO POR ESTUDIANTE

```
Especificación del Usuario:
- nombre completo ✅
- carnet ✅
- carrera ✅
- semestre actual ✅
- promedio general de todas sus notas ✅
- cantidad de cursos aprobados (nota >= 61) ✅
- cantidad de cursos reprobados (nota < 61) ✅
- créditos acumulados ✅

Implementación:
┌─────────────────────────┬──────────────┬──────────────────────────┐
│ Campo                   │ Requerido    │ Implementado             │
├─────────────────────────┼──────────────┼──────────────────────────┤
│ Nombre Completo         │ SI           │ s.nombre + " " + apellido│
│ Carnet                  │ SI           │ s.carnet                 │
│ Carrera                 │ SI           │ s.carrera                │
│ Semestre Actual         │ SI           │ s.semestre               │
│ Promedio General        │ SI           │ average(notas)           │
│ Aprobados (>=61)        │ SI           │ contador aprob           │
│ Reprobados (<61)        │ SI           │ contador repro           │
│ Créditos Acumulados     │ SI           │ acumulador creditos      │
└─────────────────────────┴──────────────┴──────────────────────────┘

Criterio Aprobación: nota >= 61 ✅

Archivo: reportes/reporte_estudiante.html
```

---

## REPORTE 3: TOP 10 MEJORES ESTUDIANTES

```
Especificación del Usuario:
- posición (1-10) ✅
- carnet ✅
- nombre completo ✅
- carrera ✅
- semestre ✅
- promedio ✅
- ordenados por promedio descendente ✅

Implementación:
┌──────────────────┬──────────────┬──────────────────────────┐
│ Campo            │ Requerido    │ Implementado             │
├──────────────────┼──────────────┼──────────────────────────┤
│ Posición         │ SI           │ i+1 (0-9 a 1-10)         │
│ Carnet           │ SI           │ carnet (del ranking)     │
│ Nombre Completo  │ SI           │ nombre + " " + apellido  │
│ Carrera          │ SI           │ carrera                  │
│ Semestre         │ SI           │ semestre                 │
│ Promedio         │ SI           │ average(notas)           │
│ Ordenamiento     │ SI           │ sort(..., greater<>())   │
│ Límite a 10      │ SI           │ i < 10 en bucle          │
└──────────────────┴──────────────┴──────────────────────────┘

Algoritmo:
1. Calcular promedio de cada estudiante
2. Crear vector de pares (promedio, carnet)
3. Ordenar descendente por promedio
4. Mostrar solo primeros 10

Archivo: reportes/reporte_top10.html
```

---

## REPORTE 4: CURSOS CON MAYOR ÍNDICE DE REPROBACIÓN

```
Especificación del Usuario:
- código del curso ✅
- nombre del curso ✅
- total de estudiantes ✅
- cantidad de aprobados ✅
- cantidad de reprobados ✅
- porcentaje de reprobación ✅
- ordenados por % reprobación (mayor a menor) ✅

Implementación:
┌─────────────────────────┬──────────────┬──────────────────────────┐
│ Campo                   │ Requerido    │ Implementado             │
├─────────────────────────┼──────────────┼──────────────────────────┤
│ Código Curso            │ SI           │ code                     │
│ Nombre Curso            │ SI           │ it->nombre               │
│ Total Estudiantes       │ SI           │ st.total                 │
│ Aprobados               │ SI           │ st.apr (nota >= 61)      │
│ Reprobados              │ SI           │ st.rep (nota < 61)       │
│ % Reprobación           │ SI           │ (100.0*rep/total)        │
│ Ordenamiento Descen.    │ SI           │ sort(..., greater<>())   │
└─────────────────────────┴──────────────┴──────────────────────────┘

Fórmula de Cálculo:
% Reprobación = (Cantidad Reprobados / Total Estudiantes) * 100

Criterio Aprobación: nota >= 61 ✅

Algoritmo:
1. Contar por curso: total, aprobados, reprobados
2. Calcular % reprobación para cada curso
3. Crear vector de pares (% reprobación, código)
4. Ordenar descendente por % reprobación
5. Mostrar todos los cursos

Archivo: reportes/reporte_reprobacion.html
```

---

## REPORTE 5: ANÁLISIS POR CARRERA

```
Especificación del Usuario:
- nombre de la carrera ✅
- cantidad total de estudiantes ✅
- promedio general de la carrera ✅
- cantidad de cursos disponibles ✅
- distribución de estudiantes por semestre ✅

Implementación:
┌─────────────────────────┬──────────────┬──────────────────────────┐
│ Campo                   │ Requerido    │ Implementado             │
├─────────────────────────┼──────────────┼──────────────────────────┤
│ Nombre Carrera          │ SI           │ carrera (key del map)    │
│ Total Estudiantes       │ SI           │ studentsByCareer.size()  │
│ Promedio General        │ SI           │ average(careerGrades)    │
│ Cantidad Cursos         │ SI           │ careerCourses.size()     │
│ Distribución Semestre   │ SI           │ distribution[semestre]   │
└─────────────────────────┴──────────────┴──────────────────────────┘

Mapeos de Datos Utilizados:
1. studentsByCareer    : carrera → vector de carnets
2. careerGrades        : carrera → vector de notas
3. careerCourses       : carrera → set de códigos (sin duplicados)
4. distribution        : carrera → (semestre → cantidad)

Algoritmo:
1. Iterar estudiantes: agrupar por carrera y semestre
2. Iterar notas: compilar todas por carrera
3. Iterar cursos: contar únicos por carrera
4. Mostrar estadísticas por carrera con distribución

Formato Distribución: "1:45 2:38 3:20 4:12 5:5"
                      (semestre:cantidad de estudiantes)

Archivo: reportes/reporte_carrera.html
```

---

## RESUMEN GENERAL

| Reporte | # Campos | Estado | Archivo |
|---------|----------|--------|---------|
| Estadísticas por Curso | 7 | Completo | reporte_curso.html |
| Rendimiento por Estudiante | 8 | Completo | reporte_estudiante.html |
| Top 10 Mejores | 6 | Completo | reporte_top10.html |
| Mayor Reprobación | 6 | Completo | reporte_reprobacion.html |
| Análisis Carrera | 5 | Completo | reporte_carrera.html |
| **TOTAL** | **32 campos** | **100%** | **5 HTML** |

## CONCLUSIÓN

**Todos los 5 reportes cumplen exactamente con las especificaciones proporcionadas.**

- Todos los campos requeridos están implementados
- Cálculos estadísticos correctos y documentados
- Relaciones de datos adecuadamente programadas
- Criterio de aprobación: nota >= 61 (nota < 61 = reprobado)
- Archivos HTML generados dinámicamente en directorio reportes/
- Menú interactivo de 9 opciones en main.cpp
- Compilación exitosa sin errores
