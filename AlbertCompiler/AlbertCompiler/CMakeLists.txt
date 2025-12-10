cmake_minimum_required(VERSION 3.20)

project(AlbertCompiler LANGUAGES CXX VERSION 0.1.0)

# C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Carpeta de salida de los ejecutables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

# Por ahora solo tenemos el main
set(SRC_FILES
    src/cli/main.cpp
)

add_executable(albert ${SRC_FILES})

target_include_directories(albert PRIVATE src)