#include <iostream>

#include "BinaryTree.h"

int main() {
    std::cout << "1. 创建二叉树" << std::endl;
    const BinaryTree<char> tree{"A(B(D, E(H(J, K(L, M(, N))))), C(F, G(, I)))"};

    std::cout << "2. 输出二叉树：" << std::endl;
    std::cout << tree.toParenthesesList() << std::endl;

    std::cout << "3. 输出“H”结点左、右孩子的值：";
    const auto *h = tree.find('H');
    std::cout << h->lChild->data << ", " << h->rChild->data << std::endl;

    std::cout << "4. 输出树的高度：" << tree.depth() << std::endl;

    std::cout << "5. 释放二叉树" << std::endl;

    return 0;
}
