// src/frontend/parser/Parser.h
#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../lexer/Token.h"

#include "ast/Expr.h"
#include "ast/Stmt.h"

namespace albert {

    // Forward declarations (AST mínimo, lo definimos después)
    struct Stmt;
    struct Expr;

    // Aliases para ownership claro
    using StmtPtr = std::unique_ptr<Stmt>;
    using ExprPtr = std::unique_ptr<Expr>;

    class Parser {
    public:
        explicit Parser(const std::vector<Token>& tokens);

        // Entry point: parsea un "programa" completo (lista de statements)
        std::vector<StmtPtr> parseProgram();

    private:
        // Input
        const std::vector<Token>& m_tokens;
        std::size_t m_current = 0;

        // -------------------------
        // Core helpers de navegación
        // -------------------------
        bool isAtEnd() const;
        const Token& peek() const; //Devuelve el token actual (solo lectura)
        const Token& previous() const; //Devuelve el token anterior (solo lectura)
        const Token& advance(); //Avanzamos un token hacia adelante, y devolvemos el token anterior (o el actual antes de avanzar) (solo lectura)
        bool check(TokenType type) const; //Chequeamos si el token actual es del tipo enviado por parámetro.

        // match: si el token actual coincide con alguno, consume y devuelve true
        bool match(TokenType type); //Si coincide con este
        bool match(std::initializer_list<TokenType> types); //Si coincide con alguno de estos

        // consume: exige un tipo, si no está lanza error de parseo
        const Token& consume(TokenType type, const std::string& message);

        // Error handling (mínimo)
        void errorAt(const Token& token, const std::string& message) const;
        void synchronize(); // recovery simple: salta a un punto “seguro” tras un error

        // -------------------------
        // Grammar: statements
        // -------------------------
        StmtPtr declaration();   // punto común para "let" y futuros
        StmtPtr statement();     // return/if/while/block/exprStmt

        StmtPtr letDeclaration();    // let x = expr ;
        StmtPtr returnStatement();   // return expr ;
        StmtPtr blockStatement();    // { ... }

        StmtPtr expressionStatement(); // expr ;

        // -------------------------
        // Grammar: expressions (precedence climbing)
        // -------------------------
        ExprPtr expression();
        ExprPtr equality();      // == !=
        ExprPtr comparison();    // < <= > >=
        ExprPtr term();          // + -
        ExprPtr factor();        // * /
        ExprPtr unary();         // (si después agregás ! o - unario)
        ExprPtr primary();       // NUMBER, IDENTIFIER, (expr)
    };

} // namespace albert
