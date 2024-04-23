#ifndef EXP4TASK2_KRUSKAL_H
#define EXP4TASK2_KRUSKAL_H

#include <cstddef>
#include <functional>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

#include "DisjointSet.h"
#include "MatrixGraph.h"

template<typename T>
void Kruskal(const MatrixGraph<T> &graph) {
    const size_t n = graph.vertex_count();
    using edge_t = std::tuple<size_t, size_t, int>;
    std::priority_queue<edge_t, std::vector<edge_t>, std::function<bool (const edge_t &, const edge_t &)>> queue{[](const edge_t &a, const edge_t &b) {
        return std::get<2>(a) > std::get<2>(b);
    }};
    DisjointSet ds{n};

    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            if (graph.get_edge(i, j) != MatrixGraph<T>::UNCONNECTED) {
                queue.push({i, j, graph.get_edge(i, j)});
            }
        }
    }

    while (!queue.empty()) {
        const auto &[i, j, w] = queue.top();
        if (ds.find(i) != ds.find(j)) {
            std::cout << "边 (" << graph.get_vertex(i) << ", " << graph.get_vertex(j) << ") 权值: " << w << '\n';
            ds.unite(i, j);
        }
        queue.pop();
    }
}

#endif //EXP4TASK2_KRUSKAL_H
