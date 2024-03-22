#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "SuffixExpression.h"

int main() {
    const std::vector<std::string> cases {
        "123",
        "3 + 4",
        "2 * x",
        "10 / 5",
        "2 ^ 3",
        "3 + 4 * 2",
        "10 - 5 + 2",
        "2 ^ 3 * 4",
        "1+2+3",
        "2*(1+3)-4",
        "(56-20)/(4+2)",
        "((123 + 456) * 789) / 2",
        "(56 - (45 + 34)) * (23 / 12)",
        "((12 ^ 3) + 456) / (78 - 90)",
        "3 + 4 * 2 / (1 - 5) ^ 2 ^ 3",
        "a + b * c - d / e + f * g - h",
        "1 * 20 +",
        "(3 + 4",
        "2 / (12 - 1",
        "1 + 3)",
        "2 ^ (3 * 4))",
        "1 + 3 * ",
        "(1 + 3) / ",
    };

    std::unique_ptr<SuffixExpression> exp;
    for (const auto &infix : cases) {
        std::cout << "==> " << infix << "\n    ==> ";

        try {
            exp = std::make_unique<SuffixExpression>(infix);
            std::cout << *exp << "\n    ==> ";
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
            continue;
        }

        try {
            std::cout << exp->evaluate() << std::endl;
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        }
    }
    while (true) {
        std::string infix;
        std::cout << "==> ";
        std::getline(std::cin, infix);

        try {
            exp = std::make_unique<SuffixExpression>(infix);
            std::cout << "    ==> " << *exp << "\n    ==> ";
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
            continue;
        }

        try {
            std::cout << exp->evaluate() << std::endl;
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        }
    }

    return 0;
}
