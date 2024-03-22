#ifndef EXP2TASK5_SUFFIXEXPRESSION_H
#define EXP2TASK5_SUFFIXEXPRESSION_H

#include <iostream>
#include <string>

#include "LinkedStack.h"

class SuffixExpression final {
    friend std::ostream &operator<<(std::ostream& os, const SuffixExpression& exp);
public:
    SuffixExpression() = delete;
    explicit SuffixExpression(const std::string &infix);
    double evaluate() const;
    void print() const {
        std::cout << *this << std::endl;
    }
private:
    LinkedStack<std::string> stack;
};

#endif //EXP2TASK5_SUFFIXEXPRESSION_H
