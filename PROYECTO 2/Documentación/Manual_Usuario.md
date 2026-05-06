# Manual de Usuario - TaskScriptAnalyzer

## Versión 1.0
**Fecha:** 6 de mayo de 2026  
**Autor:** Equipo de Desarrollo TaskScriptAnalyzer  
**Plataforma:** Windows 10/11, Linux  

---

## Tabla de Contenidos

1. [Introducción](#1-introducción)
2. [Instalación y Compilación](#2-instalación-y-compilación)
3. [Primeros Pasos](#3-primeros-pasos)
4. [Interfaz de Usuario](#4-interfaz-de-usuario)
5. [Creación de Archivos .task](#5-creación-de-archivos-task)
6. [Análisis de Archivos](#6-análisis-de-archivos)
7. [Interpretación de Reportes](#7-interpretación-de-reportes)
8. [Solución de Problemas](#8-solución-de-problemas)
9. [Apéndices](#9-apéndices)

---

## 1. Introducción

### 1.1 ¿Qué es TaskScriptAnalyzer?

TaskScriptAnalyzer es una aplicación de escritorio que permite analizar y visualizar tableros Kanban definidos en un lenguaje específico. El programa realiza análisis léxico y sintáctico del código fuente, genera reportes visuales en formato HTML y proporciona una interfaz intuitiva para la edición y validación de archivos.

### 1.2 Características Principales

- **Análisis Léxico y Sintáctico**: Procesamiento completo de archivos .task
- **Interfaz Gráfica Intuitiva**: Editor integrado con resaltado y validación en tiempo real
- **Reportes Visuales**: Tres tipos de reportes HTML generados automáticamente
- **Manejo de Errores**: Detección y reporte detallado de errores léxicos, sintácticos y semánticos
- **Multiplataforma**: Compatible con Windows y Linux

### 1.3 Requisitos del Sistema

- **Sistema Operativo**: Windows 10/11 o distribuciones Linux modernas
- **Procesador**: Intel/AMD x64 de 64 bits
- **Memoria RAM**: Mínimo 2 GB, recomendado 4 GB
- **Espacio en Disco**: 500 MB para instalación y compilación
- **Dependencias**: Qt6, CMake, compilador C++17

### 1.4 Convenciones del Manual

- **Nota**: Información importante para el usuario
- **Advertencia**: Acciones que pueden causar problemas
- **Consejo**: Recomendaciones para un mejor uso

---

## 2. Instalación y Compilación

### 2.1 Instalación de Dependencias

#### Windows

1. **Instalar Qt6**:
   - Descargue Qt6 desde [qt.io](https://www.qt.io/download)
   - Seleccione la versión Open Source
   - Instale con MinGW 64-bit como toolchain
   - Versión recomendada: Qt 6.5.0 o superior

2. **Instalar CMake**:
   - Descargue desde [cmake.org](https://cmake.org/download/)
   - Versión recomendada: 3.16 o superior
   - Asegúrese de que esté en el PATH del sistema

3. **Instalar MinGW-w64**:
   - Si no viene incluido con Qt, instale desde [mingw-w64.org](https://mingw-w64.org/)
   - Versión recomendada: GCC 16.1+

#### Linux (Ubuntu/Debian)

```bash
# Actualizar el sistema
sudo apt update && sudo apt upgrade

# Instalar Qt6 y herramientas de desarrollo
sudo apt install qt6-base-dev cmake build-essential

# Verificar versiones
qmake6 --version
cmake --version
g++ --version
```

### 2.2 Compilación del Proyecto

#### Paso 1: Descargar el Código Fuente

```bash
# Clonar el repositorio (si aplica)
git clone https://github.com/JimH0202/1S2026_-LFPA-_-202303768.git
cd 1S2026_-LFPA-_-202303768/PROYECTO\ 2
```

#### Paso 2: Configurar el Entorno de Compilación

```bash
# Crear directorio de compilación
mkdir build
cd build

# Configurar con CMake
cmake ..
```

**Nota**: En Windows, si usa Visual Studio, especifique el generador:
```powershell
cmake .. -G "Visual Studio 17 2022"
```

#### Paso 3: Compilar

```bash
# Compilar en Release
cmake --build . --config Release
```

**Tiempo estimado de compilación**: 2-5 minutos dependiendo del hardware.

#### Paso 4: Verificar la Compilación

```bash
# En Windows
./Release/TaskScriptAnalyzer.exe --version

# En Linux
./TaskScriptAnalyzer --version
```

### 2.3 Instalación Opcional

Para una instalación completa (opcional):

```bash
# Instalar en /usr/local (Linux)
sudo cmake --install . --prefix /usr/local

# O crear un enlace simbólico
sudo ln -s $(pwd)/TaskScriptAnalyzer /usr/local/bin/
```

### 2.4 Solución de Problemas de Compilación

**Error: "Qt6 not found"**
- Verifique que Qt6 esté instalado y en el PATH
- En Windows: `echo %PATH% | findstr Qt`
- En Linux: `pkg-config --modversion Qt6Core`

**Error: "CMake Error"**
- Borre el directorio build y reintente
- Verifique versiones mínimas de dependencias

---

## 3. Primeros Pasos

### 3.1 Iniciar la Aplicación

1. Navegue al directorio de compilación
2. Ejecute el binario:
   ```bash
   ./TaskScriptAnalyzer.exe  # Windows
   ./TaskScriptAnalyzer      # Linux
   ```

### 3.2 Pantalla de Bienvenida

Al iniciar, verá la interfaz principal con:
- Área de edición de texto (vacía inicialmente)
- Tabla de tokens (vacía)
- Tabla de errores (vacía)
- Barra de estado: "Listo para analizar"

### 3.3 Cargar un Archivo de Ejemplo

1. Haga clic en **"Cargar"**
2. Seleccione un archivo con extensión `.task`
3. El contenido se cargará en el editor

**Consejo**: Guarde sus archivos con extensión `.task` para fácil identificación.

---

## 4. Interfaz de Usuario

### 4.1 Descripción General

La interfaz principal consta de los siguientes elementos:

```
+---------------------------------------------------+
| TaskScriptAnalyzer v1.0                 [_][□][X] |
+---------------------------------------------------+
| [Cargar] [Analizar]                      [Estado] |
+---------------------------------------------------+
|                                                   |
| Editor de Texto (área principal)                  |
|                                                   |
+---------------------------------------------------+
| Tabla de Tokens                          | Errores|
+---------------------------------------------------+
| Barra de Estado: Listo                            |
+---------------------------------------------------+
```

### 4.2 Barra de Herramientas

- **Cargar**: Abre un diálogo para seleccionar archivo .task
- **Analizar**: Inicia el proceso de análisis léxico y sintáctico
- **Estado**: Muestra el progreso del análisis

### 4.3 Área de Edición

- **Editor de Texto**: Área principal para escribir o editar código .task
- **Soporte**: Sintaxis básica (sin resaltado avanzado)
- **Funciones**: Cortar, copiar, pegar estándar

### 4.4 Tabla de Tokens

Muestra los tokens identificados durante el análisis léxico:

| Columna | Descripción |
|---------|-------------|
| Tipo | Categoría del token (PALABRA_RESERVADA, IDENTIFICADOR, etc.) |
| Lexema | Texto exacto del token |
| Línea | Número de línea |
| Columna | Posición en la línea |

### 4.5 Tabla de Errores

Lista los errores encontrados:

| Columna | Descripción |
|---------|-------------|
| Tipo | Léxico, Sintáctico, Semántico |
| Descripción | Mensaje detallado del error |
| Línea | Ubicación del error |
| Columna | Posición exacta |

### 4.6 Barra de Estado

Muestra mensajes informativos:
- "Cargando archivo..."
- "Analizando..."
- "Análisis completado con X errores"
- "Reportes generados en [ruta]"

**Captura de Pantalla Recomendada**: Interfaz principal con archivo cargado y análisis completado.

---

## 5. Creación de Archivos .task

### 5.1 Sintaxis Básica

Los archivos .task siguen una estructura jerárquica:

```
TABLERO "Nombre del Proyecto" {
    COLUMNA "Nombre de Columna" {
        TAREA "Nombre de Tarea" [
            PRIORIDAD "ALTA|MEDIA|BAJA",
            RESPONSABLE "Nombre del Responsable",
            FECHA_LIMITE "YYYYMMDD",
            DESCRIPCION "Descripción detallada"
        ]
    }
}
```

### 5.2 Elementos Obligatorios

- **TABLERO**: Define el inicio del archivo
- **COLUMNA**: Agrupa tareas relacionadas
- **TAREA**: Define una tarea individual
- **Delimitadores**: `{ } [ ]` y comas donde corresponda

### 5.3 Elementos Opcionales

- **PRIORIDAD**: "ALTA", "MEDIA", "BAJA"
- **RESPONSABLE**: Nombre de la persona asignada
- **FECHA_LIMITE**: Fecha en formato YYYYMMDD
- **DESCRIPCION**: Texto descriptivo de la tarea

### 5.4 Ejemplo Completo 1: Proyecto de Desarrollo Web

```
TABLERO "Sitio Web Corporativo" {
    COLUMNA "POR HACER" {
        TAREA "Diseñar Mockups" [
            PRIORIDAD "ALTA",
            RESPONSABLE "Ana García",
            FECHA_LIMITE "20231215",
            DESCRIPCION "Crear diseños de alta fidelidad para páginas principales"
        ],
        TAREA "Configurar Hosting" [
            PRIORIDAD "MEDIA",
            RESPONSABLE "Carlos López",
            FECHA_LIMITE "20231220",
            DESCRIPCION "Seleccionar proveedor y configurar dominio"
        ]
    }
    COLUMNA "EN PROGRESO" {
        TAREA "Desarrollar Frontend" [
            PRIORIDAD "ALTA",
            RESPONSABLE "María Rodríguez",
            FECHA_LIMITE "20240110",
            DESCRIPCION "Implementar HTML, CSS y JavaScript responsivo"
        ]
    }
    COLUMNA "COMPLETADO" {
        TAREA "Análisis de Requisitos" [
            PRIORIDAD "ALTA",
            RESPONSABLE "Juan Pérez",
            FECHA_LIMITE "20231130",
            DESCRIPCION "Documentar funcionalidades requeridas"
        ]
    }
}
```

### 5.5 Ejemplo 2: Gestión de Proyecto Personal

```
TABLERO "Organización Personal" {
    COLUMNA "TAREAS PENDIENTES" {
        TAREA "Comprar víveres" [
            PRIORIDAD "MEDIA",
            RESPONSABLE "Yo",
            FECHA_LIMITE "20231201",
            DESCRIPCION "Lista de compras semanal"
        ]
    }
    COLUMNA "EN CURSO" {
        TAREA "Estudiar C++" [
            PRIORIDAD "ALTA",
            RESPONSABLE "Yo",
            FECHA_LIMITE "20231231",
            DESCRIPCION "Completar tutoriales avanzados"
        ]
    }
}
```

### 5.6 Reglas de Nomenclatura

- **Nombres de Tablero**: Descriptivos, sin caracteres especiales
- **Nombres de Columnas**: Estados del flujo de trabajo (POR HACER, EN PROGRESO, etc.)
- **Nombres de Tareas**: Acciones concretas y específicas
- **Responsables**: Nombres completos o identificadores únicos

### 5.7 Validación de Sintaxis

**Consejo**: Use el analizador para validar su sintaxis antes de guardar archivos importantes.

---

## 6. Análisis de Archivos

### 6.1 Proceso de Análisis

1. **Cargar Archivo**: Use el botón "Cargar" o escriba directamente
2. **Iniciar Análisis**: Haga clic en "Analizar"
3. **Revisar Resultados**: Verifique tokens y errores
4. **Generar Reportes**: Los reportes se crean automáticamente

### 6.2 Estados del Análisis

- **Éxito**: Sin errores, reportes generados
- **Advertencias**: Errores menores, análisis completado
- **Errores**: Problemas críticos, revisar y corregir

### 6.3 Tiempo de Procesamiento

- **Archivos pequeños** (< 1KB): Instantáneo
- **Archivos medianos** (1-10KB): < 1 segundo
- **Archivos grandes** (> 10KB): 1-5 segundos

### 6.4 Archivos de Salida

Los reportes se generan en el directorio raíz del proyecto:
- `reporte_kanban.html`
- `reporte_responsables.html`
- `reporte_tokens_errores.html`

---

## 7. Interpretación de Reportes

### 7.1 Reporte Kanban (reporte_kanban.html)

**Propósito**: Visualización gráfica del tablero Kanban completo.

**Estructura**:
- **Encabezado**: Nombre del tablero
- **Columnas**: Representadas como contenedores verticales
- **Tareas**: Tarjetas dentro de cada columna

**Elementos Visuales**:
- **Prioridad**: Indicador de color
  - 🔴 Rojo: ALTA
  - 🟡 Amarillo: MEDIA
  - 🟢 Verde: BAJA
- **Información de Tarea**: Nombre, responsable, fecha límite
- **Layout**: Grid responsivo con CSS

**Interpretación**:
- Distribución de carga de trabajo por columnas
- Identificación de cuellos de botella
- Seguimiento del progreso del proyecto

**Captura de Pantalla Recomendada**: Reporte Kanban con múltiples columnas y tareas.

### 7.2 Reporte de Responsables (reporte_responsables.html)

**Propósito**: Análisis de la distribución de tareas por responsable.

**Estructura**:
- **Lista de Responsables**: Cada persona como sección separada
- **Tareas Asignadas**: Lista detallada por responsable
- **Estadísticas**: Conteo de tareas por prioridad

**Elementos Visuales**:
- **Encabezados**: Nombre del responsable
- **Listas**: Tareas agrupadas por estado
- **Colores**: Consistentes con prioridades

**Interpretación**:
- Carga de trabajo por persona
- Balance de responsabilidades
- Identificación de sobrecargas o subutilización

**Ejemplo de Lectura**:
```
Responsable: Ana García
- Tareas en POR HACER: 3 (2 ALTA, 1 MEDIA)
- Tareas en PROGRESO: 1 (1 ALTA)
- Tareas COMPLETADAS: 5 (1 ALTA, 3 MEDIA, 1 BAJA)
```

### 7.3 Reporte de Tokens y Errores (reporte_tokens_errores.html)

**Propósito**: Detalle técnico del análisis léxico y errores encontrados.

**Secciones**:

#### Tabla de Tokens
| # | Tipo | Lexema | Línea | Columna |
|---|------|--------|-------|---------|
| 1 | PALABRA_RESERVADA | TABLERO | 1 | 1 |
| 2 | CADENA | "Proyecto Alpha" | 1 | 9 |

**Interpretación**:
- Verificación de tokenización correcta
- Ubicación exacta de cada elemento
- Ayuda en depuración de sintaxis

#### Tabla de Errores
| Tipo | Descripción | Línea | Columna |
|------|-------------|-------|---------|
| Sintáctico | Falta ',' entre tareas | 15 | 5 |
| Léxico | Carácter inválido '@' | 20 | 12 |

**Interpretación**:
- **Léxico**: Problemas de caracteres no reconocidos
- **Sintáctico**: Errores de estructura gramatical
- **Semántico**: Valores inválidos o inconsistentes

**Consejo**: Use este reporte para corregir errores antes de compartir archivos.

---

## 8. Solución de Problemas

### 8.1 Problemas Comunes

#### "Error al cargar archivo"
- **Causa**: Archivo no encontrado o permisos insuficientes
- **Solución**: Verificar ruta y permisos de lectura

#### "Análisis no genera reportes"
- **Causa**: Errores críticos en el archivo
- **Solución**: Corregir errores mostrados en tabla de errores

#### "Interfaz se congela"
- **Causa**: Archivo muy grande o bucle infinito
- **Solución**: Cerrar aplicación y dividir archivo en partes

### 8.2 Errores de Compilación

#### Qt6 no encontrado
```bash
# Linux
export CMAKE_PREFIX_PATH=/usr/lib/x86_64-linux-gnu/cmake/Qt6
```

#### Librerías faltantes
```bash
# Instalar dependencias faltantes
sudo apt install libqt6widgets6 libqt6core6
```

### 8.3 Optimización de Rendimiento

- **Archivos grandes**: Divida en múltiples tableros
- **Análisis frecuente**: Use modo batch si está disponible
- **Memoria**: Cierre otros programas durante análisis grandes

### 8.4 Soporte Técnico

Para soporte adicional:
- Revise los logs de la aplicación
- Verifique la versión de Qt6 y CMake
- Consulte el Manual Técnico para detalles avanzados

---

## 9. Apéndices

### 9.1 Glosario de Términos

- **Token**: Unidad mínima de significado en el código fuente
- **Lexema**: Representación textual de un token
- **Parser**: Componente que verifica la estructura gramatical
- **Kanban**: Metodología de gestión visual de trabajo
- **Sintaxis**: Reglas que definen la estructura válida del lenguaje

### 9.2 Códigos de Error

| Código | Tipo | Descripción |
|--------|------|-------------|
| LEX001 | Léxico | Carácter no reconocido |
| SYN001 | Sintáctico | Token inesperado |
| SEM001 | Semántico | Valor inválido |

### 9.3 Atajos de Teclado

| Combinación | Acción |
|-------------|--------|
| Ctrl+O | Cargar archivo |
| Ctrl+S | Guardar archivo |
| F5 | Analizar |
| Ctrl+Q | Salir |

### 9.4 Historial de Versiones

- **v1.0** (2026-05-06): Versión inicial completa
  - Análisis léxico y sintáctico
  - Tres tipos de reportes
  - Interfaz gráfica completa

---

**Fin del Manual de Usuario**

Para más información técnica detallada, consulte el Manual Técnico incluido en la carpeta `Documentación/`.

*TaskScriptAnalyzer - Análisis y visualización de tableros Kanban*