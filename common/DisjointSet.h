#ifndef COMMON_DISJOINTSET_H
#define COMMON_DISJOINTSET_H

#include <cstddef>
#include <numeric>

class DisjointSet {
public:
    DisjointSet() = delete;
    explicit DisjointSet(size_t size);
    ~DisjointSet();
    size_t find(size_t x);
    void unite(size_t x, size_t y);
private:
    size_t *parent;
};

DisjointSet::DisjointSet(size_t size) {
    parent = new size_t[size];
    std::iota(parent, parent + size, 0);
}

DisjointSet::~DisjointSet() {
    delete[] parent;
}

size_t DisjointSet::find(size_t x) {
    return parent[x] == x ? x : parent[x] = find(parent[x]);
}

void DisjointSet::unite(size_t x, size_t y) {
    parent[find(x)] = find(y);
}

#endif //COMMON_DISJOINTSET_H
