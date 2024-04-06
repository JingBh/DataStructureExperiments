#ifndef EXP3TASK5_THREADEDBINARYTREE_H
#define EXP3TASK5_THREADEDBINARYTREE_H

#include <functional>

#include "BinaryTree.h"

template<typename T>
class ThreadedBinaryTree {
public:
    struct Node {
        T data;
        bool lFlag, rFlag;
        Node *lChild, *rChild;
    };

    ThreadedBinaryTree() = delete;
    explicit ThreadedBinaryTree(const BinaryTree<T> &t);
    ~ThreadedBinaryTree();
    Node *get_root() const;
    void traversal(std::function<void (const T&)> cb) const;
private:
    Node *head = nullptr;
    Node *root = nullptr;

    void thread();
    static void thread(Node *t, Node **pre);
    static Node *copy(const BinaryTree<T>::Node *t);
    static void release(Node *t);
};

template<typename T>
inline ThreadedBinaryTree<T>::ThreadedBinaryTree(const BinaryTree<T> &t) {
    root = copy(t.get_root());
    thread();
}

template<typename T>
inline ThreadedBinaryTree<T>::~ThreadedBinaryTree() {
    release(root);
    delete head;
}

template<typename T>
inline ThreadedBinaryTree<T>::Node *ThreadedBinaryTree<T>::get_root() const {
    return root;
}

template<typename T>
void ThreadedBinaryTree<T>::traversal(std::function<void(const T &)> cb) const {
    const Node *p = root;
    while (p != nullptr && p != head) {
        while (!p->lFlag) {
            p = p->lChild;
        }
        cb(p->data);
        while (p->rFlag && p->rChild != head) {
            p = p->rChild;
            cb(p->data);
        }
        p = p->rChild;
    }
}

template<typename T>
void ThreadedBinaryTree<T>::thread() {
    delete head;
    head = new Node;
    head->lFlag = false;
    if (root == nullptr) {
        head->lChild = head;
        return;
    }
    head->lChild = root;
    Node *pre = head;
    thread(root, &pre);
    pre->rFlag = true;
    pre->rChild = head;
    head->rFlag = true;
    head->rChild = pre;
}

template<typename T>
void ThreadedBinaryTree<T>::thread(ThreadedBinaryTree::Node *t, ThreadedBinaryTree::Node **pre) {
    if (t == nullptr) {
        return;
    }
    thread(t->lChild, pre);
    if (t->lChild == nullptr) {
        t->lFlag = true;
        t->lChild = *pre;
    } else {
        t->lFlag = false;
    }
    if ((*pre)->rChild == nullptr) {
        (*pre)->rFlag = true;
        (*pre)->rChild = t;
    } else {
        (*pre)->rFlag = false;
    }
    *pre = t;
    thread(t->rChild, pre);
}

template<typename T>
ThreadedBinaryTree<T>::Node *ThreadedBinaryTree<T>::copy(const BinaryTree<T>::Node *t) {
    if (t == nullptr) {
        return nullptr;
    }
    return new Node{t->data, false, false, copy(t->lChild), copy(t->rChild)};
}

template<typename T>
void ThreadedBinaryTree<T>::release(ThreadedBinaryTree::Node *t) {
    if (t == nullptr) {
        return;
    }
    if (!t->lFlag) {
        release(t->lChild);
    }
    if (!t->rFlag) {
        release(t->rChild);
    }
    delete t;
}

#endif //EXP3TASK5_THREADEDBINARYTREE_H
