#ifndef COMMON_SEQSTACK_H
#define COMMON_SEQSTACK_H

#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename ElemType>
class SeqStack;

template <typename ElemType>
std::ostream &operator<<(std::ostream &os, const SeqStack<ElemType> &stack);

template <typename ElemType>
class SeqStack {
    friend std::ostream &operator<<<ElemType>(std::ostream &os, const SeqStack &stack);
public:
    SeqStack();
    SeqStack(const SeqStack &);
    ~SeqStack();
    size_t size() const;
    void push(ElemType x);
    void pop();
    ElemType get_top() const;
    bool is_empty() const;
    void empty();
private:
    void scale();
    ElemType *arr;
    size_t arrLength;
    size_t top;
    constexpr static size_t NO_TOP = -1;
    constexpr static size_t ARR_INITIAL_LENGTH = 10;
    constexpr static size_t ARR_SCALE_STEP = 10;
};

template<typename ElemType>
SeqStack<ElemType>::SeqStack() {
    arr = new ElemType[ARR_INITIAL_LENGTH];
    arrLength = ARR_INITIAL_LENGTH;
    top = NO_TOP;
}

template<typename ElemType>
SeqStack<ElemType>::SeqStack(const SeqStack &other) {
    arr = new ElemType[other.arrLength];
    arrLength = other.arrLength;
    for (size_t i = 0, l = other.size(); i < l; i++) {
        arr[i] = other.arr[i];
    }
    top = other.top;
}

template<typename ElemType>
SeqStack<ElemType>::~SeqStack() {
    delete[] arr;
}

template<typename ElemType>
size_t SeqStack<ElemType>::size() const {
    if (top == NO_TOP) {
        return 0;
    }
    return top + 1;
}

template<typename ElemType>
void SeqStack<ElemType>::push(ElemType x) {
    if (this->size() == arrLength) {
        scale();
    }
    arr[++top] = x;
}

template<typename ElemType>
void SeqStack<ElemType>::pop() {
    if (this->is_empty()) {
        throw std::out_of_range("stack is empty");
    }
    top--;
}

template<typename ElemType>
ElemType SeqStack<ElemType>::get_top() const {
    if (this->is_empty()) {
        throw std::out_of_range("stack is empty");
    }
    return arr[top];
}

template<typename ElemType>
bool SeqStack<ElemType>::is_empty() const {
    return top == NO_TOP;
}

template<typename ElemType>
void SeqStack<ElemType>::empty() {
    delete[] arr;
    arr = new ElemType[ARR_INITIAL_LENGTH];
    arrLength = ARR_INITIAL_LENGTH;
    top = NO_TOP;
}

template<typename ElemType>
void SeqStack<ElemType>::scale() {
    const size_t newLength = arrLength + ARR_SCALE_STEP;
    auto *newArr = new ElemType[newLength];
    for (size_t i = 0, l = this->size(); i < l; i++) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
}

template<typename ElemType>
std::ostream &operator<<(std::ostream &os, const SeqStack<ElemType> &stack) {
    os << "[";
    for (size_t i = 0, l = stack.size(); i < l; i++) {
        os << stack.arr[i];
        if (i != l - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

#endif //COMMON_SEQSTACK_H
