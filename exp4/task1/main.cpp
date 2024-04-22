#include <iostream>

#include "MatrixGraph.h"

void cb(char v) {
    std::cout << v << ' ';
}

int main() {
    MatrixGraph graph{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'z'};
    graph.add_edge(0, 1, 1);
    graph.add_edge(0, 2, 4);
    graph.add_edge(0, 3, 4);
    graph.add_edge(1, 2, 2);
    graph.add_edge(1, 4, 9);
    graph.add_edge(2, 3, 3);
    graph.add_edge(2, 4, 6);
    graph.add_edge(2, 5, 3);
    graph.add_edge(3, 5, 5);
    graph.add_edge(3, 6, 7);
    graph.add_edge(4, 5, 2);
    graph.add_edge(4, 7, 1);
    graph.add_edge(5, 6, 4);
    graph.add_edge(5, 7, 6);
    graph.add_edge(6, 7, 3);

    std::cout << "1. 测试递归 DFS" << '\n';
    graph.dfs(0, cb);
    std::cout << std::endl;

    std::cout << "2. 测试非递归 DFS" << '\n';
    graph.dfs_flat(0, cb);
    std::cout << std::endl;

    std::cout << "3. 测试 BFS" << '\n';
    graph.bfs(0, cb);
    std::cout << std::endl;

    return 0;
}
