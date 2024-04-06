#include <iostream>
#include <stdexcept>

#include "HuffmanTree.h"

int main() {
    std::string input;

    std::cout << "1. 构造 Huffman 树" << '\n'
        << "   请输入要用于构建码表的字符串，按下 <Enter> 结束" << '\n'
        << "   > " << std::flush;
    std::getline(std::cin, input);
    const HuffmanTree tree{input};

    std::cout << "2. 输出码表" << '\n';
    for (const auto &[c, encoding] : tree.mapping()) {
        std::cout << "   " << c << " <-> " << encoding << '\n';
    }
    std::cout << std::flush;

    std::cout << "3. 编码" << '\n'
        << "   初始字符串的编码是：" << tree.encode(input) << '\n'
        << "   请输入其它要编码的字符串，按下 <Enter> 结束" << '\n';
    while (true) {
        std::cout << "   > " << std::flush;
        std::getline(std::cin, input);
        if (input.empty()) {
            break;
        }

        try {
            std::cout << "   " << tree.encode(input) << std::endl;
        } catch (std::out_of_range &) {
            std::cout << "错误：含有码表中不存在的字符" << std::endl;
        }
    }

    std::cout << "4. 解码" << '\n'
              << "   请输入要解码的字符串，按下 <Enter> 结束" << '\n';
    while (true) {
        std::cout << "   > " << std::flush;
        std::getline(std::cin, input);
        if (input.empty()) {
            break;
        }

        try {
            std::cout << "   " << tree.decode(input) << std::endl;
        } catch (std::runtime_error &) {
            std::cout << "错误：解码失败" << std::endl;
        }
    }

    return 0;
}
