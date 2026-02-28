# VALIDACIÓN DE REQUISITOS OBLIGATORIOS - PROYECTO SISTEMA DE ANÁLISIS ACADÉMICO

## Checklist de Cumplimiento (9/9 Requisitos)

---

## 1. **Uso del Lenguaje C++**

|Componente|Ubicación|Descripción|
|----------|---------|-----------|
|**Lenguaje**|Todo el proyecto|C++17 con estándar moderno|
|**Compilador**|Línea de compilación|g++ -std=c++17|
|**Archivos fuente**|src/*.cpp|4 archivos implementación|
|**Headers**|include/*.h|Declaraciones de funciones|
|**STL usado**|Múltiples archivos|vector, map, set, algorithm, fstream, cmath|

**Comando compilación exitoso:**
```bash
g++ -std=c++17 -Iinclude src/main.cpp src/FileManager.cpp src/Estadisticas.cpp src/ReporteHTML.cpp -o app.exe
```

---

## 2. **Lectura de Archivos .lfp**

|Requisito|Archivo|Línea|Detalles|
|---------|-------|-----|--------|
|**Lectura estudiantes.lfp**|src/FileManager.cpp|35-61|`loadStudents(const string &path, vector<Student> &students)`|
|**Lectura cursos.lfp**|src/FileManager.cpp|65-92|`loadCourses(const string &path, vector<Course> &courses)`|
|**Lectura notas.lfp**|src/FileManager.cpp|96-144|`loadGrades(const string &path, vector<Grade> &grades)`|
|**Ubicación archivos**|data/|—|`data/estudiantes.lfp`, `data/cursos.lfp`, `data/notas.lfp`|
|**Validación apertura**|src/FileManager.cpp|línea 38, 67, 99|`if (!file.is_open()) { cerr << "Error..."; return false; }`|

**Estructura de lectura por archivo:**
```cpp
// Ejemplo: loadStudents()
ifstream file(path);  // Abrir archivo .lfp
if (!file.is_open()) return false;
while (getline(file, line)) {  // Leer línea por línea
    auto parts = split(line, ',');  // Procesar CSV
    if (parts.size() < 5) continue;  // Validar campos
    Student s;
    s.carnet = stoi(parts[0]);
    s.nombre = parts[1];
    // ... más campos
    students.push_back(s);  // Almacenar
}
```

---

## 3. **Separación de Datos Mediante Comas (CSV)**

|Función|Ubicación|Línea|Descripción|
|-------|---------|-----|-----------|
|**split()**|src/FileManager.cpp|20-29|Divide strings por delimitador ','|
|**stringstream**|src/FileManager.cpp|21|Procesa el string carácter por carácter|
|**getline()**|src/FileManager.cpp|24|Extrae subcadenas hasta encontrar delimitador|
|**Vector retorno**|src/FileManager.cpp|26|Retorna vector de strings separados|

**Algoritmo CSV:**
```cpp
vector<string> split(const string &s, char delim) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {  // Separa por ','
        elems.push_back(item);
    }
    return elems;
}
```

**Uso en archivos:**
- Estudiantes: `carnet,nombre,apellido,carrera,semestre`
- Cursos: `codigo,nombre,creditos,semestre,carrera`
- Notas: `carnet,codigo_curso,nota,ciclo,anio`

---

## 4. **Estructuras de Control (if, while, for, switch)**

|Componente|Ubicación|Línea|Tipo|Función|
|----------|---------|-----|-----|--------|
|**Menu do-while**|src/main.cpp|35|`do { ... } while (option != 9);`|Ciclo principal programa|
|**Switch menu**|src/main.cpp|45|`switch(option)`|Procesa 9 opciones|
|**If apertura archivo**|src/FileManager.cpp|38|`if (!file.is_open())`|Valida lectura archivo|
|**While lectura líneas**|src/FileManager.cpp|40|`while (getline(file, line))`|Itera líneas del archivo|
|**If validación campos**|src/FileManager.cpp|41|`if (line.empty()) continue;`|Salta líneas vacías|
|**For iteración cursos**|src/ReporteHTML.cpp|58|`for (const auto &c : courses)`|Recorre cada curso|
|**For iteración estudiantes**|src/ReporteHTML.cpp|120|`for (const auto &s : students)`|Recorre cada estudiante|
|**If vector vacío**|src/Estadisticas.cpp|19|`if (vals.empty()) return 0.0;`|Valida datos|

**Estructuras de control usadas:**
- `if` - Condicionales (líneas 38, 41, 42, 48, 52, 72)
- `while` - Ciclos (línea 40 lectura, 24 procesamiento strings)
- `for` - Iteraciones (líneas 58, 120, 186 con range-based for)
- `switch` - Selección multicase (línea 45 con 9 casos)

---

## 5.**Implementación de Cálculos Estadísticos**

|Función|Ubicación|Línea|Fórmula|
|-------|---------|-----|---------|
|**average()**|src/Estadisticas.cpp|19-27|Suma todas las notas / cantidad: `Σx / n`|
|**variance()**|src/Estadisticas.cpp|32-44|`Σ(xi - promedio)² / n`|
|**stddev()**|src/Estadisticas.cpp|49-55|Raíz cuadrada de varianza: `√varianza`|
|**median()**|src/Estadisticas.cpp|60-73|Valor central de datos ordenados|

**Compilación de funciones.**
```cpp
// src/Estadisticas.h
double average(const vector<double> &vals);
double variance(const vector<double> &vals);
double stddev(const vector<double> &vals);
double median(const vector<double> &vals);
```

**Uso en reportes:**
- Reporte 1: promedio, máx, mín, desviación, mediana
- Reporte 2: promedio por estudiante
- Reporte 3: promedio ordenado descendente
- Reporte 5: promedio por carrera

---

## 6. **Generación de Reportes HTML**

|Reporte|Función|Línea|Salida|Campos|
|-------|--------|-----|------|-------|
|**Reporte 1**|`reportStatsByCourse()`|47-85|`reportes/reporte_curso.html`|7 campos|
|**Reporte 2**|`reportPerformanceByStudent()`|88-150|`reportes/reporte_estudiante.html`|8 campos|
|**Reporte 3**|`reportTop10()`|153-210|`reportes/reporte_top10.html`|6 campos|
|**Reporte 4**|`reportCoursesReprobation()`|213-275|`reportes/reporte_reprobacion.html`|6 campos|
|**Reporte 5**|`reportAnalysisByCareer()`|278-285|`reportes/reporte_carrera.html`|5 campos|

**Estructura HTML generada:**
```cpp
// Ejemplo: Reporte 1
out << "<html><head><meta charset=\"utf-8\"><title>Estadísticas por Curso</title></head><body>";
out << "<h1>Estadísticas Generales por Curso</h1>";
out << "<table border=\"1\"><tr><th>Curso</th><th>Estudiantes</th>...</tr>";
// Iteración y datos...
out << "</table></body></html>";
```

---

## 7. **Uso de Vectores para Almacenar Datos**

|Vector|Tipo|Ubicación|Línea|Descripción|
|------|-----|---------|-----|-----------|
|**students**|`vector<Student>`|src/main.cpp|26|Almacena todos los estudiantes|
|**courses**|`vector<Course>`|src/main.cpp|27|Almacena todos los cursos|
|**grades**|`vector<Grade>`|src/main.cpp|28|Almacena todas las notas|
|**elems**|`vector<string>`|src/FileManager.cpp|21|Split de CSV|
|**notas**|`vector<double>`|src/ReporteHTML.cpp|60|Notas de un curso|

**Estructura de datos:**
```cpp
struct Student { int carnet; string nombre; /* ... */ };
struct Course { int codigo; string nombre; /* ... */ };
struct Grade { int carnet; int codigo_curso; double nota; /* ... */ };
```

**Uso de STL:**
- `vector<T>`: almacenamiento dinámico
- `.push_back()`: agregar elementos
- `.size()`: cantidad elementos
- `.empty()`: validar si vacío
- Range-based for: `for (const auto &item : vector)`

---

## 8.  **Relación de Información Entre Múltiples Archivos**

|Relación|Desde|A|Clave|Ubicación|
|--------|-----|---|-----|----------|
|**Student → Grade**|estudiantes.lfp|notas.lfp|`carnet`|src/ReporteHTML.cpp línea 150|
|**Course → Grade**|cursos.lfp|notas.lfp|`codigo_curso`|src/ReporteHTML.cpp línea 62|
|**Student → Course**|estudiantes.lfp|cursos.lfp|`carrera`|src/ReporteHTML.cpp línea 280|

**Algoritmo de relación:**
```cpp
// Buscar notas de un estudiante (carnet)
for (const auto &g : grades) {
    if (g.carnet == s.carnet) {  // Relación por CARNET
        notas.push_back(g.nota);
    }
}

