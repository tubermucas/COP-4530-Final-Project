#include "Graph.hpp"


//additional function for Graph class: get_index. Takes label as an argument and returns index
int Graph:: getIndex(const std:: string& label) const {
   for (int i = 0; i < vertices.size(); i++) {
       //if label matches with the specific element in vertices -> return i
       if (vertices[i] == label) return i;
   }
   //if not found, then it will be added to the end
   return -1;
}


//addVertex function, takes label as an argument and adds a vertex with that label
void Graph:: addVertex(std::string label) {
    //if already exists
    if (getIndex(label) != -1) return;
    //otherwise, pushback label and new pair to the adjList
    vertices.push_back(label);
    adjList.push_back({});
}


//removeVertex function, takes label as an argument and removes the vertex with that label
void Graph:: removeVertex(std::string label) {
    int index = getIndex(label);
    if (index == -1) return;


    //erasing from vertices and adjList
    vertices.erase(vertices.begin() + index);
    adjList.erase(adjList.begin() + index);


    //neighbors is the vector<pair<int, unsigned long>> for each vertex.
    //updating each list to remove links to the deleted vertex
    for (auto& neighbors : adjList) {
        for (int i = 0; i < neighbors.size(); ) {
            if (neighbors[i].first == index) {
                neighbors.erase(neighbors.begin() + i);
            } else {
                if (neighbors[i].first > index) {
                    neighbors[i].first -= 1;
                }
                ++i;
            }
        }
    }
}

// addEdge function, takes two labels and a weight as arguments and adds an edge between them
void Graph:: addEdge(std::string label1, std::string label2, unsigned long weight){

    // Get the indices of the vertices
    int index1 = getIndex(label1);
    int index2 = getIndex(label2);

    // If either vertex does not exist, return
    if (index1 == -1 || index2 == -1) return;

    // Add the edge to the adjacency list
    adjList[index1].push_back({index2, weight});
    adjList[index2].push_back({index1, weight});
}

// removeEdge function, takes two labels as arguments and removes the edge between them
void Graph:: removeEdge(std::string label1, std::string label2){

    // Get the indices of the vertices
    int index1 = getIndex(label1);
    int index2 = getIndex(label2);

    // If either vertex does not exist, return
    if (index1 == -1 || index2 == -1) return;

    // Remove the edge from index1's list
    for (int i = 0; i < adjList[index1].size(); ) {
        if (adjList[index1][i].first == index2) {
            adjList[index1].erase(adjList[index1].begin() + i);
        } else {
            ++i;
        }
    }

    // Remove the edge from index2's list
    for (int i = 0; i < adjList[index2].size(); ) {
        if (adjList[index2][i].first == index1) {
            adjList[index2].erase(adjList[index2].begin() + i);
        } else {
            ++i;
        }
    }
}

