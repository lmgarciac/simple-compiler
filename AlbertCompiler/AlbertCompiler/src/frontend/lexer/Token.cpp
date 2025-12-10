// src/frontend/lexer/Token.cpp
#include "Token.h"
#include <sstream>

namespace albert {

    Token::Token(TokenType type,
        std::string lexeme,
        int line,
        int column,
        int intValue)
        : type(type)
        , lexeme(std::move(lexeme))
        , line(line)
        , column(column)
        , intValue(intValue) {
    }

    std::string toString(TokenType type) {
        switch (type) {
        case TokenType::LEFT_PAREN:   return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN:  return "RIGHT_PAREN";
        case TokenType::LEFT_BRACE:   return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE:  return "RIGHT_BRACE";
        case TokenType::COMMA:        return "COMMA";
        case TokenType::SEMICOLON:    return "SEMICOLON";
        case TokenType::PLUS:         return "PLUS";
        case TokenType::MINUS:        return "MINUS";
        case TokenType::STAR:         return "STAR";
        case TokenType::SLASH:        return "SLASH";
        case TokenType::EQUAL:        return "EQUAL";
        case TokenType::EQUAL_EQUAL:  return "EQUAL_EQUAL";
        case TokenType::BANG_EQUAL:   return "BANG_EQUAL";
        case TokenType::LESS:         return "LESS";
        case TokenType::LESS_EQUAL:   return "LESS_EQUAL";
        case TokenType::GREATER:      return "GREATER";
        case TokenType::GREATER_EQUAL:return "GREATER_EQUAL";
        case TokenType::IDENTIFIER:   return "IDENTIFIER";
        case TokenType::NUMBER:       return "NUMBER";
        case TokenType::FN:           return "FN";
        case TokenType::LET:          return "LET";
        case TokenType::RETURN:       return "RETURN";
        case TokenType::IF:           return "IF";
        case TokenType::ELSE:         return "ELSE";
        case TokenType::WHILE:        return "WHILE";
        case TokenType::END_OF_FILE:  return "END_OF_FILE";
        }
        return "UNKNOWN";
    }

    std::string toString(const Token& token) {
        std::ostringstream oss;
        oss << toString(token.type) << "('" << token.lexeme << "')";
        if (token.type == TokenType::NUMBER) {
            oss << " value=" << token.intValue;
        }
        oss << " @" << token.line << ":" << token.column;
        return oss.str();
    }

} // namespace albert
