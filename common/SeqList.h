#ifndef COMMON_SEQLIST_H
#define COMMON_SEQLIST_H

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <stdexcept>

template<typename ElemType>
class SeqList {
public:
    SeqList();
    SeqList(const ElemType *arr, size_t n);
    SeqList(std::initializer_list<ElemType> list);
    ~SeqList();
    size_t size() const;
    ElemType get(size_t i) const;
    size_t locate(ElemType x) const;
    void append(ElemType x);
    void insert(size_t i, ElemType x);
    void remove(size_t i);
    bool is_empty() const;
    void empty();
    void print() const;
    constexpr static size_t INDEX_NOT_FOUND = -1;
private:
    void scale();
    ElemType *arr;
    size_t arrLength;
    size_t length;
    constexpr static size_t ARR_INITIAL_LENGTH = 10;
    constexpr static size_t ARR_SCALE_STEP = 10;
};

template<typename ElemType>
SeqList<ElemType>::SeqList() {
    arr = new ElemType[ARR_INITIAL_LENGTH];
    arrLength = ARR_INITIAL_LENGTH;
    length = 0;
}

template<typename ElemType>
SeqList<ElemType>::SeqList(const ElemType* arr, const size_t n) {
    this->arr = new ElemType[n];
    arrLength = n;
    this->length = n;
    for (size_t i = 0; i < n; i++) {
        this->arr[i] = arr[i];
    }
}

template<typename ElemType>
SeqList<ElemType>::SeqList(std::initializer_list<ElemType> list) {
    length = list.size();
    arr = new ElemType[length];
    arrLength = length;
    size_t i = 0;
    for (const auto &x : list) {
        arr[i++] = x;
    }
}

template<typename ElemType>
SeqList<ElemType>::~SeqList() {
    delete[] arr;
}

template<typename ElemType>
size_t SeqList<ElemType>::size() const {
    return length;
}

template<typename ElemType>
ElemType SeqList<ElemType>::get(const size_t i) const {
    if (i >= length) {
        throw std::out_of_range("Index out of range");
    }
    return arr[i];
}

template<typename ElemType>
size_t SeqList<ElemType>::locate(const ElemType x) const {
    for (size_t i = 0; i < length; i++) {
        if (arr[i] == x) {
            return i;
        }
    }
    return INDEX_NOT_FOUND;
}

template<typename ElemType>
void SeqList<ElemType>::append(const ElemType x) {
    insert(length, x);
}

template<typename ElemType>
void SeqList<ElemType>::insert(const size_t i, const ElemType x) {
    if (i > length) {
        throw std::out_of_range("Index out of range");
    }
    if (length == arrLength) {
        scale();
    }
    if (i == length) {
        // append
        arr[i] = x;
    } else {
        for (size_t j = length; j > i; j--) {
            arr[j] = arr[j - 1];
        }
        arr[i] = x;
    }
    length++;
}

template<typename ElemType>
void SeqList<ElemType>::remove(const size_t i) {
    if (i > length) {
        throw std::out_of_range("Index out of range");
    }
    for (size_t j = i; j < length - 1; j++) {
        arr[j] = arr[j + 1];
    }
    length--;
}

template<typename ElemType>
bool SeqList<ElemType>::is_empty() const {
    return length == 0;
}

template<typename ElemType>
void SeqList<ElemType>::empty() {
    delete[] arr;
    arr = new ElemType[ARR_INITIAL_LENGTH];
    arrLength = ARR_INITIAL_LENGTH;
    length = 0;
}

template<typename ElemType>
void SeqList<ElemType>::print() const {
    std::cout << *this << std::endl;
}

template<typename ElemType>
void SeqList<ElemType>::scale() {
    const size_t newLength = arrLength + ARR_SCALE_STEP;
    auto *newArr = new ElemType[newLength];
    for (size_t i = 0; i < length; i++) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
}

template<typename ElemType>
std::ostream &operator<<(std::ostream &os, const SeqList<ElemType> &list) {
    os << "[";
    for (size_t i = 0; i < list.size(); i++) {
        os << list.get(i);
        if (i != list.size() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

#endif //COMMON_SEQLIST_H
