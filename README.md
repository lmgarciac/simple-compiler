# Albert Programming Language

Albert is a minimal, educational programming language created to understand how a compiler works end-to-end.  
The goal is not performance or completeness, but **clarity**: every stage of the compilation pipeline is explicit, simple, and fully readable.

Albert serves as a study project for learning:

- Lexical analysis  
- Parsing and AST construction  
- Semantic analysis and symbol resolution  
- Code generation  
- (Optional) Virtual machine execution  

The language itself is intentionally tiny — similar to a simplified C-like syntax with only integers, variables, functions, conditionals, loops, and expressions.

---

## Purpose of This Project

The purpose of Albert is to provide a clean, approachable, real-world implementation of a compiler that a beginner can understand from the first line of code to the last.

Albert exists to answer questions like:

- How does source code become tokens?  
- How does a parser build a tree from those tokens?  
- What is an AST and why does it matter?  
- How are scopes and variables resolved?  
- How does high-level code become low-level instructions or C code?  
- How does a simple VM execute those instructions?  

The project is structured to reflect the classic architecture of a compiler, with each stage isolated into its own module.

---

## Compiler Architecture & Modules

The Albert compiler is divided into the following modules:

### **1. `frontend/lexer/` – Lexical Analysis**
Converts raw text into a stream of tokens.  
Detects keywords, identifiers, numbers, operators, and punctuation.

### **2. `frontend/parser/` – Syntax Analysis**
Consumes tokens and produces an abstract syntax tree (AST).  
Implements a recursive descent parser following Albert’s grammar.

### **3. `frontend/ast/` – Abstract Syntax Tree**
Contains the node structures used to represent programs.  
Expressions, statements, function declarations, blocks, etc.

### **4. `middleend/semantics/` – Semantic Analysis**
Checks that the program makes sense:
- Variable declaration and usage  
- Scope rules  
- Return statements  
- Function arity and validity  

Also manages symbol tables.

### **5. `backend/` – Code Generation**
Transforms the AST into executable form.  
Two possible backends may exist:

- A small bytecode instruction set + VM  
- A C code generator producing compilable `.c` output  

### **6. `vm/` (optional) – Virtual Machine**
Executes the bytecode produced by the compiler.  
Implements stack operations, jumps, arithmetic ops, and function calls.

### **7. `cli/` – Command-Line Interface**
The `albert` executable.  
Handles input files and orchestrates the entire pipeline.

---

## Project Status

Albert is currently in early development.  
Language specification: ✔️  
Architecture design: in progress  
Compiler implementation: not started  

---

## License

This project is open for educational use.  
Feel free to study, fork, or extend Albert for your own learning.

