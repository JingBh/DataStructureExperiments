#ifndef COMMON_BINARYTREE_H
#define COMMON_BINARYTREE_H

#include <cctype>
#include <cmath>
#include <cstddef>
#include <sstream>
#include <string>
#include <stdexcept>

#include "LinkedStack.h"

template<typename T>
class BinaryTree {
public:
    struct Node {
        T data;
        Node *lChild, *rChild;
    };

    BinaryTree() = default;
    explicit BinaryTree(const std::string &parenthesesList);
    ~BinaryTree();
    const Node *get_root() const;
    const Node *find(T x) const;
    std::size_t depth() const;
    std::string toParenthesesList() const;
private:
    Node *root = nullptr;

    static void release(Node *t);
    static const Node *find(const Node *t, const T &x);
    static std::size_t depth(const Node *t);
    static void toParenthesesList(std::ostringstream &ss, const Node *t);
};

template<typename T>
inline BinaryTree<T>::~BinaryTree() {
    release(root);
}

template<typename T>
inline const BinaryTree<T>::Node *BinaryTree<T>::get_root() const {
    return root;
}

template<typename T>
inline const BinaryTree<T>::Node *BinaryTree<T>::find(const T x) const {
    return find(root, x);
}

template<typename T>
inline std::size_t BinaryTree<T>::depth() const {
    return depth(root);
}

template<typename T>
inline std::string BinaryTree<T>::toParenthesesList() const {
    std::ostringstream ss;
    toParenthesesList(ss, root);
    return ss.str();
}

template<typename T>
void BinaryTree<T>::release(BinaryTree::Node *t) {
    if (t == nullptr) {
        return;
    }
    release(t->lChild);
    release(t->rChild);
    delete t;
}

template<typename T>
const BinaryTree<T>::Node *BinaryTree<T>::find(const BinaryTree::Node *t, const T &x) {
    if (t == nullptr) {
        return nullptr;
    }
    if (t->data == x) {
        return t;
    }
    if (auto *p = find(t->lChild, x)) {
        return p;
    }
    return find(t->rChild, x);
}

template<typename T>
std::size_t BinaryTree<T>::depth(const BinaryTree::Node *t) {
    if (t == nullptr) {
        return 0;
    }
    return std::max(depth(t->lChild), depth(t->rChild)) + 1;
}

template<typename T>
void BinaryTree<T>::toParenthesesList(std::ostringstream &ss, const BinaryTree::Node *t) {
    if (t == nullptr) {
        return;
    }
    ss << t->data;
    if (t->lChild || t->rChild) {
        ss << '(';
        toParenthesesList(ss, t->lChild);
        ss << ", ";
        toParenthesesList(ss, t->rChild);
        ss << ')';
    }
}

template<> BinaryTree<char>::BinaryTree(const std::string &parenthesesList) {
    LinkedStack<BinaryTree<char>::Node *> stack;
    BinaryTree<char>::Node *p = nullptr;
    bool right = false;

    for (const char c : parenthesesList) {
        if (c == '(') {
            if (p == nullptr) {
                continue;
            }
            stack.push(p);
            right = false;
        } else if (c == ')') {
            try {
                stack.pop();
            } catch (std::out_of_range &) {
                break;
            }
        } else if (c == ',') {
            right = true;
        } else if (!std::isblank(c)) {
            p = new BinaryTree<char>::Node{c, nullptr, nullptr};
            if (root == nullptr) {
                root = p;
            } else {
                right ? stack.get_top()->rChild = p : stack.get_top()->lChild = p;
            }
        }
    }
}

#endif //COMMON_BINARYTREE_H
