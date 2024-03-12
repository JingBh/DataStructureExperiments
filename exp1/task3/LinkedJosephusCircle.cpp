#include <stdexcept>
#include "LinkedJosephusCircle.h"

LinkedJosephusCircle::LinkedJosephusCircle(int n, int s, int m)
    : length(n), start(s - 1), step(m) {
    if (n < 1) {
        throw std::invalid_argument("n 必须为正数");
    }
    if (s < 1) {
        throw std::invalid_argument("s 必须为正数");
    }
    if (m < 1) {
        throw std::invalid_argument("m 必须为正数");
    }

    head = new Node{ 0, nullptr };
    Node *p = head;
    for (int i = 0; i < length; p = p->next, i++) {
        auto *node = new Node{ i + 1, nullptr };
        p->next = node;
        if (i == length - 1) {
            node->next = head->next;
        }
    }
}

LinkedJosephusCircle::~LinkedJosephusCircle() {
    const Node *first = head->next;
    const Node *p = head;
    if (!p->next) {
        delete p;
        return;
    }
    while (true) {
        const Node *q = p->next;
        delete p;
        if (q == first && p != head) {
            // circled back
            break;
        }
        p = q;
    }
}

int LinkedJosephusCircle::remaining() const {
    return length;
}

int LinkedJosephusCircle::out() {
    if (length == 0) {
        throw std::out_of_range("空圈");
    }
    const int i = start + step - 1;
    Node *p = head;
    for (int j = 0; j < i; p = p->next, j++) {}
    const Node *q = p->next;
    const int result = q->data;
    p->next = q->next;
    if (p == q) {
        // only one element left
        head->next = nullptr;
    } else if (head->next == q) {
        // deleting first element
        head->next = q->next;
    }
    delete q;
    start = i % length;
    length--;
    return result;
}

std::ostream &operator<<(std::ostream &os, const LinkedJosephusCircle &circle) {
    os << "[";
    const LinkedJosephusCircle::Node *p = circle.head->next;
    for (int i = 0; i < circle.length; p = p->next, i++) {
        os << p->data;
        if (i != circle.length - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
