#include <iostream>
#include <string>

#include "LinkedStack.h"

bool isSymmetric(const std::string &str) {
    LinkedStack<char> stack;
    const size_t len = str.size();

    for (size_t i = 0, l = len / 2; i < l; i++) {
        stack.push(str.at(i));
    }

    for (size_t i = len / 2 + len % 2; i < len; i++) {
        if (stack.get_top() != str.at(i)) {
            return false;
        }
        stack.pop();
    }

    return true;
}

int main() {
    std::string str;

    while (true) {
        std::cout << "请输入一个字符串：";
        std::cin >> str;

        std::cout << (isSymmetric(str) ? "是" : "不是") << "中心对称字符串" << std::endl;
    }

    return 0;
}
