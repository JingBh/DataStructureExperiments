#include <iostream>

#define EXP5TASK2_PRINT_SEARCH_PATH
#include "BinarySearchTree.h"

int main() {
    std::cout << "1. 创建一棵二叉排序树" << std::endl;
    BinarySearchTree<int> bt{4, 9, 0, 1, 8, 6, 3, 5, 2, 7};
    std::cout << "bt：" << bt << std::endl;
    std::cout << std::endl;

    if (bt.verify()) {
        std::cout << "2. bt 是一棵二叉排序树" << std::endl;
    } else {
        std::cout << "2. bt 不是一棵二叉排序树" << std::endl;
        return 1;
    }
    std::cout << std::endl;

    std::cout << "3.1 递归查找“6”" << std::endl;
    bt.search(6);
    std::cout << std::endl;

    std::cout << "3.2 非递归查找“6”" << std::endl;
    bt.search_flat(6);
    std::cout << std::endl;

    std::cout << "4.1 删除“4”" << std::endl;
    bt.remove(4);
    std::cout << "bt：" << bt << std::endl;
    if (bt.verify()) {
        std::cout << "bt 是一棵二叉排序树" << std::endl;
    } else {
        std::cout << "bt 不是一棵二叉排序树" << std::endl;
        return 1;
    }
    std::cout << std::endl;

    std::cout << "4.2 删除“5”" << std::endl;
    bt.remove(5);
    std::cout << "bt：" << bt << std::endl;
    if (bt.verify()) {
        std::cout << "bt 是一棵二叉排序树" << std::endl;
    } else {
        std::cout << "bt 不是一棵二叉排序树" << std::endl;
        return 1;
    }

    return 0;
}
