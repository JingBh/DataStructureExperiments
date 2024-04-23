#include <iostream>
#include <stdexcept>
#include <string>

#include "LinkedStack.h"
#include "MatrixGraph.h"

struct Site {
    std::string name;
    std::string description;
};

void Dijkstra(const MatrixGraph<Site> &graph, size_t v, size_t w) {
    size_t n = graph.vertex_count();
    auto *distance = new int[n];
    auto *path = new size_t[n];
    auto *selected = new bool[n];

    for (size_t i = 0; i < n; i++) {
        distance[i] = graph.get_edge(v, i);
        selected[i] = i == v;
        if (graph.get_edge(v, i) < MatrixGraph<Site>::UNCONNECTED) {
            path[i] = v;
        } else {
            path[i] = -1;
        }
    }

    for (size_t i = 0; i < n - 1; i++) {
        int min = MatrixGraph<Site>::UNCONNECTED;
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
            if (!selected[j] && graph.get_edge(u, j) < MatrixGraph<Site>::UNCONNECTED && distance[u] + graph.get_edge(u, j) < distance[j]) {
                distance[j] = distance[u] + graph.get_edge(u, j);
                path[j] = u;
            }
        }
    }

    // output path
    if (distance[w] == MatrixGraph<Site>::UNCONNECTED) {
        std::cout << "- 路径不存在" << std::endl;
        return;
    }
    LinkedStack<size_t> pathStack;
    size_t p = w;
    while (p != v) {
        pathStack.push(p);
        p = path[p];
    }
    std::cout << "- 路径：[ " << graph.get_vertex(v).name;
    while (!pathStack.is_empty()) {
        std::cout << " -> " << graph.get_vertex(pathStack.get_top()).name;
        pathStack.pop();
    }
    std::cout << " ]，总距离 = " << distance[w] << std::endl;

    delete[] selected;
    delete[] path;
    delete[] distance;
}

int main() {
    MatrixGraph<Site> graph{
        { "礼堂", "于 1986 年落成，内部结构为上下两层，拥有 974 个座席，是学校举行重要会议、科技报告、重大典礼、晚会等活动的主要场所。" },
        { "图书馆", "于 2019 年 9 月启用的图书馆，面积 4 万余平米，座位数 3000 余个，拥有丰富的馆藏资源。"},
        { "北操场", "师生锻炼身体、举行田径运动会的主要场所。" },
        { "南操场", "师生锻炼身体、举行田径运动会的主要场所。" },
        { "月亮湖", "环境优美，师生散步游憩的好去处。" },
        { "小花园", "校园角落景色秀丽的小公园，种植有多种树木花卉。" },
        { "日新广场", "科学楼前一片广阔的广场，是举办升旗仪式的场所。" },
        { "体育馆", "平常作为师生的文体活动中心，曾在 2008 年北京奥运会期间作为羽毛球、艺术体操比赛项目的场馆。" }
    };
    graph.add_edge(0, 1, 4);
    graph.add_edge(0, 2, 1);
    graph.add_edge(1, 2, 4);
    graph.add_edge(1, 3, 5);
    graph.add_edge(1, 6, 5);
    graph.add_edge(2, 3, 2);
    graph.add_edge(3, 4, 5);
    graph.add_edge(3, 7, 3);
    graph.add_edge(4, 5, 2);
    graph.add_edge(4, 7, 2);
    graph.add_edge(6, 7, 3);

    std::cout << "校园景点列表：" << '\n';
    for (size_t i = 0, n = graph.vertex_count(); i < n; i++) {
        std::cout << "- [" << i << "] " << graph.get_vertex(i).name << '\n';
    }

    while (true) {
        std::string input;
        std::cout << "\n输入一个景点编号查询详情；输入两个景点编号查询路径；输入 q 退出：";
        std::getline(std::cin, input);

        try {
            if (input == "q") {
                break;
            }
            if (input.find(' ') == std::string::npos) {
                const size_t i = std::stoul(input);
                const auto &site = graph.get_vertex(i);
                std::cout << "- [" << i << "] " << site.name << '\n'
                    << "  简介：" << site.description << '\n'
                    << "  相邻景点：";
                for (size_t j = 0, n = graph.vertex_count(); j < n; j++) {
                    if (i != j && graph.get_edge(i, j) != MatrixGraph<Site>::UNCONNECTED) {
                        std::cout << '[' << j << "] " << graph.get_vertex(j).name << ' ';
                    }
                }
                std::cout << std::endl;
            } else {
                std::string::size_type pos = input.find(' ');
                const size_t i = std::stoul(input.substr(0, pos));
                const size_t j = std::stoul(input.substr(pos + 1));
                Dijkstra(graph, i, j);
            }
        } catch (std::invalid_argument &) {
            std::cout << "输入无效，请重新输入" << std::endl;
        } catch (std::out_of_range &) {
            std::cout << "编号超出范围，请重新输入" << std::endl;
        }
    }

    return 0;
}
