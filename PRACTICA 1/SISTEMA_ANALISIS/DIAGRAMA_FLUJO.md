# Diagrama de Flujo del Programa

A continuación se describe el flujo de ejecución general del sistema mediante un
diagrama de flujo. El diagrama usa sintaxis Mermaid, que puede visualizarse en
plataformas que soporten Mermaid (GitHub, VS Code con la extensión apropiada,
etc.).

```mermaid
flowchart TD
    Start([Inicio])
    Menu["Mostrar menú y leer opción"]
    Validar["Validar entrada numérica (1-9)"]
    Option1["Cargar estudiantes"]
    Option2["Cargar cursos"]
    Option3["Cargar notas"]
    Option4["Generar reporte 1"]
    Option5["Generar reporte 2"]
    Option6["Generar reporte 3"]
    Option7["Generar reporte 4"]
    Option8["Generar reporte 5"]
    Exit([Fin])

    Start --> Menu
    Menu --> Validar
    Validar -->|1| Option1
    Validar -->|2| Option2
    Validar -->|3| Option3
    Validar -->|4| Option4
    Validar -->|5| Option5
    Validar -->|6| Option6
    Validar -->|7| Option7
    Validar -->|8| Option8
    Validar -->|9| Exit
    Option1 --> Menu
    Option2 --> Menu
    Option3 --> Menu
    Option4 --> Menu
    Option5 --> Menu
    Option6 --> Menu
    Option7 --> Menu
    Option8 --> Menu
```

## Subdiagramas por opción

Cada opción del menú tiene su propio flujo; a continuación se detalla cada uno.

### Opción 1: Cargar archivo de estudiantes

```mermaid
flowchart TD
    O1Start([Inicio - cargar estudiantes])
    Prompt["Pedir ruta de archivo estudiantes.lfp"]
    LeerPath["Leer entrada (ruta) \n(permite espacios)"]
    Abrir["Intentar abrir con ifstream"]
    ErrorAbrir{"¿Se abrió?"}
    LeerLineas["Leer cada línea no vacía"]
    Split["Separar por comas con split()"]
    ValidaCampos{"¿>=5 campos?"}
    Convertir["Convertir tipos y validar valores"]
    Agregar["Agregar registro al vector"]
    FinO1([Fin carga estudiantes])

    O1Start --> Prompt --> LeerPath --> Abrir --> ErrorAbrir
    ErrorAbrir -->|No| FinO1
    ErrorAbrir -->|Sí| LeerLineas --> Split --> ValidaCampos
    ValidaCampos -->|No| LeerLineas
    ValidaCampos -->|Sí| Convertir --> Agregar --> LeerLineas
    LeerLineas -->|EOF| FinO1
```

### Opción 2: Cargar archivo de cursos

```mermaid
flowchart TD
    O2Start([Inicio - cargar cursos])
    Prompt2["Pedir ruta de archivo cursos.lfp"]
    LeerPath2["Leer entrada (ruta)"]
    Abrir2["Intentar abrir con ifstream"]
    ErrorAbrir2{"¿Se abrió?"}
    LeerLineas2["Leer cada línea no vacía"]
    Split2["Separar por comas con split()"]
    ValidaCampos2{"¿>=5 campos?"}
    Convertir2["Convertir tipos y validar valores"]
    Agregar2["Agregar curso al vector"]
    FinO2([Fin carga cursos])

    O2Start --> Prompt2 --> LeerPath2 --> Abrir2 --> ErrorAbrir2
    ErrorAbrir2 -->|No| FinO2
    ErrorAbrir2 -->|Sí| LeerLineas2 --> Split2 --> ValidaCampos2
    ValidaCampos2 -->|No| LeerLineas2
    ValidaCampos2 -->|Sí| Convertir2 --> Agregar2 --> LeerLineas2
    LeerLineas2 -->|EOF| FinO2
```

### Opción 3: Cargar archivo de notas

```mermaid
flowchart TD
    O3Start([Inicio - cargar notas])
    Prompt3["Pedir ruta de archivo notas.lfp"]
    LeerPath3["Leer entrada (ruta)"]
    Abrir3["Intentar abrir con ifstream"]
    ErrorAbrir3{"¿Se abrió?"}
    LeerLineas3["Leer cada línea no vacía"]
    Split3["Separar por comas con split()"]
    ValidaCampos3{"¿>=5 campos?"}
    Convertir3["Convertir tipos y validar valores"]
    Agregar3["Agregar nota al vector"]
    FinO3([Fin carga notas])

    O3Start --> Prompt3 --> LeerPath3 --> Abrir3 --> ErrorAbrir3
    ErrorAbrir3 -->|No| FinO3
    ErrorAbrir3 -->|Sí| LeerLineas3 --> Split3 --> ValidaCampos3
    ValidaCampos3 -->|No| LeerLineas3
    ValidaCampos3 -->|Sí| Convertir3 --> Agregar3 --> LeerLineas3
    LeerLineas3 -->|EOF| FinO3
```

### Opciones 4–8: Generar reportes

```mermaid
flowchart TD
    Rstart([Inicio - generar reporte])
    Generar["Llamar a función de reporte correspondiente"]
    Mensaje["Mostrar mensaje de éxito"]
    Rend([Volver al menú])

    Rstart --> Generar --> Mensaje --> Rend
```

