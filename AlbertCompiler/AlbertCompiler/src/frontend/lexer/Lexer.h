// src/frontend/lexer/Lexer.h
#pragma once

#include <string>
#include <vector>
#include "Token.h"

namespace albert {

    class Lexer {
    public:
        explicit Lexer(std::string source);

        std::vector<Token> scanTokens();

    private:
        std::string m_source;
        std::vector<Token> m_tokens;

        std::size_t m_start = 0;
        std::size_t m_current = 0;
        int m_line = 1;
        int m_column = 1;

        bool isAtEnd() const;
        char advance();
        char peek() const;
        char peekNext() const;
        bool match(char expected);

        void addToken(TokenType type);
        void addToken(TokenType type, int intValue);

        void scanToken();
        void number();
        void identifier();

        static bool isAlpha(char c);
        static bool isAlphaNumeric(char c);
        static TokenType identifierType(const std::string& text);
    };

} // namespace albert
