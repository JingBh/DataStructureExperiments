#include <iostream>

#include "LinkedList.h"

template <typename ElemType>
LinkedList<ElemType> merge(const LinkedList<ElemType> &l1, const LinkedList<ElemType> &l2) {
    LinkedList<ElemType> res;
    auto *p1 = l1.get_first();
    auto *p2 = l2.get_first();
    auto *p3 = res.get_first();
    ElemType insert;
    while (p1 != nullptr || p2 != nullptr) {
        if (p1 != nullptr && p2 != nullptr) {
            if (p1->data <= p2->data) {
                insert = p1->data;
                p1 = p1->next;
            } else {
                insert = p2->data;
                p2 = p2->next;
            }
        } else if (p1 != nullptr) {
            insert = p1->data;
            p1 = p1->next;
        } else { // p2 != nullptr
            insert = p2->data;
            p2 = p2->next;
        }
        if (p3 == nullptr) {
            res.prepend(insert);
            p3 = res.get_first();
        } else if (p3->data != insert) {
            p3->next = new typename LinkedList<ElemType>::Node;
            p3 = p3->next;
            p3->data = insert;
        }
    }
    return res;
}

int main() {
    // 创建两个有序数组
    const LinkedList l1 = { 1, 2, 3, 4, 5 };
    const LinkedList l2 = { 1, 3, 5, 7, 9, 10 };
    std::cout << "List 1: " << l1 << std::endl;
    std::cout << "List 2: " << l2 << std::endl;

    const LinkedList merged = merge(l1, l2);
    std::cout << "Merged: " << merged << std::endl;

    return 0;
}
