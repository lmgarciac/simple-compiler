// src/frontend/lexer/Lexer.h
#pragma once

#include <string>
#include <vector>
#include "Token.h"

namespace albert {

    class Lexer {
    public:
        explicit Lexer(std::string source); // Utilizamos explicit para evitar conversiones implícitas en el constructor por ej: Lexer lex = "fn main() {}";
                                            // Un Lexer no debería construirse desde un string sin intención explícita.

        std::vector<Token> scanTokens();

    private:
        std::string m_source;
        std::vector<Token> m_tokens;

        std::size_t m_start = 0; // Siempre que vayamos a contar índices en contenedores, usamos size_t (el tipo que utiliza STL).
        std::size_t m_current = 0;
        int m_line = 1;
        int m_column = 1;

        bool isAtEnd() const;
        char advance(); //Devuelve el carácter actual y avanza m_current.
        char peek() const; //Mira el carácter actual sin avanzar.
        char peekNext() const; //Mira el carácter después del actual, sin avanzar.
        bool match(char expected); //Si el carácter actual coincide con expected, lo consume y retorna true.

        void addToken(TokenType type); //Crea un token con el tipo indicado y el lexeme extraído entre m_start y m_current.
        void addToken(TokenType type, int intValue); //Idem, para los token "Number"

        void scanToken(); //Escanea un solo token según el carácter actual.
        void number(); //Escanea un token numérico.
        void identifier();//Escanea identificadores o palabras clave.

        static bool isAlpha(char c); //True si "c" es ASCII o "_". Sirve para decidir si un token puede empezar como identificador.
        static bool isAlphaNumeric(char c); //True si "c" es letra, dígito o "_". Se usa para continuar un identificador.
        static TokenType identifierType(const std::string& text); //si es keyword devuelve el TokenType correspondiente, si no devuelve IDENTIFIER
    };

} // namespace albert
