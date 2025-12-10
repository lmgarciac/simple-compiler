# Albert Compiler Architecture (`architecture.md`)

## 1. Overview

This document describes the architecture of the Albert compiler and how the project is organized.

Albert is implemented in C++ as a command-line tool that takes a `.albert` (or `.alb`) source file and:

- tokenizes it
- parses it into an AST
- performs basic semantic checks
- generates either:
  - bytecode executable by a small virtual machine, or
  - C source code that can be compiled by a C compiler

The architecture is intentionally simple and mirrors the classic compiler pipeline.

---

## 2. High-Level Pipeline

Overall flow:

1. Read source file
2. Lexical analysis (lexer)
3. Parsing (parser)
4. AST construction
5. Semantic analysis (resolver)
6. Code generation (backend)
7. Execution (VM) or C output

Diagram:

        source.alb
            |
            v
     [ Lexical Analysis ]
            |
            v
          Tokens
            |
            v
     [   Parser   ]
            |
            v
            AST
            |
            v
 [ Semantic Analysis ]
            |
            v
       Checked AST
            |
            v
      [  Backend  ]
      /           \
     v             v
  Bytecode        C code
     |             |
     v             v
   [VM]         C compiler

---

## 3. Directory Structure

Suggested layout:

albert/
  docs/
    language.md
    architecture.md

  src/
    frontend/
      lexer/
      parser/
      ast/
    middleend/
      semantics/
    backend/
      codegen/
      vm/
      cgen/
    runtime/
    cli/

  tests/

  CMakeLists.txt or solution files
  README.md

---

## 4. Frontend

### 4.1 Lexer (`src/frontend/lexer/`)

Responsibilities:

- Convert source text to tokens  
- Identify keywords, identifiers, literals, operators, punctuation  
- Basic error handling  

Output: a list of `Token` objects.

---

### 4.2 Parser (`src/frontend/parser/`)

Responsibilities:

- Consume tokens  
- Build an Abstract Syntax Tree (AST)  
- Validate syntax  

Uses a recursive descent parser.  
Output: the AST.

---

### 4.3 AST (`src/frontend/ast/`)

Responsibilities:

- Represent program structure  
- Nodes: expressions, statements, declarations  

Key components:

- Base `Expr` and `Stmt` classes  
- Derived nodes: `BinaryExpr`, `LiteralExpr`, `IfStmt`, etc.

---

## 5. Middleend (Semantic Analysis)

Directory: `src/middleend/semantics/`

Responsibilities:

- Validate correctness of the AST  
- Manage scopes and symbol tables  
- Detect errors like:
  - variable used before declaration
  - redeclaration in same scope
  - invalid returns
  - incorrect function arity  

Output: validated AST + symbol metadata.

---

## 6. Backend (`src/backend/`)

Two possible backends.

### 6.1 Bytecode Backend (`codegen/`)

Responsibilities:

- Convert AST into bytecode  
- Manage local variables, jumps, calls  

Components:

- `OpCode` enum  
- `Chunk` or instruction buffer  
- `CodeGenerator` walker  

---

### 6.2 Virtual Machine (`vm/`)

Responsibilities:

- Execute bytecode  
- Implement operand stack, call stack, PC  
- Handle arithmetic, jumps, calls  

Input: bytecode program  
Output: program exit value

---

### 6.3 C Code Generator (`cgen/`)

Responsibilities:

- Convert AST into C code  
- Map Albert constructs directly to C constructs  

Example:

Albert:
    fn sum(a, b) { return a + b; }

C:
    int sum(int a, int b) { return a + b; }

Output: `.c` file.

---

## 7. Runtime (`src/runtime/`)

Responsibilities:

- Provide optional built-in functions  
- VM native functions (e.g., print)  
- C helper functions used by compiler-generated C files  

---

## 8. CLI (`src/cli/`)

Responsibilities:

- Implement compiler's entry point (`main`)  
- Parse arguments  
- Execute pipeline:
  - lexer
  - parser
  - semantics
  - backend
  - run or output file  

Example commands:

- `albert run file.alb`
- `albert compile file.alb -o out.c`
- `albert tokens file.alb`
- `albert ast file.alb`

---

## 9. Tests (`tests/`)

Recommended subfolders:

- `lexer/`
- `parser/`
- `semantics/`
- `backend/`

Tests ensure stability and avoid regressions.

---

## 10. Extensibility

Albert is modular:

- New language features → update lexer, parser, AST, semantics, backend  
- New backends → implement another codegen module  
- Ideal for experimentation and learning compiler design
