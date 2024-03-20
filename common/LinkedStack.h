#ifndef COMMON_LINKEDSTACK_H
#define COMMON_LINKEDSTACK_H

#include <cstddef>
#include <stdexcept>

template <typename ElemType>
class LinkedStack {
public:
    struct Node {
        ElemType data;
        Node *next;
    };

    LinkedStack();
    ~LinkedStack();
    size_t size() const;
    void push(ElemType x);
    void pop();
    ElemType getTop() const;
    bool is_empty() const;
    void empty();
private:
    Node *first;
};

template<typename ElemType>
LinkedStack<ElemType>::LinkedStack() {
    first = nullptr;
}

template<typename ElemType>
LinkedStack<ElemType>::~LinkedStack() {
    this->empty();
}

template<typename ElemType>
size_t LinkedStack<ElemType>::size() const {
    size_t n = 0;
    for (auto *node = first; node != nullptr; node = node->next, n++) {}
    return n;
}

template<typename ElemType>
void LinkedStack<ElemType>::push(ElemType x) {
    auto *node = new Node;
    node->data = x;
    node->next = first;
    first = node;
}

template<typename ElemType>
void LinkedStack<ElemType>::pop() {
    if (this->is_empty()) {
        throw std::out_of_range("stack is empty");
    }
    auto *node = first;
    first = first->next;
    delete node;
}

template<typename ElemType>
ElemType LinkedStack<ElemType>::getTop() const {
    if (this->is_empty()) {
        throw std::out_of_range("stack is empty");
    }
    return first->data;
}

template<typename ElemType>
bool LinkedStack<ElemType>::is_empty() const {
    return first == nullptr;
}

template<typename ElemType>
void LinkedStack<ElemType>::empty() {
    while (first != nullptr) {
        auto *node = first;
        first = first->next;
        delete node;
    }
}

#endif //COMMON_LINKEDSTACK_H
