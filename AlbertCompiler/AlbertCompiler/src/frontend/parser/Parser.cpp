// src/frontend/parser/Parser.cpp

#include "Parser.h"
#include <iostream>

namespace albert
{
	Parser::Parser(const std::vector<Token>& tokens) 
		: m_tokens(tokens) {}


	const Token& Parser::peek() const
	{
		return m_tokens[m_current];
	}

	const Token& Parser::previous() const
	{
		return m_tokens[m_current - 1];
	}

	bool Parser::isAtEnd() const
	{
		return peek().type == TokenType::END_OF_FILE;
	}

	const Token& Parser::advance()
	{
		if (!isAtEnd())
			m_current++;

		return previous();
	}

	bool Parser::check(TokenType type) const
	{
		if (isAtEnd()) return false;
		return peek().type == type;
	}

	bool Parser::match(TokenType type)
	{
		if (check(type))
		{
			advance();
			return true;
		}
		return false;
	}

	bool Parser::match(std::initializer_list<TokenType> types)
	{
		for (TokenType type : types)
		{
			if (match(type))
				return true;
		}
		return false;
	}

	const Token& Parser::consume(TokenType type, const std::string& message) {
		if (check(type)) return advance();
		errorAt(peek(), message);
		// En una versión mínima, podés lanzar excepción o abortar.
		// Más adelante hacemos recovery con synchronize().
		return peek(); // fallback para no-crashear si todavía no usás exceptions
	}

	void Parser::errorAt(const Token& token, const std::string& message) const {
		// Por ahora: log simple. Luego lo conectamos a un sistema de diagnostics.
		// Ejemplo: [line:col] Error at 'lexeme': message
		// (token.lexeme puede estar vacío en EOF)
		// Podés cambiar std::cerr por tu logger.
		std::cerr << "["
			<< token.line << ":" << token.column
			<< "] Parse error";

		if (token.type == TokenType::END_OF_FILE) {
			std::cerr << " at end";
		}
		else {
			std::cerr << " at '" << token.lexeme << "'";
		}

		std::cerr << ": " << message << "\n";
	}

	ExprPtr Parser::expression()
	{
		primary();
	}
}

