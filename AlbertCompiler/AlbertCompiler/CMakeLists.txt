cmake_minimum_required(VERSION 3.20)

project(AlbertCompiler LANGUAGES CXX VERSION 0.1.0)

# Versión de C++ (C++20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Carpeta de salida de los ejecutables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

# Archivos fuente
set(SRC_FILES
    src/cli/main.cpp
    src/frontend/lexer/Lexer.cpp
    src/frontend/lexer/Token.cpp
)

add_executable(albert ${SRC_FILES} "src/frontend/parser/Parser.h" "src/frontend/parser/ast/Stmt.h" "src/frontend/parser/ast/Expr.h")

target_include_directories(albert PRIVATE src)