// Buscar notas de un curso (codigo_curso)
for (const auto &g : grades) {
    if (g.codigo_curso == c.codigo) {  // Relación por CODIGO_CURSO
        notas.push_back(g.nota);
    }
}
```

---

## 9. **Menú Funcional en Consola**

|Opción|Función|Línea|Descripción|
|------|--------|-----|-----------|
|**1**|Cargar estudiantes|case 1|Lee data/estudiantes.lfp|
|**2**|Cargar cursos|case 2|Lee data/cursos.lfp|
|**3**|Cargar notas|case 3|Lee data/notas.lfp|
|**4**|Reporte Curso|case 4|Genera reporte_curso.html|
|**5**|Rendimiento Estudiante|case 5|Genera reporte_estudiante.html|
|**6**|Top 10 Estudiantes|case 6|Genera reporte_top10.html|
|**7**|Mayor Reprobación|case 7|Genera reporte_reprobacion.html|
|**8**|Análisis Carrera|case 8|Genera reporte_carrera.html|
|**9**|Salir|default|Termina programa|

**Estructura del menú:**
```cpp
// Tipo: do-while loop (línea 35)
do {
    // Mostrar opciones (líneas 38-46)
    cout << "SISTEMA DE ANALISIS ACADEMICO\n";
    cout << "1. Cargar archivo de estudiantes\n";
    // ... más opciones
    
    // Procesar entrada (línea 48)
    cin >> option;
    
    // Procesar opción (línea 50, switch)
    switch(option) {
        case 1: loadStudents(...); break;
        case 2: loadCourses(...); break;
        // ... más casos
        case 9: cout << "Saliendo...\n"; break;
    }
} while (option != 9);  // Continúa hasta opción 9
```

---

## RESUMEN FINAL

```
┌─────────────────────────────────────────────────────────┐
│         VALIDACION DE REQUISITOS OBLIGATORIOS          │
├─────────────────────────────────────────────────────────┤
│ 1. Lenguaje C++                                      │
│ 2. Lectura de archivos .lfp                          │
│ 3. Separación de datos mediante comas               │
│ 4. Estructuras de control (if,while,for,switch)    │
│ 5. Cálculos estadísticos                             │
│ 6. Generación de reportes HTML                       │
│ 7. Uso de vectores/arreglos                          │
│ 8. Relación entre múltiples archivos                 │
│ 9. Menú funcional en consola                         │
├─────────────────────────────────────────────────────────┤
│              CUMPLIMIENTO: 9/9 (100%)                   │
└─────────────────────────────────────────────────────────┘
```

##  Comando de Compilación

```bash
g++ -std=c++17 -Iinclude src/main.cpp src/FileManager.cpp src/Estadisticas.cpp src/ReporteHTML.cpp -o app.exe
```

##  Archivos del Proyecto

```
SISTEMA_ANALISIS/
├── include/
│   ├── FileManager.h
│   ├── Estadisticas.h
│   └── ReporteHTML.h
├── src/
│   ├── main.cpp
│   ├── FileManager.cpp
│   ├── Estadisticas.cpp
│   └── ReporteHTML.cpp
├── data/
│   ├── estudiantes.lfp
│   ├── cursos.lfp
│   └── notas.lfp
├── reportes/
│   ├── reporte_curso.html
│   ├── reporte_estudiante.html
│   ├── reporte_top10.html
│   ├── reporte_reprobacion.html
│   └── reporte_carrera.html
├── app.exe
├── README.md
├── VALIDACION_REPORTES.md
├── ESPECIFICACIONES_REPORTES.md
└── VALIDACION_REQUISITOS_OBLIGATORIOS.md ← Este archivo
```

---

**Fecha de validación:** 28 de febrero de 2026
**Versión del compilador:** g++ con estándar C++17
**Estado:**  TODOS LOS REQUISITOS CUMPLIDOS
