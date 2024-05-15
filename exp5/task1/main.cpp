#include <iostream>
#include <numeric>

#include "BinarySearch.h"

int main() {
    int arr[100];
    std::iota(arr, arr + 100, 0);

    BinarySearch<int> bs(arr, 100);
    for (const int key : {33, 52}) {
        std::cout << "try to find " << key << " recursively" << std::endl;
        const size_t i = bs.recursive(key);
        if (i != BinarySearch<int>::NOT_FOUND) {
            std::cout << "found at " << i << std::endl;
        } else {
            std::cout << "not found" << std::endl;
        }
        std::cout << std::endl;

        std::cout << "try to find " << key << " non-recursively" << std::endl;
        const size_t j = bs.non_recursive(key);
        if (j != BinarySearch<int>::NOT_FOUND) {
            std::cout << "found at " << j << std::endl;
        } else {
            std::cout << "not found" << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
