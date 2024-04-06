#include <iostream>

#include "ThreadedBinaryTree.h"

int main() {
    const BinaryTree<char> tree{"A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))"};
    const ThreadedBinaryTree<char> threadedTree{tree};

    threadedTree.traversal([](const auto &val) {
        std::cout << val << ' ';
    });
    std::cout << std::endl;

    return 0;
}
