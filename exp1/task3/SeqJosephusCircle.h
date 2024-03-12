#ifndef EXP1TASK3_SEQJOSEPHUSCIRCLE_H
#define EXP1TASK3_SEQJOSEPHUSCIRCLE_H

#include <iostream>

class SeqJosephusCircle {
    friend std::ostream &operator<<(std::ostream &os, const SeqJosephusCircle &circle);
public:
    SeqJosephusCircle(int n, int s, int m);
    ~SeqJosephusCircle();
    int remaining() const;
    int out();
private:
    int *arr;
    int length;
    int start;
    const int step;
};

#endif //EXP1TASK3_SEQJOSEPHUSCIRCLE_H
