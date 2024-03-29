#ifndef EXP2TASK3_LINKEDCIRCULARQUEUE_H
#define EXP2TASK3_LINKEDCIRCULARQUEUE_H

#include <iostream>
#include <stdexcept>

template <typename ElemType>
class LinkedCircularQueue;

template <typename ElemType>
std::ostream &operator<<(std::ostream &os, const LinkedCircularQueue<ElemType> &queue);

template <typename ElemType>
class LinkedCircularQueue {
    friend std::ostream &operator<<<ElemType>(std::ostream &os, const LinkedCircularQueue &queue);
public:
    struct Node {
        ElemType data;
        Node *next;
    };

    LinkedCircularQueue();
    ~LinkedCircularQueue();
    void enqueue(ElemType x);
    ElemType dequeue();
    ElemType get() const;
    bool is_empty() const;
    void empty();
private:
    Node *tail;
};

template<typename ElemType>
LinkedCircularQueue<ElemType>::LinkedCircularQueue() {
    tail = new Node;
    tail->next = tail;
}

template<typename ElemType>
LinkedCircularQueue<ElemType>::~LinkedCircularQueue() {
    empty();
    delete tail;
}

template<typename ElemType>
void LinkedCircularQueue<ElemType>::enqueue(ElemType x) {
    Node *p = new Node;
    p->data = x;
    p->next = tail->next;
    tail->next = p;
    tail = p;
}

template<typename ElemType>
ElemType LinkedCircularQueue<ElemType>::dequeue() {
    if (this->is_empty()) {
        throw std::out_of_range("queue is empty");
    }

    Node *p = tail->next->next;
    const ElemType x = p->data;
    tail->next->next = p->next;
    if (p == tail) {
        tail = tail->next;
    }
    delete p;
    return x;
}

template<typename ElemType>
ElemType LinkedCircularQueue<ElemType>::get() const {
    if (this->is_empty()) {
        throw std::out_of_range("queue is empty");
    }

    return tail->next->next->data;
}

template<typename ElemType>
bool LinkedCircularQueue<ElemType>::is_empty() const {
    return tail->next == tail;
}

template<typename ElemType>
void LinkedCircularQueue<ElemType>::empty() {
    while (tail->next != tail) {
        Node *p = tail->next->next;
        tail->next->next = p->next;
        if (p == tail) {
            tail = tail->next;
        }
        delete p;
    }
}

template<typename ElemType>
std::ostream& operator<<(std::ostream &os, const LinkedCircularQueue<ElemType> &queue) {
    os << '[';
    for (auto *node = queue.tail->next->next; node != queue.tail->next; node = node->next) {
        os << node->data;
        if (node->next != queue.tail->next) {
            os << ", ";
        }
    }
    os << ']';
    return os;
}

#endif //EXP2TASK3_LINKEDCIRCULARQUEUE_H
