// src/frontend/lexer/TokenType.h
#pragma once

#include <string>

namespace albert {

    // Lista de todos los tipos básicos de piezas del lenguaje

    enum class TokenType {

        // -- Porque usamos enum class? --
        // - No contamina el namespace (o el scope) (no son símbolos globales). Evita colisión de nombres
        // - Fuertemente tipado. No se convierten implícitamente a INT (que puede generar bugs),
        //   requiere conversión explícita, p ej. static_cast.

        // Single-character tokens

        LEFT_PAREN, RIGHT_PAREN,    // '(' ')'
        LEFT_BRACE, RIGHT_BRACE,    // '{' '}'
        COMMA, SEMICOLON,           // ',' ';'
        PLUS, MINUS, STAR, SLASH,   // '+', '-', '*', '/'

        // One or two character tokens
        EQUAL,          // =
        EQUAL_EQUAL,    // ==
        BANG_EQUAL,     // !=
        LESS,           // <
        LESS_EQUAL,     // <=
        GREATER,        // >
        GREATER_EQUAL,  // >=

        IDENTIFIER, // Nombres definidos por usuario
        NUMBER, // Literales numéricos

        // Keywords
        FN,
        LET,
        RETURN,
        IF,
        ELSE,
        WHILE,

        END_OF_FILE
    };

    std::string toString(TokenType type);

} // namespace albert
