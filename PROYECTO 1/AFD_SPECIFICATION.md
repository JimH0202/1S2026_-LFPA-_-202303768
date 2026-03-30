# AFD (Autómata Finito Determinístico)

ESPECIFICACIÓN DEL AFD

```
Estado Inicial: q0
Estados Finales: Múltiples (q1-q15)
Símbolos: 0-9, a-zA-Z, _, +, -, :, ", {}, [], etc.
```

---

## DIAGRAMA DE TRANSICIONES

### Estado q0 (Inicial)
```
q0 --(espacio/tab/salto)--> q0 (skip)
q0 --(//)--> q0 (skip comentario hasta '\n')
q0 --(")--> q1 (STRING)
q0 --(0-9)--> q2 (INTEGER/DATE/TIME)
q0 --(a-zA-Z|_)--> q3 (IDENTIFIER/KEYWORD/CODE)
q0 --({,},[,],:,;,,,)--> q15 (SYMBOL)
q0 --(otro)--> q16 (ERROR)
```

### Estados de Cadenas (STRING)
```
q1 --([^"\n])--> q1 (acumula)
q1 --(") --> ACEPTAR (STRING)
q1 --(\n | EOF) --> ERROR (Unclosed String)
```

### Estados de Números
```
q2 --(0-9)--> q2 (acumula)
q2 --(-) --> q4 (Posible DATE)
q2 --(:) --> q5 (Posible TIME)
q2 --(otro) --> ACEPTAR (INTEGER)

// Para DATE (q4)
q4 --(0-9)--> q4 (acumula)
q4 --(-) --> q6 (Requiere segundo -)
q6 --(0-9)--> q6 (acumula)
q6 --(ValidarFecha) --> ACEPTAR (DATE)
q6 --(resultado inválido) --> ERROR

// Para TIME (q5)
q5 --(0-9)--> q5 (acumula)
q5 --(ValidarHora) --> ACEPTAR (TIME)
q5 --(resultado inválido) --> ERROR
```

### Estados de Identificadores
```
q3 --([a-zA-Z0-9_])--> q3 (acumula)
q3 --(+|-)--> q7 (Posible BLOOD_TYPE)
q3 --(-)--> q8 (Posible CODE)
q3 --(otro) --> q9 (Clasificar)

// Blood Type (q7)
q7 --(ValidarTipo) --> ACEPTAR (BLOOD_TYPE)
q7 --(inválido) --> ERROR

// CODE (q8)
q8 --(0-9)--> q8 (acumula)
q8 --(ValidarCodigo) --> ACEPTAR (CODE)
q8 --(inválido) --> ERROR

// Clasificación (q9)
q9 --(EsKeyword) --> ACEPTAR (KEYWORD)
q9 --(EsSpecialty) --> ACEPTAR (SPECIALTY)
q9 --(EsDosis) --> ACEPTAR (DOSIS)
q9 --(para todo) --> ACEPTAR (IDENTIFIER)
```

---

## FUNCIONES DE VALIDACIÓN

### `isValidDate(string date)`
```
Entrada: "YYYY-MM-DD"
Validación:
  1. Formato exacto: longitud 10, posiciones 4 y 7 = '-'
  2. Mes: 1 ≤ MM ≤ 12
  3. Día: 1 ≤ DD ≤ días_en_mes[MM]
  4. Manejo de años bisiestos:
     Bisiesto = (año % 4 == 0 && año % 100 != 0) || (año % 400 == 0)
```

### `isValidTime(string time)`
```
Entrada: "HH:MM"
Validación:
  1. Formato exacto: longitud 5, posición 2 = ':'
  2. Hora: 0 ≤ HH ≤ 23
  3. Minuto: 0 ≤ MM ≤ 59
```

### `isValidBloodType(string bt)`
```
Validación: bt ∈ {A+, A-, B+, B-, O+, O-, AB+, AB-}
Rechaza:
  - O++ (más de un signo)
  - A (sin signo)
  - C- (grupo inválido)
```

### `isValidCode(string code)`
```
Patrón: [A-Z]{3}-[0-9]+
Ejemplo válido: MED-001, PAC-042, DIA-100
Tabla de validación:
  - Longitud ≥ 7
  - Caracteres 0-2: A-Z (mayúsculas)
  - Carácter 3: '-'
  - Caracteres 4+: dígitos
```

### `isValidSpecialty(string sp)`
```
Conjunto válido:
  {CARDIOLOGIA, NEUROLOGIA, PEDIATRIA, 
   CIRUGIA, MEDICINA_GENERAL, ONCOLOGIA}
```

### `isValidDosis(string ds)`
```
Conjunto válido:
  {DIARIA, CADA_8_HORAS, CADA_12_HORAS, SEMANAL}
```

---

## LOOKAHEAD Y DESAMBIGUACIÓN

### Problema: `A` vs `A+` vs `AB` vs `AB+` vs identificador

**Solución**: Lookahead de 1 carácter

```cpp
std::string lex = "A";
if (peek() == '+' || peek() == '-') {
    // Podría ser tipo de sangre
    if (lex == "A" || ... "AB") {
        // Consumir + o - y validar
    }
} else if (lex == "AB" && peek() == '+' ...) {
    // Tipo sangre AB+/-
} else {
    // Identificador o keyword
}
```

---

## MANEJO DE ERRORES (SIN DETENCIÓN)

### Estrategia: Recuperación y Continuidad

```
Error detectado:
  1. Registrar en ErrorManager con contexto (línea, columna, lexema)
  2. Retornar TokenType::ERROR con lexema problemático
  3. Continuar procesamiento en nextToken()
  4. No interrumpir el flujo análisis
```

### Ejemplo:
```
Entrada: "cadena sin cerrar
          error: "cadena sin cerrar
          token: ERROR ("cadena sin cerrar)
          === continúa análisis ===
          próximo token: identific...
```

---

## COMPLEJIDAD

- **Tiempo**: O(n) donde n = longitud del archivo
- **Espacio**: O(k) donde k = tokens generados
- **Backtracking**: Mínimo, solo en desambiguación tipo sangre/código

---

## CASOS DE PRUEBA

| Entrada | Token Esperado | Resultado |
|---------|----------------|-----------|
| `2025-04-10` | DATE | ✓ |
| `2025-13-05` | ERROR | ✓ |
| `25:00` | ERROR | ✓ |
| `09:30` | TIME | ✓ |
| `A+` | BLOOD_TYPE | ✓ |
| `O++` | ERROR | ✓ |
| `MED-001` | CODE | ✓ |
| `AB-` | BLOOD_TYPE | ✓ |
| `"sin cerrar | ERROR | ✓ |

---

## CARACTERÍSTICAS AVANZADAS

### 1. Rastreo Preciso de Posición
- Línea y columna actualizadas en cada carácter
- Manejo especial para saltos de línea

### 2. Comentarios
- Sintaxis: `//`
- Consumidos completamente sin generar token

### 3. Identificadores con Caracteres Especiales
- Admite guiones en identificadores (`tipo_sangre`)
- Diferencia `tipo_sangre` de código `TIP-001`

---
