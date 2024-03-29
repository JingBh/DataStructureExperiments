#ifndef COMMON_CIRCULARQUEUE_H
#define COMMON_CIRCULARQUEUE_H

#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename ElemType>
class CircularQueue;

template <typename ElemType>
std::ostream &operator<<(std::ostream &os, const CircularQueue<ElemType> &queue);

template <typename ElemType>
class CircularQueue {
    friend std::ostream &operator<<<ElemType>(std::ostream &os, const CircularQueue &queue);
public:
    CircularQueue();
    CircularQueue(const CircularQueue &);
    ~CircularQueue();
    size_t size() const;
    void enqueue(ElemType x);
    ElemType dequeue();
    ElemType get() const;
    bool is_empty() const;
    void empty();
private:
    void scale();
    ElemType *arr;
    size_t arrLength;
    size_t rear;
    size_t front;
    constexpr static size_t ARR_INITIAL_LENGTH = 10;
    constexpr static size_t ARR_SCALE_STEP = 10;
};

template <typename ElemType>
CircularQueue<ElemType>::CircularQueue() {
    arr = new ElemType[ARR_INITIAL_LENGTH];
    arrLength = ARR_INITIAL_LENGTH;
    rear = front = arrLength - 1;
}

template <typename ElemType>
CircularQueue<ElemType>::CircularQueue(const CircularQueue &other) {
    arr = new ElemType[other.arrLength];
    arrLength = other.arrLength;
    rear = other.rear;
    front = other.front;
    for (size_t i = 0; i < arrLength; ++i) {
        arr[i] = other.arr[i];
    }
}

template <typename ElemType>
CircularQueue<ElemType>::~CircularQueue() {
    delete[] arr;
}

template <typename ElemType>
size_t CircularQueue<ElemType>::size() const {
    return (rear - front + arrLength) % arrLength;
}

template <typename ElemType>
void CircularQueue<ElemType>::enqueue(ElemType x) {
    if ((rear + 1) % arrLength == front) {
        scale();
    }
    rear = (rear + 1) % arrLength;
    arr[rear] = x;
}

template <typename ElemType>
ElemType CircularQueue<ElemType>::dequeue() {
    if (this->is_empty()) {
        throw std::out_of_range("queue is empty");
    }
    front = (front + 1) % arrLength;
    return arr[front];
}

template <typename ElemType>
ElemType CircularQueue<ElemType>::get() const {
    if (this->is_empty()) {
        throw std::out_of_range("queue is empty");
    }
    return arr[(front + 1) % arrLength];
}

template <typename ElemType>
bool CircularQueue<ElemType>::is_empty() const {
    return front == rear;
}

template <typename ElemType>
void CircularQueue<ElemType>::empty() {
    front = rear = arrLength - 1;
}

template<typename ElemType>
void CircularQueue<ElemType>::scale() {
    const size_t newLength = arrLength + ARR_SCALE_STEP;
    auto *newArr = new ElemType[newLength];
    for (size_t i = front, j = 0; i != rear; i = (i + 1) % arrLength, ++j) {
        newArr[j] = arr[(i + 1) % arrLength];
    }
    rear = size() - 1;
    front = newLength - 1;
    delete[] arr;
    arr = newArr;
    arrLength = newLength;
}

template <typename ElemType>
std::ostream &operator<<(std::ostream &os, const CircularQueue<ElemType> &queue) {
    os << '[';
    for (size_t i = queue.front; i != queue.rear; i = (i + 1) % queue.arrLength) {
        os << queue.arr[(i + 1) % queue.arrLength];
        if ((i + 1) % queue.arrLength != queue.rear) {
            os << ", ";
        }
    }
    os << ']';
    return os;
}

#endif //COMMON_CIRCULARQUEUE_H
