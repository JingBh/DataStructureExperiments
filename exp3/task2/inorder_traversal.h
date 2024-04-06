#ifndef EXP3TASK2_INORDER_TRAVERSAL_H
#define EXP3TASK2_INORDER_TRAVERSAL_H

#include <functional>

#include "BinaryTree.h"
#include "LinkedStack.h"

template <typename T>
void inorderTraversal(const typename BinaryTree<T>::Node *t, std::function<void (const T&)> cb) {
    if (t == nullptr) {
        return;
    }
    inorderTraversal<T>(t->lChild, cb);
    cb(t->data);
    inorderTraversal<T>(t->rChild, cb);
}

template <typename T>
void flatInorderTraversal(const typename BinaryTree<T>::Node *t, std::function<void (const T&)> cb) {
    LinkedStack<const typename BinaryTree<T>::Node *> stack;
    const typename BinaryTree<T>::Node *p = t;
    while (p != nullptr || !stack.is_empty()) {
        while (p != nullptr) {
            stack.push(p);
            p = p->lChild;
        }
        if (!stack.is_empty()) {
            p = stack.get_top();
            stack.pop();
            cb(p->data);
            p = p->rChild;
        }
    }
}

#endif //EXP3TASK2_INORDER_TRAVERSAL_H
