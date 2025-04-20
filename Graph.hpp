#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.hpp"
#include <vector>
#include <string>
#include <iostream> 

class Graph: public GraphBase{
private:
    int MAX_VERTEX_NUMBER = 1000;
    std::vector<std::string> vertices;
    std::vector<std::vector<std::pair<int, unsigned long>>> adjList;

    int getIndex(const std::string& label) const;
    std::string getName(const int index) const;
    

public:
    ~Graph();
    
    void printGraph() const; // added for testing purposes

    void addVertex(std::string label) override;
    void removeVertex(std::string label) override;
    void addEdge(std::string label1, std::string label2, unsigned long weight) override;
    void removeEdge(std::string label1, std::string label2) override;
    unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string>&path) override;

    
};

#endif
