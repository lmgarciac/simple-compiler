// src/frontend/lexer/Token.h
#pragma once

#include "TokenType.h"
#include <string>

namespace albert {

    struct Token {
        TokenType type;
        std::string lexeme;
        int line = 0;
        int column = 0;
        int intValue = 0; // solo se usa si type == NUMBER

        Token(TokenType type,
            std::string lexeme,
            int line,
            int column,
            int intValue = 0);
    };

    std::string toString(const Token& token);

} // namespace albert
