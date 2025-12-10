// src/frontend/lexer/Lexer.cpp
#include "Lexer.h"
#include <cctype>

namespace albert {

    Lexer::Lexer(std::string source)
        : m_source(std::move(source)) {
    }

    std::vector<Token> Lexer::scanTokens() {
        while (!isAtEnd()) {
            m_start = m_current;
            scanToken();
        }

        m_tokens.emplace_back(TokenType::END_OF_FILE, "", m_line, m_column);
        return m_tokens;
    }

    bool Lexer::isAtEnd() const {
        return m_current >= m_source.size();
    }

    char Lexer::advance() {
        char c = m_source[m_current++];
        if (c == '\n') {
            ++m_line;
            m_column = 1;
        }
        else {
            ++m_column;
        }
        return c;
    }

    char Lexer::peek() const {
        if (isAtEnd()) return '\0';
        return m_source[m_current];
    }

    char Lexer::peekNext() const {
        if (m_current + 1 >= m_source.size()) return '\0';
        return m_source[m_current + 1];
    }

    bool Lexer::match(char expected) {
        if (isAtEnd()) return false;
        if (m_source[m_current] != expected) return false;
        ++m_current;
        ++m_column;
        return true;
    }

    void Lexer::addToken(TokenType type) {
        std::string text = m_source.substr(m_start, m_current - m_start);
        m_tokens.emplace_back(type, std::move(text), m_line, m_column);
    }

    void Lexer::addToken(TokenType type, int intValue) {
        std::string text = m_source.substr(m_start, m_current - m_start);
        m_tokens.emplace_back(type, std::move(text), m_line, m_column, intValue);
    }

    void Lexer::scanToken() {
        char c = advance();

        switch (c) {
            // whitespace
        case ' ':
        case '\r':
        case '\t':
            // se ignora
            break;

        case '\n':
            // advance() ya actualizó línea/columna, nada más que hacer
            break;

            // punctuation
        case '(': addToken(TokenType::LEFT_PAREN);  break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE);  break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA);       break;
        case ';': addToken(TokenType::SEMICOLON);   break;

            // operators
        case '+': addToken(TokenType::PLUS);        break;
        case '-': addToken(TokenType::MINUS);       break;
        case '*': addToken(TokenType::STAR);        break;
        case '/':
            if (match('/')) {
                // comentario de línea: consumir hasta fin de línea
                while (peek() != '\n' && !isAtEnd()) advance();
            }
            else {
                addToken(TokenType::SLASH);
            }
            break;

        case '=':
            addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '!':
            if (match('=')) {
                addToken(TokenType::BANG_EQUAL);
            }
            // si quisieras soportar '!' solo, acá podrías agregarlo como token aparte
            break;
        case '<':
            addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        case '>':
            addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;

        default:
            if (std::isdigit(static_cast<unsigned char>(c))) {
                number();
            }
            else if (isAlpha(c)) {
                identifier();
            }
            else {
                // por ahora, caracteres inválidos se ignoran.
                // más adelante podemos reportar un error léxico.
            }
            break;
        }
    }

    void Lexer::number() {
        while (std::isdigit(static_cast<unsigned char>(peek()))) {
            advance();
        }

        std::string text = m_source.substr(m_start, m_current - m_start);

        int value = 0;
        for (char ch : text) {
            value = value * 10 + (ch - '0');
        }

        m_tokens.emplace_back(TokenType::NUMBER, std::move(text),
            m_line, m_column, value);
    }

    void Lexer::identifier() {
        while (isAlphaNumeric(peek())) {
            advance();
        }

        std::string text = m_source.substr(m_start, m_current - m_start);
        TokenType type = identifierType(text);
        m_tokens.emplace_back(type, std::move(text), m_line, m_column);
    }

    bool Lexer::isAlpha(char c) {
        return std::isalpha(static_cast<unsigned char>(c)) || c == '_';
    }

    bool Lexer::isAlphaNumeric(char c) {
        return isAlpha(c) || std::isdigit(static_cast<unsigned char>(c));
    }

    TokenType Lexer::identifierType(const std::string& text) {
        if (text == "fn")     return TokenType::FN;
        if (text == "let")    return TokenType::LET;
        if (text == "return") return TokenType::RETURN;
        if (text == "if")     return TokenType::IF;
        if (text == "else")   return TokenType::ELSE;
        if (text == "while")  return TokenType::WHILE;
        return TokenType::IDENTIFIER;
    }

} // namespace albert
