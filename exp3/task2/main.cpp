#include <iostream>

#include "BinaryTree.h"
#include "inorder_traversal.h"

void callback(const char &c) {
    std::cout << c << ' ';
}

int main() {
    const BinaryTree<char> tree{"A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))"};

    std::cout << "1. 递归中序遍历" << std::endl;
    inorderTraversal<char>(tree.get_root(), callback);
    std::cout << std::endl;

    std::cout << "2. 非递归中序遍历" << std::endl;
    flatInorderTraversal<char>(tree.get_root(), callback);
    std::cout << std::endl;

    return 0;
}
