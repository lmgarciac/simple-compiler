// src/frontend/parser/ast/Expr.h

#pragma once

#include <memory>
#include <string>
#include "../../lexer/Token.h"

// Las expresiones son cosas que producen un valor. Por ejemplo: 
// 25
// 10 + 2
// (a * b)

namespace albert
{
	struct Expr
	{
		virtual	~Expr() = default;
	};

	using ExprPtr = std::unique_ptr<Expr>;

	struct NumberExpr : Expr // Literal Numérico
	{
		int value;
		Token token; //para información, opcional

		explicit NumberExpr(const Token& t) : value(t.intValue), token(t) {}
	};

	struct IdentifierExpr : Expr // Identificador (x, total, sum)
	{
		std::string name;
		Token token;

		explicit IdentifierExpr(const Token& t) : name(t.lexeme), token(t) {}
	};

	struct GroupingExpr : Expr // Expresion entre paréntesis. Por ej: (x * (y + 2))
	{
		ExprPtr expression;

		explicit GroupingExpr(ExprPtr expr) : expression(std::move(expr)) {}
	};

	struct BinaryExpr : Expr // Operación binaria entre dos expresiones. Por ejemplo:
							 // 10 * 2  
							 // x == y
							 // a < b
	{
		ExprPtr left; // lhs: Left hand side
		Token op; // necesitamos el operador
		ExprPtr right; // rhs: Right hand side

		BinaryExpr(ExprPtr lhs, const Token& oper, ExprPtr rhs) : left(std::move(lhs)), op(oper), right(std::move(rhs)) {}
	};
}