#ifndef EXP4TASK2_DIJKSTRA_H
#define EXP4TASK2_DIJKSTRA_H

#include <cstddef>
#include <iostream>

#include "LinkedStack.h"
#include "MatrixGraph.h"

template<typename T>
void Dijkstra(const MatrixGraph<T> &graph, size_t v) {
    size_t n = graph.vertex_count();
    auto *distance = new int[n];
    auto *path = new size_t[n];
    auto *selected = new bool[n];

    for (size_t i = 0; i < n; i++) {
        distance[i] = graph.get_edge(v, i);
        selected[i] = i == v;
        if (graph.get_edge(v, i) < MatrixGraph<T>::UNCONNECTED) {
            path[i] = v;
        } else {
            path[i] = -1;
        }
    }

    for (size_t i = 0; i < n - 1; i++) {
        int min = MatrixGraph<T>::UNCONNECTED;
        size_t u = v;
        for (size_t j = 0; j < n; j++) {
            if (!selected[j] && distance[j] < min) {
                min = distance[j];
                u = j;
            }
        }
        if (u == v) {
            // no more connected vertex
            break;
        }
        selected[u] = true;
        for (size_t j = 0; j < n; j++) {
            if (!selected[j] && graph.get_edge(u, j) < MatrixGraph<T>::UNCONNECTED && distance[u] + graph.get_edge(u, j) < distance[j]) {
                distance[j] = distance[u] + graph.get_edge(u, j);
                path[j] = u;
            }
        }
    }

    // output paths
    for (size_t i = 0; i < n; i++) {
        if (i == v) {
            continue;
        }
        if (distance[i] == MatrixGraph<T>::UNCONNECTED) {
            std::cout << "No path" << std::endl;
            continue;
        }
        LinkedStack<size_t> pathStack;
        size_t p = i;
        while (p != v) {
            pathStack.push(p);
            p = path[p];
        }
        std::cout << graph.get_vertex(v);
        while (!pathStack.is_empty()) {
            std::cout << " -> " << graph.get_vertex(pathStack.get_top());
            pathStack.pop();
        }
        std::cout << ", distance = " << distance[i] << std::endl;
    }

    delete[] selected;
    delete[] path;
    delete[] distance;
}

#endif //EXP4TASK2_DIJKSTRA_H
