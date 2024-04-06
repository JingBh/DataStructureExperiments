#include <iostream>

#include "BinaryTree.h"

template <typename T>
std::size_t count(const typename BinaryTree<T>::Node *t) {
    if (t == nullptr) {
        return 0;
    }
    return 1 + count<T>(t->lChild) + count<T>(t->rChild);
}

int main() {
    const BinaryTree<char> tree{"A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))"};

    std::cout << "树有 " << count<char>(tree.get_root()) << " 个结点";

    return 0;
}
