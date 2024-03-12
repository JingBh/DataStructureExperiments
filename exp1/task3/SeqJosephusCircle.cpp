#include <stdexcept>
#include "SeqJosephusCircle.h"

SeqJosephusCircle::SeqJosephusCircle(const int n, const int s, const int m)
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
    arr = new int[length];
    for (int i = 0; i < length; i++) {
        arr[i] = i + 1;
    }
}

SeqJosephusCircle::~SeqJosephusCircle() {
    delete[] arr;
}

int SeqJosephusCircle::remaining() const {
    return length;
}

int SeqJosephusCircle::out() {
    if (length == 0) {
        throw std::out_of_range("空圈");
    }
    const int i = (start + step - 1) % length;
    const int result = arr[i];
    for (int j = i; j < length - 1; j++) {
        arr[j] = arr[j + 1];
    }
    length--;
    start = i;
    return result;
}

std::ostream &operator<<(std::ostream &os, const SeqJosephusCircle &circle) {
    os << "[";
    for (int i = 0; i < circle.length; i++) {
        os << circle.arr[i];
        if (i != circle.length - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
