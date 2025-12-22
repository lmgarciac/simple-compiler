// src/frontend/parser/ast/Stmt.h

#pragma once

#include <memory>
#include <vector>
#include "Expr.h"

// Las sentencias son cosas que representan una acción o una estructura de control y no necesariamente producen un valor. Por ejemplo:
// let x = 10; (declaracion) 
// return expr 
// { ... } (bloque) 
// if(...){...}else{...}

namespace albert
{
	struct Stmt
	{
		virtual ~Stmt() = default;
	};

	using StmtPtr = std::unique_ptr<Stmt>;

	struct ExprStmt : Stmt // Expresión usada como sentencia. Evalua expresión por su efecto, no por su valor (aunque el valor se descarte). Por ejemplo 
		// foo();
		// a * b;
	{
		ExprPtr expression;

		explicit ExprStmt(ExprPtr expr) : expression(std::move(expr)) {}
	};

	struct LetStmt : Stmt // Declaración de variable. Por ej. let x = 10;
	{
		Token name; // Identifier Token, con lexeme + posicion
		ExprPtr initializer;

		LetStmt(const Token& nameToken, ExprPtr init) : name(nameToken), initializer(std::move(init)) {}
	};

	struct ReturnStmt : Stmt // Finalizacion de una funcion con un valor. Por ej: return x + 1;
	{
		Token keyword; //Identifier token
		ExprPtr value;

		ReturnStmt(const Token& kw, ExprPtr v) : keyword(kw), value(std::move(v)) {}
	};

	struct BlockStmt : Stmt // Bloque de sentencias agrupadas. Por ej:
		// { 
		// let x = 10; 
		// return x; 
		// }
	{
		std::vector<StmtPtr> statements;

		explicit BlockStmt(std::vector<StmtPtr> stmts) : statements(std::move(stmts)) {}
	};
}

