#pragma once

enum class TokenType {
    // Palabras reservadas
    TABLERO,
    COLUMNA,
    TAREA,
    PRIORIDAD,
    RESPONSABLE,
    FECHA_LIMITE,

    // Prioridades
    ALTA,
    MEDIA,
    BAJA,

    // Literales
    CADENA,
    ENTERO,
    FECHA,

    // Delimitadores
    LLAVE_ABRE,     // {
    LLAVE_CIERRA,   // }
    CORCHETE_ABRE,  // [
    CORCHETE_CIERRA,// ]
    DOS_PUNTOS,     // :
    COMA,           // ,
    PUNTO_Y_COMA,   // ;

    // Control
    END_OF_FILE,
    ERROR
};
