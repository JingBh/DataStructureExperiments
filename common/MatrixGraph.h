#ifndef COMMON_MATRIXGRAPH_H
#define COMMON_MATRIXGRAPH_H

#include <algorithm>
#include <functional>
#include <initializer_list>
#include <limits>
#include <stdexcept>

#include "LinkedQueue.h"
#include "LinkedStack.h"

template <typename T>
class MatrixGraph {
public:
    MatrixGraph(const T vertices[], size_t n);
    MatrixGraph(std::initializer_list<T> vertices);
    ~MatrixGraph();
    void add_edge(size_t a, size_t b);
    void add_edge(size_t a, size_t b, int weight);
    int get_edge(size_t a, size_t b) const;
    const T &get_vertex(size_t i) const;
    size_t vertex_count() const;
    size_t edge_count() const;
    void dfs(size_t v, const std::function<void (const T &)> &cb) const;
    void dfs_flat(size_t v, const std::function<void (const T &)> &cb) const;
    void bfs(size_t v, const std::function<void (const T &)> &cb) const;
    constexpr static int UNCONNECTED = std::numeric_limits<int>::max();
private:
    T *vertices;
    int **edges;
    size_t n;
    void dfs(size_t v, bool visited[], const std::function<void (const T &)> &cb) const;
};

template<typename T>
MatrixGraph<T>::MatrixGraph(const T *vertices, size_t n) {
    this->vertices = new T[n];
    std::copy(vertices, vertices + n, this->vertices);
    this->edges = new int*[n];
    for (size_t i = 0; i < n; i++) {
        this->edges[i] = new int[n];
        for (size_t j = 0; j < n; j++) {
            this->edges[i][j] = i == j ? 0 : UNCONNECTED;
        }
    }
    this->n = n;
}

template<typename T>
MatrixGraph<T>::MatrixGraph(std::initializer_list<T> vertices)
    : MatrixGraph(vertices.begin(), vertices.size()) {}

template<typename T>
MatrixGraph<T>::~MatrixGraph() {
    for (size_t i = 0; i < n; i++) {
        delete[] edges[i];
    }
    delete[] edges;
    delete[] vertices;
}

template<typename T>
inline void MatrixGraph<T>::add_edge(size_t a, size_t b) {
    add_edge(a, b, 1);
}

template<typename T>
void MatrixGraph<T>::add_edge(size_t a, size_t b, int weight) {
    if (a == b) {
        // cannot connect self
        return;
    }
    if (a >= n || b >= n) {
        throw std::out_of_range("index out of range");
    }
    // undirected graph
    edges[a][b] = weight;
    edges[b][a] = weight;
}

template<typename T>
int MatrixGraph<T>::get_edge(size_t a, size_t b) const {
    if (a >= n || b >= n) {
        throw std::out_of_range("index out of range");
    }
    return edges[a][b];
}

template<typename T>
inline const T &MatrixGraph<T>::get_vertex(size_t i) const {
    return vertices[i];
}

template<typename T>
inline size_t MatrixGraph<T>::vertex_count() const {
    return n;
}

template<typename T>
size_t MatrixGraph<T>::edge_count() const {
    size_t count = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            if (edges[i][j] != UNCONNECTED) {
                count++;
            }
        }
    }
    return count;
}

template<typename T>
void MatrixGraph<T>::dfs(size_t v, const std::function<void(const T &)> &cb) const {
    bool *visited = new bool[n];
    dfs(v, visited, cb);
    delete[] visited;
}

template<typename T>
void MatrixGraph<T>::dfs(size_t v, bool visited[], const std::function<void(const T &)> &cb) const {
    cb(vertices[v]);
    visited[v] = true;
    for (size_t i = 0; i < n; i++) {
        if (edges[v][i] > 0 && edges[v][i] != UNCONNECTED && !visited[i]) {
            dfs(i, visited, cb);
        }
    }
}

template<typename T>
void MatrixGraph<T>::dfs_flat(size_t v, const std::function<void(const T &)> &cb) const {
    LinkedStack<size_t> stack;
    bool *visited = new bool[n];
    visited[v] = true;
    stack.push(v);
    cb(vertices[v]);
    while (!stack.is_empty()) {
        const size_t top = stack.get_top();
        size_t i = 0;
        for (; i < n; i++) {
            if (edges[top][i] > 0 && edges[top][i] != UNCONNECTED && !visited[i]) {
                visited[i] = true;
                stack.push(i);
                cb(vertices[i]);
                break;
            }
        }
        if (i == n) {
            stack.pop();
        }
    }
    delete[] visited;
}

template<typename T>
void MatrixGraph<T>::bfs(size_t v, const std::function<void(const T &)> &cb) const {
    LinkedQueue<size_t> queue;
    bool *visited = new bool[n];
    cb(vertices[v]);
    visited[v] = true;
    queue.enqueue(v);
    while (!queue.is_empty()) {
        const size_t front = queue.dequeue();
        for (size_t i = 0; i < n; i++) {
            if (edges[front][i] > 0 && edges[front][i] != UNCONNECTED && !visited[i]) {
                cb(vertices[i]);
                visited[i] = true;
                queue.enqueue(i);
            }
        }
    }
    delete[] visited;
}

#endif //COMMON_MATRIXGRAPH_H
