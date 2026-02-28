# Manual de Usuario

Este documento explica cómo utilizar el sistema de análisis académico desde
la perspectiva del usuario final.

## Requisitos previos

- Contar con el ejecutable `app.exe` compilado (ver sección de instalación).
- Disponer de los archivos de datos en la carpeta `data/`:
  - `estudiantes.lfp`
  - `cursos.lfp`
  - `notas.lfp`
- El programa se ejecuta en consola (PowerShell, CMD, terminal de Linux/macOS).

## Ejecución

1. Abra una terminal y navegue hasta el directorio raíz del proyecto:
   ```bash
   cd "c:/Users/jimhu/Desktop/1S2026_-LFPA-_-202303768/PRACTICA 1/SISTEMA_ANALISIS"
   ```
2. Inicie el programa:
   ```bash
   ./app.exe         # en Windows
   ./app             # en Linux/macOS
   ```
3. Aparecerá el menú principal con las opciones numeradas del 1 al 9.

## Menú e instrucciones

Al ejecutar, verá algo similar a:

```
==========================================
SISTEMA DE ANALISIS ACADEMICO
==========================================
1. Cargar archivo de estudiantes
2. Cargar archivo de cursos
3. Cargar archivo de notas
4. Generar Reporte: Estadisticas por Curso
5. Generar Reporte: Rendimiento por Estudiante
6. Generar Reporte: Top 10 Mejores Estudiantes
7. Generar Reporte: Cursos con Mayor Reprobacion
8. Generar Reporte: Analisis por Carrera
9. Salir
```

### Ingresar opciones

- Debe escribir un número entero entre 1 y 9 y presionar Enter.
- El programa valida la entrada; si escribe texto o un número fuera de rango
  mostrará un mensaje de error y volverá a pedir la opción.

### Cargar archivos

Opciones 1–3 piden la ruta del archivo correspondiente. Puede usar rutas
relativas, por ejemplo:

```
Ruta del archivo estudiantes: data/estudiantes.lfp
```

Si el archivo no existe o no se puede abrir, se muestra un mensaje de error.

> **Consejo**: dado que el ejecutable suele estar en la carpeta raíz, la ruta
> relativa `data/archivo.lfp` funciona sin necesidad de `..`.

### Generar reportes

Una vez que haya cargado los tres archivos, elija las opciones 4–8 para crear
reportes en formato HTML. Estos se escriben en la carpeta `reportes/` con
nombres como `reporte_curso.html`, `reporte_estudiante.html`, etc.

Abrir los reportes:
- Use cualquier navegador web (Chrome, Edge, Firefox) y arrastre el archivo.
- Ejemplo: `reportes/reporte_curso.html` para ver estadísticas por curso.

### Salir

Seleccione `9` para cerrar el programa de manera segura.

## Formato de los archivos de entrada

Cada archivo `.lfp` debe contener líneas de texto con campos separados por
comas. Los encabezados no son obligatorios pero ayudan a verificar el orden.

- `estudiantes.lfp`: `Carnet,Nombre,Apellido,Carrera,Semestre`
- `cursos.lfp`: `Codigo,Nombre,Creditos,Semestre,Carrera`
- `notas.lfp`: `Carnet,CodigoCurso,Nota,Ciclo,Anio`

Si un campo faltante, número incorrecto o línea vacía, el programa ignorará la
línea y seguirá procesando.

## Solución de problemas

- **No se abre el archivo**: Verifique la ruta y permisos.
- **Menú se bloquea**: Asegúrese de ingresar sólo números; la validación del main no permite otra entrada que no sea una opción dentro del menú (solo número)
- **Reporte vacío**: Quizá no se cargaron los datos o las notas no corresponden
a los cursos/estudiantes.

## Ejemplo de uso

1. Ejecutar `app.exe`.
2. Elegir `1`; ingresar `data/estudiantes.lfp`.
3. Elegir `2`; ingresar `data/cursos.lfp`.
4. Elegir `3`; ingresar `data/notas.lfp`.
5. Elegir `4` para generar el primer reporte.
6. Abrir `reportes/reporte_curso.html` en el navegador.
7. Repetir con otras opciones según la necesidad.


