#ifndef EXP1TASK3_LINKEDJOSEPHUSCIRCLE_H
#define EXP1TASK3_LINKEDJOSEPHUSCIRCLE_H

#include <iostream>

class LinkedJosephusCircle {
    friend std::ostream &operator<<(std::ostream &os, const LinkedJosephusCircle &circle);
public:
    struct Node {
        int data;
        Node *next;
    };

    LinkedJosephusCircle(int n, int s, int m);
    ~LinkedJosephusCircle();
    int remaining() const;
    int out();
private:
    Node *head;
    int length;
    int start;
    const int step;
};

#endif //EXP1TASK3_LINKEDJOSEPHUSCIRCLE_H
