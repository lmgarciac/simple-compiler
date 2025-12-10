// src/cli/main.cpp
#include <iostream>
#include <string>
#include <vector>
#include "frontend/lexer/Lexer.h"

int main() {
    std::string source = R"(fn main() {
        let x = 5 + 3;
        if (x < 10) {
            x = x + 1;
        }
        return x;
    })";

    albert::Lexer lexer(source);
    std::vector<albert::Token> tokens = lexer.scanTokens();

    for (const auto& t : tokens) {
        std::cout << albert::toString(t) << '\n';
    }

    return 0;
}
