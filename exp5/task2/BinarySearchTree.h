#ifndef EXP5TASK2_BINARYSEARCHTREE_H
#define EXP5TASK2_BINARYSEARCHTREE_H

#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <string>

template<typename T>
class BinarySearchTree {
public:
    struct Node {
        T key;
        Node *lChild;
        Node *rChild;
    };

    BinarySearchTree() = default;
    BinarySearchTree(T arr[], size_t n);
    BinarySearchTree(std::initializer_list<T> list);
    ~BinarySearchTree();
    const Node *search(const T &key) const;
    const Node *search_flat(const T &key) const;
    void insert(const T &key);
    void remove(const T &key);
    bool verify() const;
    std::string to_parentheses_list() const;
private:
    const Node *search(const Node *bt, const T &key) const;
    Node *insert(Node *bt, const T &key);
    void release(Node *bt);
    void inorder_traversal(const Node *bt, const std::function<void(const T &)> &cb) const;
    static void to_parentheses_list(std::ostringstream &ss, const Node *bt);
    Node *root = nullptr;
};

template<typename T>
BinarySearchTree<T>::BinarySearchTree(T *arr, size_t n) {
    for (size_t i = 0; i < n; i++) {
        insert(arr[i]);
    }
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(std::initializer_list<T> list) {
    for (const T &i : list) {
        insert(i);
    }
}

template<typename T>
inline BinarySearchTree<T>::~BinarySearchTree() {
    release(root);
}

template<typename T>
inline const BinarySearchTree<T>::Node *BinarySearchTree<T>::search(const T &key) const {
#ifdef EXP5TASK2_PRINT_SEARCH_PATH
    std::cout << "查找路径：";
#endif //EXP5TASK2_PRINT_SEARCH_PATH
    return search(root, key);
}

template<typename T>
const BinarySearchTree<T>::Node *BinarySearchTree<T>::search_flat(const T &key) const {
#ifdef EXP5TASK2_PRINT_SEARCH_PATH
    std::cout << "查找路径：";
#endif //EXP5TASK2_PRINT_SEARCH_PATH
    Node *p = root;
    while (p != nullptr) {
#ifdef EXP5TASK2_PRINT_SEARCH_PATH
        std::cout << p->key;
        if (p->key == key) {
            std::cout << std::endl;
        } else {
            std::cout << " -> ";
        }
#endif //EXP5TASK2_PRINT_SEARCH_PATH
        if (p->key == key) {
            return p;
        }
        if (p->key > key) {
            p = p->lChild;
        } else {
            p = p->rChild;
        }
    }
    return nullptr;
}

template<typename T>
inline void BinarySearchTree<T>::insert(const T &key) {
    root = insert(root, key);
}

template<typename T>
void BinarySearchTree<T>::remove(const T &key) {
    // find the node and its parent
    Node *p = root, *pp = nullptr;
    while (p != nullptr && p->key != key) {
        if (p->key > key) {
            pp = p;
            p = p->lChild;
        } else {
            pp = p;
            p = p->rChild;
        }
    }

    // case 1: p is not found
    if (p == nullptr) {
        return;
    }

    // case 2: p has none or one child
    if (p->lChild == nullptr || p->rChild == nullptr) {
        Node *child = p->lChild != nullptr ? p->lChild : p->rChild;
        if (pp == nullptr) {
            root = child;
        } else if (pp->lChild == p) {
            pp->lChild = child;
        } else {
            pp->rChild = child;
        }
        delete p;
        return;
    }

    // case 3: p has both left and right children
    // find maximum node in left subtree
    Node *m = p->lChild, *mp = p;
    while (m->rChild != nullptr) {
        mp = m;
        m = m->rChild;
    }
    p->key = m->key;
    if (mp == p) {
        mp->lChild = m->lChild;
    } else {
        mp->rChild = m->lChild;
    }
    delete m;
}

template<typename T>
bool BinarySearchTree<T>::verify() const {
    if (root == nullptr) {
        return true;
    }
    T last = root->key;
    bool first = true, result = true;
    inorder_traversal(root, [&](const T &key) {
        if (!first && key < last) {
            result = false;
        }
        first = false;
        last = key;
    });
    return result;
}

template<typename T>
std::string BinarySearchTree<T>::to_parentheses_list() const {
    std::ostringstream ss;
    to_parentheses_list(ss, root);
    return ss.str();
}

template<typename T>
const BinarySearchTree<T>::Node *BinarySearchTree<T>::search(const BinarySearchTree::Node *bt, const T &key) const {
    if (bt == nullptr) {
        return nullptr;
    }
#ifdef EXP5TASK2_PRINT_SEARCH_PATH
    std::cout << bt->key;
    if (bt->key == key) {
        std::cout << std::endl;
    } else {
        std::cout << " -> ";
    }
#endif //EXP5TASK2_PRINT_SEARCH_PATH
    if (bt->key == key) {
        return bt;
    }
    if (bt->key > key) {
        return search(bt->lChild, key);
    }
    return search(bt->rChild, key);
}

template<typename T>
BinarySearchTree<T>::Node *BinarySearchTree<T>::insert(BinarySearchTree::Node *bt, const T &key) {
    if (bt == nullptr) {
        Node *p = new Node{key, nullptr, nullptr};
        return p;
    }
    if (bt->key > key) {
        bt->lChild = insert(bt->lChild, key);
    } else {
        bt->rChild = insert(bt->rChild, key);
    }
    return bt;
}

template<typename T>
void BinarySearchTree<T>::release(BinarySearchTree::Node *bt) {
    if (bt == nullptr) {
        return;
    }
    release(bt->lChild);
    release(bt->rChild);
    delete bt;
}

template<typename T>
void BinarySearchTree<T>::inorder_traversal(const BinarySearchTree::Node *bt, const std::function<void(const T &)> &cb) const {
    if (bt == nullptr) {
        return;
    }
    inorder_traversal(bt->lChild, cb);
    cb(bt->key);
    inorder_traversal(bt->rChild, cb);
}

template<typename T>
void BinarySearchTree<T>::to_parentheses_list(std::ostringstream &ss, const BinarySearchTree::Node *bt) {
    if (bt == nullptr) {
        return;
    }
    ss << bt->key;
    if (bt->lChild || bt->rChild) {
        ss << '(';
        to_parentheses_list(ss, bt->lChild);
        ss << ", ";
        to_parentheses_list(ss, bt->rChild);
        ss << ')';
    }
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const BinarySearchTree<T> &bt) {
    os << bt.to_parentheses_list();
    return os;
}

#endif //EXP5TASK2_BINARYSEARCHTREE_H
