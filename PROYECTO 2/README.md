TaskScript Analyzer – Proyecto 2 LFP
# TaskScript Analyzer  
### Analizador Léxico, Sintáctico, Semántico y Generador de Reportes para el Lenguaje TaskScript  
**Proyecto 2 — Lenguajes Formales y de Programación**

---

# Tabla de Contenidos
- [Descripción General](#-descripción-general)
- [Arquitectura del Proyecto](#-arquitectura-del-proyecto)
- [Estructura del Repositorio](#-estructura-del-repositorio)
- [Flujo Completo del Sistema](#-flujo-completo-del-sistema)
- [Gramática Oficial de TaskScript](#-gramática-oficial-de-taskscript)
- [Ejemplo de Archivo TaskScript](#-ejemplo-de-archivo-taskscript)
- [Componentes del Sistema](#-componentes-del-sistema)
  - [1. Analizador Léxico](#1-analizador-léxico)
  - [2. Analizador Sintáctico](#2-analizador-sintáctico)
  - [3. Modelo Interno del Tablero](#3-modelo-interno-del-tablero)
  - [4. Árbol de Derivación (Graphviz)](#4-árbol-de-derivación-graphviz)
  - [5. Generador de Reportes HTML](#5-generador-de-reportes-html)
  - [6. Interfaz Gráfica en Qt](#6-interfaz-gráfica-en-qt)
- [Requisitos del Sistema](#-requisitos-del-sistema)
- [Compilación y Ejecución](#️-compilación-y-ejecución)
- [Reportes Generados](#-reportes-generados)
- [Pruebas Realizadas](#-pruebas-realizadas)
- [Capturas Sugeridas](#-capturas-sugeridas)
- [Autor](#-autor)

---

# Descripción General

**TaskScript Analyzer** es una aplicación completa desarrollada en **C++17 + Qt6**, capaz de:

- Analizar archivos escritos en el lenguaje **TaskScript**
- Generar tokens mediante un **AFD manual**
- Validar la estructura mediante un **parser descendente recursivo**
- Construir un **modelo interno del tablero Kanban**
- Generar **reportes HTML profesionales**
- Construir un **árbol de derivación en Graphviz**
- Mostrar resultados en una **interfaz gráfica moderna**

Este proyecto fue desarrollado sin herramientas automáticas como ANTLR, Flex, Bison o Yacc.  
Todo el análisis está implementado **a mano**, cumpliendo los requisitos académicos.

---

# Arquitectura del Proyecto

El sistema sigue una arquitectura modular:
GUI (Qt)
↓
Parser (SyntaxAnalyzer)
↓
Lexer (LexicalAnalyzer)
↓
Modelo (Board, Column, Task)
↓
Reportes HTML + Árbol DOT


Cada módulo está completamente desacoplado y probado individualmente.

---

# Estructura del Repositorio

/src
/lexer
Token.h / Token.cpp
TokenType.h
LexicalAnalyzer.h / LexicalAnalyzer.cpp

/parser
SyntaxAnalyzer.h / SyntaxAnalyzer.cpp

/model
BoardModel.h / BoardModel.cpp

/errors
ErrorManager.h / ErrorManager.cpp

/reports
ReportGenerator.h / ReportGenerator.cpp

/tree
TreeNode.h

/gui
MainWindow.h / MainWindow.cpp
main.cpp

arbol.dot
reporte_kanban.html
reporte_responsables.html
reporte_tokens.html
---

# Flujo Completo del Sistema
┌────────────┐
│   Usuario   │
└──────┬─────┘
│
▼
┌───────────────┐
│   GUI (Qt)     │
└──────┬────────┘
│ texto .task
▼
┌────────────────────┐
│  LexicalAnalyzer    │
│  (AFD manual)       │
└──────┬─────────────┘
│ tokens
▼
┌────────────────────┐
│  SyntaxAnalyzer     │
│  (Descenso Rec.)    │
└──────┬─────────────┘
│ modelo Board
▼
┌────────────────────┐
│  ReportGenerator    │
└──────┬─────────────┘
│ HTML / DOT
▼
┌────────────────────┐
│  Reportes finales   │
└────────────────────┘
---

# Gramática Oficial de TaskScript
```ebnf
<programa>       ::= TABLERO CADENA "{" <columnas> "}" ";"
<columnas>       ::= <columna> <columnas> | <columna>
<columna>        ::= COLUMNA CADENA "{" <tareas> "}" ";"
<tareas>         ::= <tarea> "," <tareas> | <tarea>
<tarea>          ::= tarea ":" CADENA "[" <atributos> "]"
<atributos>      ::= <atributo> "," <atributos> | <atributo>
<atributo>       ::= prioridad ":" <prioridad>
                   | responsable ":" CADENA
                   | fecha_limite ":" FECHA
<prioridad>      ::= ALTA | MEDIA | BAJA

Ejemplo de Archivo TaskScript
TABLERO "Proyecto LFP" {
  COLUMNA "Pendientes" {
    tarea: "Implementar lexer" [
      prioridad: ALTA,
      responsable: "Jimmy",
      fecha_limite: 2026-05-10
    ],
    tarea: "Diseñar GUI" [
      prioridad: MEDIA,
      responsable: "Ana",
      fecha_limite: 2026-05-15
    ]
  };
};

# Componentes del Sistema
1. Analizador Léxico
Implementado con un AFD manual, sin expresiones regulares.

Reconoce:

Palabras reservadas

Cadenas "texto"
Enteros
Fechas AAAA-MM-DD
Delimitadores
Comentarios (si se agregan)

Maneja errores como:
Cadena sin cerrar
Fecha inválida
Caracter no reconocido

2. Analizador Sintáctico
Implementado con descenso recursivo.

Cada regla de la gramática es un método:

Código
programa()
columnas()
columna()
tareas()
tarea()
atributos()
atributo()
prioridad()

Incluye:
Recuperación de errores
Registro de errores sintácticos
Construcción del modelo Board

3. Modelo Interno del Tablero
cpp
struct Task {
    std::string name;
    std::string priority;
    std::string responsible;
    std::string deadline;
};

struct Column {
    std::string name;
    std::vector<Task> tasks;
};

struct Board {
    std::string name;
    std::vector<Column> columns;
};
4. Árbol de Derivación (Graphviz)
Se genera un archivo:

Código
arbol.dot
Con nodos:

Terminales → azul

No terminales → verde

Ejemplo:

Código
<programa>
 ├── TABLERO
 ├── "Proyecto LFP"
 ├── {
 ├── <columnas>
 └── };

5. Generador de Reportes HTML
Reporte 1: Kanban Visual
Columnas lado a lado

Tarjetas con colores según prioridad

Diseño tipo Trello

Reporte 2: Carga por Responsable
Totales

Prioridades

Barra de progreso

Reporte 3: Tokens y Errores
Tablas limpias

Colores alternados

6. Interfaz Gráfica en Qt
Incluye:

Editor de texto

Botón “Cargar archivo”

Botón “Analizar”

Tabla de tokens

Tabla de errores

Botones para abrir reportes

Mensajes de estado

Requisitos del Sistema
Qt 6
C++17
CMake 3.16+
Graphviz (opcional para visualizar DOT)

Compilación y Ejecución
bash
mkdir build
cd build
cmake ..
cmake --build .
./TaskScriptAnalyzer

Reportes Generados
Reporte	Archivo	Descripción
Kanban Visual	reporte_kanban.html	Tablero estilo Trello
Responsables	reporte_responsables.html	Carga por usuario
Tokens/Errores	reporte_tokens.html	Tablas detalladas
Árbol	arbol.dot	Árbol de derivación


Pruebas Realizadas
Archivos válidos
Múltiples columnas

Múltiples tareas

Prioridades variadas

Fechas válidas

Archivos inválidos
Cadenas sin cerrar

Fechas mal formadas

Atributos incompletos

Llaves faltantes

Pruebas GUI
Cargar archivo

Analizar
Mostrar tokens
Mostrar errores
Abrir reportes

Autor
Jimmy Brian Hurtarte López
Proyecto 2 — Lenguajes Formales y de Programación
Universidad San Carlos de Guatemala