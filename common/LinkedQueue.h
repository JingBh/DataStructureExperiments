#ifndef COMMON_LINKEDQUEUE_H
#define COMMON_LINKEDQUEUE_H

#include <iostream>
#include <stdexcept>

template <typename ElemType>
class LinkedQueue;

template <typename ElemType>
std::ostream &operator<<(std::ostream &os, const LinkedQueue<ElemType> &queue);

template <typename ElemType>
class LinkedQueue {
    friend std::ostream &operator<<<ElemType>(std::ostream &os, const LinkedQueue &queue);
public:
    struct Node {
        ElemType data;
        Node *next;
    };

    LinkedQueue();
    LinkedQueue(const LinkedQueue &);
    ~LinkedQueue();
    size_t size() const;
    void enqueue(ElemType x);
    ElemType dequeue();
    ElemType get() const;
    bool is_empty() const;
    void empty();
private:
    Node *front;
    Node *rear;
};

template<typename ElemType>
LinkedQueue<ElemType>::LinkedQueue() {
    front = new Node;
    rear = front;
}

template<typename ElemType>
LinkedQueue<ElemType>::LinkedQueue(const LinkedQueue &other) {
    front = new Node;
    Node *p = front;
    for (Node *q = other.front->next; q != nullptr; q = q->next) {
        p->next = new Node;
        p = p->next;
        p->data = q->data;
    }
    rear = p;
}

template<typename ElemType>
LinkedQueue<ElemType>::~LinkedQueue() {
    this->empty();
    delete front;
}

template<typename ElemType>
size_t LinkedQueue<ElemType>::size() const {
    size_t count = 0;
    for (Node *p = front->next; p != nullptr; p = p->next, count++) {}
    return count;
}

template<typename ElemType>
void LinkedQueue<ElemType>::enqueue(ElemType x) {
    rear->next = new Node;
    rear->next->data = x;
    rear = rear->next;
}

template<typename ElemType>
ElemType LinkedQueue<ElemType>::dequeue() {
    if (this->is_empty()) {
        throw std::out_of_range("queue is empty");
    }

    Node *p = front->next;
    const ElemType x = p->data;
    front->next = p->next;
    if (p->next == nullptr) {
        rear = front;
    }
    delete p;
    return x;
}

template<typename ElemType>
ElemType LinkedQueue<ElemType>::get() const {
    if (this->is_empty()) {
        throw std::out_of_range("queue is empty");
    }

    return front->next->data;
}

template<typename ElemType>
bool LinkedQueue<ElemType>::is_empty() const {
    return front == rear;
}

template<typename ElemType>
void LinkedQueue<ElemType>::empty() {
    Node *p = front->next;
    while (p != nullptr) {
        const Node *q = p;
        p = p->next;
        delete q;
    }
    rear = front;
}

template<typename ElemType>
std::ostream& operator<<(std::ostream &os, const LinkedQueue<ElemType> &queue) {
    os << '[';
    for (auto *node = queue.front->next; node != nullptr; node = node->next) {
        os << node->data;
        if (node->next != nullptr) {
            os << ", ";
        }
    }
    os << ']';
    return os;
}

#endif //COMMON_LINKEDQUEUE_H
