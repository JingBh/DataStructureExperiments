#ifndef EXP5TASK1_BINARYSEARCH_H
#define EXP5TASK1_BINARYSEARCH_H

#include <cstddef>
#include <iostream>

template<typename T>
class BinarySearch {
public:
    BinarySearch(const T *arr, size_t n);
    size_t recursive(const T &key) const;
    size_t non_recursive(const T &key) const;
    static constexpr size_t NOT_FOUND = -1;
private:
    const T *arr;
    const size_t n;
    size_t recursive(const T &key, size_t lower, size_t upper) const;
};

template<typename T>
BinarySearch<T>::BinarySearch(const T *arr, const size_t n)
    : arr{arr}, n{n} {}

template<typename T>
size_t BinarySearch<T>::non_recursive(const T &key) const {
    size_t mid, lower = 0, upper = n - 1;
    while (lower <= upper) {
        std::cout << "lower = " << lower << ", upper = " << upper << std::endl;
        mid = (lower + upper) / 2;
        if (arr[mid] > key) {
            upper = mid - 1;
        } else if (arr[mid] < key) {
            lower = mid + 1;
        } else {
            return mid;
        }
    }
    return NOT_FOUND;
}

template<typename T>
inline size_t BinarySearch<T>::recursive(const T &key) const {
    return recursive(key, 0, n - 1);
}

template<typename T>
size_t BinarySearch<T>::recursive(const T &key, const size_t lower, const size_t upper) const {
    if (lower > upper) {
        return NOT_FOUND;
    }
    std::cout << "lower = " << lower << ", upper = " << upper << std::endl;
    size_t mid = (lower + upper) / 2;
    if (arr[mid] > key) {
        return recursive(key, lower, mid - 1);
    } else if (arr[mid] < key) {
        return recursive(key, mid + 1, upper);
    } else {
        return mid;
    }
}

#endif //EXP5TASK1_BINARYSEARCH_H
