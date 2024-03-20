#include <iostream>

#include "LinkedStack.h"
#include "SeqStack.h"

void testSeq() {
    SeqStack<char> stack;
    std::cout << (stack.is_empty() ? "栈为空" : "栈不为空") << std::endl;

    for (char i = 'a'; i <= 'k'; i++) {
        stack.push(i);
    }
    std::cout << "添加元素 'a' - 'k'..." << std::endl;
    std::cout << (stack.is_empty() ? "栈为空" : "栈不为空") << std::endl;
    std::cout << "栈内容为：" << stack << std::endl;
    std::cout << "栈长度为 " << stack.size() << std::endl;

    while (!stack.is_empty()) {
        std::cout << "栈顶元素为：" << stack.getTop() << "，退栈" << std::endl;
        stack.pop();
    }

    std::cout << (stack.is_empty() ? "栈为空" : "栈不为空") << std::endl;
}

void testLinked() {
    LinkedStack<char> stack;
    std::cout << (stack.is_empty() ? "栈为空" : "栈不为空") << std::endl;

    for (char i = 'a'; i <= 'e'; i++) {
        stack.push(i);
    }
    std::cout << "添加元素 'a' - 'e'..." << std::endl;
    std::cout << (stack.is_empty() ? "栈为空" : "栈不为空") << std::endl;
    std::cout << "栈长度为 " << stack.size() << std::endl;

    while (!stack.is_empty()) {
        std::cout << "栈顶元素为：" << stack.getTop() << "，退栈" << std::endl;
        stack.pop();
    }

    std::cout << (stack.is_empty() ? "栈为空" : "栈不为空") << std::endl;
}

int main() {
    std::cout << '\n'
        << "===== 测试顺序表实现 ====="
        << '\n' << std::endl;
    testSeq();

    std::cout << '\n'
        << "===== 测试链表实现 ====="
        << '\n' << std::endl;
    testLinked();

    return 0;
}
