#ifndef COMMON_SINGLELINKEDLIST_H
#define COMMON_SINGLELINKEDLIST_H

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <stdexcept>

template <typename ElemType>
class LinkedList {
public:
    struct Node {
        ElemType data;
        Node *next;
    };

    LinkedList();
    LinkedList(const ElemType *arr, size_t n);
    LinkedList(std::initializer_list<ElemType> list);
    ~LinkedList();
    size_t size() const;
    Node *get_first() const;
    Node *get_node(size_t i) const;
    ElemType get(size_t i) const;
    size_t locate(ElemType x) const;
    void prepend(ElemType x);
    void insert(size_t i, ElemType x);
    void remove(size_t i);
    bool is_empty() const;
    void empty();
    void print() const;
    constexpr static size_t INDEX_NOT_FOUND = -1;
private:
    Node *first;
};

template <typename ElemType>
LinkedList<ElemType>::LinkedList() {
    first = nullptr;
}

template <typename ElemType>
LinkedList<ElemType>::LinkedList(const ElemType *arr, const size_t n) {
    first = nullptr;
    for (size_t i = n; i > 0; i--) {
        prepend(arr[i - 1]);
    }
}

template<typename ElemType>
LinkedList<ElemType>::LinkedList(std::initializer_list<ElemType> list) {
    first = nullptr;
    for (auto it = list.end(); it != list.begin(); ) {
        prepend(*--it);
    }
}

template <typename ElemType>
LinkedList<ElemType>::~LinkedList() {
    while (first != nullptr) {
        auto *node = first;
        first = first->next;
        delete node;
    }
}

template <typename ElemType>
size_t LinkedList<ElemType>::size() const {
    size_t n = 0;
    for (auto *node = first; node != nullptr; node = node->next) {
        n++;
    }
    return n;
}

template<typename ElemType>
typename LinkedList<ElemType>::Node *LinkedList<ElemType>::get_first() const {
    return first;
}

template <typename ElemType>
typename LinkedList<ElemType>::Node *LinkedList<ElemType>::get_node(const size_t i) const {
    auto *node = first;
    for (size_t j = 0; j < i; j++) {
        if (node == nullptr) {
            throw std::out_of_range("Index out of range");
        }
        node = node->next;
    }
    if (node == nullptr) {
        throw std::out_of_range("Index out of range");
    }
    return node;
}

template <typename ElemType>
ElemType LinkedList<ElemType>::get(const size_t i) const {
    return get_node(i)->data;
}

template <typename ElemType>
size_t LinkedList<ElemType>::locate(const ElemType x) const {
    size_t i = 0;
    for (auto *node = first; node != nullptr; node = node->next) {
        if (node->data == x) {
            return i;
        }
        i++;
    }
    return INDEX_NOT_FOUND;
}

template <typename ElemType>
void LinkedList<ElemType>::prepend(const ElemType x) {
    insert(0, x);
}

template<typename ElemType>
void LinkedList<ElemType>::insert(const size_t i, const ElemType x) {
    if (i == 0) {
        auto *node = new Node;
        node->data = x;
        node->next = first;
        first = node;
        return;
    }
    auto *prev = get_node(i - 1);
    auto *node = new Node;
    node->data = x;
    node->next = prev->next;
    prev->next = node;
}

template<typename ElemType>
void LinkedList<ElemType>::remove(const size_t i) {
    if (i == 0) {
        auto *node = first;
        first = first->next;
        delete node;
        return;
    }
    auto *prev = get_node(i - 1);
    auto *node = prev->next;
    prev->next = node->next;
    delete node;
}

template<typename ElemType>
bool LinkedList<ElemType>::is_empty() const {
    return first == nullptr;
}

template<typename ElemType>
void LinkedList<ElemType>::empty() {
    while (first != nullptr) {
        auto *node = first;
        first = first->next;
        delete node;
    }
}

template<typename ElemType>
void LinkedList<ElemType>::print() const {
    std::cout << *this << std::endl;
}

template<typename ElemType>
std::ostream &operator<<(std::ostream &os, const LinkedList<ElemType> &list) {
    os << "[";
    for (auto *node = list.get_first(); node != nullptr; node = node->next) {
        os << node->data;
        if (node->next != nullptr) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

#endif //COMMON_SINGLELINKEDLIST_H
