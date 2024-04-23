#ifndef EXP4TASK2_PRIM_H
#define EXP4TASK2_PRIM_H

#include <cstddef>
#include <iostream>

#include "MatrixGraph.h"

template<typename T>
void Prim(const MatrixGraph<T> &graph, size_t v) {
    const size_t n = graph.vertex_count();
    size_t k;
    auto *lowCost = new int[n];
    auto *closest = new size_t[n];

    for (size_t i = 0; i < n; i++) {
        lowCost[i] = graph.get_edge(v, i);
        closest[i] = v;
    }

    for (size_t i = 1; i < n; i++) {
        int min = MatrixGraph<T>::UNCONNECTED;
        for (size_t j = 0; j < n; j++) {
            if (lowCost[j] != 0 && lowCost[j] < min) {
                min = lowCost[j];
                k = j;
            }
        }
        std::cout << "边 (" << graph.get_vertex(closest[k]) << ", " << graph.get_vertex(k) << ") 权值: " << min << '\n';
        lowCost[k] = 0;

        for (size_t j = 0; j < n; j++) {
            if (lowCost[j] != 0 && graph.get_edge(k, j) < lowCost[j]) {
                lowCost[j] = graph.get_edge(k, j);
                closest[j] = k;
            }
        }
    }

    delete[] lowCost;
    delete[] closest;
}

#endif //EXP4TASK2_PRIM_H
