#include <iostream>
#include <stdexcept>
#include <tuple>
#include <vector>

#include "LinkedJosephusCircle.h"
#include "SeqJosephusCircle.h"

int main() {
    std::vector<std::tuple<int, int, int>> args {
        { 9, 1, 5 },
        { 9, 1, 0 },
        { 9, 1, 10 }
    };

    while (true) {
        int n, s, m;
        std::cout << "请输入一组参数（n, s, m），输入 0 0 0 结束：";
        std::cin >> n >> s >> m;
        if (n == 0) {
            break;
        }
        args.emplace_back(n, s, m);
    }

    std::cout << '\n'
        << "===== 测试顺序表实现 ====="
        << '\n' << std::endl;

    for (const auto &set : args) {
        try {
            std::cout << "=> "
            << "n = " << std::get<0>(set)
            << ", s = " << std::get<1>(set)
            << ", m = " << std::get<2>(set)
            << std::endl;
            auto circle = SeqJosephusCircle(std::get<0>(set), std::get<1>(set), std::get<2>(set));
            std::cout << "   初始状态：" << circle << std::endl;
            while (circle.remaining() > 0) {
                const int out = circle.out();
                std::cout << "   " << out << " 出圈，剩余：" << circle << std::endl;
            }
        } catch (const std::exception &e) {
            std::cout << "   错误：" << e.what() << std::endl;
        }
    }

    std::cout << '\n'
        << "===== 测试循环链表实现 ====="
    << '\n' << std::endl;

    for (const auto &set : args) {
        try {
            std::cout << "=> "
            << "n = " << std::get<0>(set)
            << ", s = " << std::get<1>(set)
            << ", m = " << std::get<2>(set)
            << std::endl;
            auto circle = LinkedJosephusCircle(std::get<0>(set), std::get<1>(set), std::get<2>(set));
            std::cout << "   初始状态：" << circle << std::endl;
            while (circle.remaining() > 0) {
                const int out = circle.out();
                std::cout << "   " << out << " 出圈，剩余：" << circle << std::endl;
            }
        } catch (const std::exception &e) {
            std::cout << "   错误：" << e.what() << std::endl;
        }
    }

    return 0;
}
