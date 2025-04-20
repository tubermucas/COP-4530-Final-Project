#include <iostream>
#include "Graph.hpp"

void printPath(const std::vector<std::string>& path) {
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i];
        if (i < path.size() - 1) std::cout << " -> ";
    }
    std::cout << "\n";
}

struct EdgeStruct {
    std::string from, to;
    unsigned long weight;
};

int main() {
    Graph g;

    // --- Graph 1 ---
    std::vector<std::string> vertices1 = { "1", "2", "3", "4", "5", "6" };
    std::vector<EdgeStruct> edges1 = {
        {"1", "2", 7}, {"1", "3", 9}, {"1", "6", 14}, {"2", "3", 10},
        {"2", "4", 15}, {"3", "4", 11}, {"3", "6", 2}, {"4", "5", 6}, {"5", "6", 9}
    };

    for (const auto& v : vertices1) g.addVertex(v);
    for (const auto& e : edges1) g.addEdge(e.from, e.to, e.weight);

    std::vector<std::string> path1;
    unsigned long cost1 = g.shortestPath("1", "5", path1);
    std::cout << "[Graph 1] Cost from 1 to 5: " << cost1 << "\n";
    std::cout << "[Graph 1] Path: "; printPath(path1);

    std::cout << "\nGraph 1 adjacency list:\n";
    g.printGraph();

    // --- Graph 2 ---
    Graph g2;

    std::vector<std::string> vertices2 = { "BSN", "LIB", "ENB", "MSC", "CAS", "SUB", "SUN" };

    std::vector<EdgeStruct> edges2 = {
        {"BSN", "LIB", 871}, {"BSN", "CAS", 1672}, {"BSN", "MSC", 2355}, {"SUN", "SUB", 1265},
        {"LIB", "MSC", 1615}, {"LIB", "SUN", 1847}, {"ENB", "SUN", 2885},
        {"ENB", "CAS", 454}, {"ENB", "LIB", 1078}
    };

    for (const auto& v : vertices2) g2.addVertex(v);
    for (const auto& e : edges2) g2.addEdge(e.from, e.to, e.weight);

    std::vector<std::string> path2;
    unsigned long cost2 = g2.shortestPath("ENB", "SUN", path2);
    std::cout << "\n[Graph 2] Cost from ENB to SUN: " << cost2 << "\n";
    std::cout << "[Graph 2] Path: "; printPath(path2);

    std::vector<std::string> path3;
    unsigned long cost3 = g2.shortestPath("LIB", "CAS", path3);
    std::cout << "\n[Graph 2] Cost from LIB to CAS: " << cost3 << "\n";
    std::cout << "[Graph 2] Path: "; printPath(path3);

    std::cout << "\nGraph 2 adjacency list:\n";
    g2.printGraph();

    return 0;
}
