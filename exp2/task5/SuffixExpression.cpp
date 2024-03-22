#include <cctype>
#include <stdexcept>

#include "SuffixExpression.h"

enum class TokenType {
    NONE,
    BLANK,
    OPERAND_NUMBER,
    OPERAND_VARIABLE,
    OPERATOR,
    PARENTHESIS_LEFT,
    PARENTHESIS_RIGHT
};

SuffixExpression::SuffixExpression(const std::string &infix) {
    auto optr = LinkedStack<std::string>();

    std::string token;
    TokenType last_token_type = TokenType::NONE, token_type;
    for (size_t i = 0, l = infix.length(); i < l; i++) {
        const char c = infix.at(i);

        if (std::isdigit(c) || c == '.') {
            token_type = TokenType::OPERAND_NUMBER;
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            token_type = TokenType::OPERATOR;
        } else if (c == '(') {
            token_type = TokenType::PARENTHESIS_LEFT;
        } else if (c == ')') {
            token_type = TokenType::PARENTHESIS_RIGHT;
        } else if (std::isblank(c)) {
            token_type = TokenType::BLANK;
        } else {
            token_type = TokenType::OPERAND_VARIABLE;
        }

        if (last_token_type != TokenType::NONE && last_token_type != token_type) {
            i--;
            token_type = last_token_type;
        } else {
            token += c;
            if (token_type != TokenType::OPERATOR &&
                token_type != TokenType::PARENTHESIS_LEFT &&
                token_type != TokenType::PARENTHESIS_RIGHT &&
                i < l - 1) {
                // multi-char token
                last_token_type = token_type;
                continue;
            }
        }

        if (token_type == TokenType::OPERATOR) {
            while (!(optr.is_empty() || optr.get_top() == "(" ||
                token == "^" ||
                ((token == "*" || token == "/") && (optr.get_top() == "+" || optr.get_top() == "-")))) {
                stack.push(optr.get_top());
                optr.pop();
            }
            optr.push(token);
        } else if (token_type == TokenType::PARENTHESIS_LEFT) {
            optr.push(token);
        } else if (token_type == TokenType::PARENTHESIS_RIGHT) {
            while (true) {
                if (optr.is_empty()) {
                    throw std::invalid_argument("invalid expression");
                }
                if (optr.get_top() != "(") {
                    stack.push(optr.get_top());
                    optr.pop();
                } else {
                    optr.pop();
                    break;
                }
            }
        } else if (token_type != TokenType::BLANK) {
            stack.push(token);
        }

        last_token_type = TokenType::NONE;
        token = "";
    }

    while (!optr.is_empty()) {
        if (optr.get_top() == "(" || optr.get_top() == ")") {
            throw std::invalid_argument("invalid expression");
        }
        stack.push(optr.get_top());
        optr.pop();
    }
}

double evaluate_step(LinkedStack<std::string> *stack) {
    const std::string token = stack->get_top();
    stack->pop();

    if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^") {
        const double operand2 = evaluate_step(stack),
            operand1 = evaluate_step(stack);
        if (token == "+") {
            return operand1 + operand2;
        }
        if (token == "-") {
            return operand1 - operand2;
        }
        if (token == "*") {
            return operand1 * operand2;
        }
        if (token == "/") {
            return operand1 / operand2;
        }
        if (token == "^") {
            return std::pow(operand1, operand2);
        }
    }

    try {
        return std::stod(token);
    } catch (std::invalid_argument &) {
        throw std::invalid_argument("unable to evaluate");
    }
}

double SuffixExpression::evaluate() const {
    LinkedStack<std::string> stack = this->stack;
    try {
        const double result = evaluate_step(&stack);
        if (!stack.is_empty()) {
            throw std::invalid_argument("invalid expression");
        }
        return result;
    } catch (std::out_of_range &) {
        throw std::invalid_argument("invalid expression");
    }
}

std::ostream &operator<<(std::ostream& os, const SuffixExpression& exp) {
    LinkedStack<std::string> stack = exp.stack, reverseStack;

    while (!stack.is_empty()) {
        reverseStack.push(stack.get_top());
        stack.pop();
    }

    while (!reverseStack.is_empty()) {
        std::cout << reverseStack.get_top();
        reverseStack.pop();
        if (!reverseStack.is_empty()) {
            std::cout << ' ';
        }
    }

    return os;
}
