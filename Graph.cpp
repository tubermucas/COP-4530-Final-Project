#include "Graph.hpp"
#include "PriorityQueue.hpp"


// Destructor implementation
Graph::~Graph() {
    vertices.clear();
    adjList.clear();
}

// getName function, takes index as an argument and returns the name of the vertex at that index
std::string Graph::getName(const int index) const {
  if (vertices[index] == "EMPTY") {
    std::cout << "ERROR!" << std::endl;
    return "ERROR INDEX DOESN\'T MATCH!";
  }
  return vertices[index];
}

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
void Graph::addVertex(std::string label) {
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
    /*vertices.erase(vertices.begin() + index);*/
    vertices[index] = "EMPTY"; // needed to not mess up the indexing when removing vertices
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

// printGraph function, prints the graph in a readable format for testing purposes
void Graph:: printGraph() const {
    for (int i = 0; i < vertices.size(); ++i) {
        std::cout << vertices[i] << ": ";
        for (const auto& neighbor : adjList[i]) {
            std::cout << "(" << vertices[neighbor.first] << ", " << neighbor.second << ") ";
        }
        std::cout << "\n";
    }
}

// indexes should be unique for "dist" and "parent" arrays to work
// getIndex can be implemented by creating an array with size of MAX_VERTEX_NUMBER
// string index_to_name[MAX_VERTEX_NUMBER]
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) {
  // map <string, pair <unsigned long, string> > dist should be created and set to INF
  const unsigned long INF = 1e9; // 1000000000
  unsigned long dist[MAX_VERTEX_NUMBER];
  int parent[MAX_VERTEX_NUMBER];
  PriorityQueue<std::pair<int, int>> pq;

  for (int i = 0; i < MAX_VERTEX_NUMBER; i++) {
    dist[i] = INF;
  }
  int start_i = getIndex(startLabel);
  dist[start_i] = 0;
  parent[start_i] = -1;
  pq.push({dist[start_i], start_i});
  while (!pq.empty()) {
    int cur_index = pq.top().second;
    unsigned long cur_dist = pq.top().first;
    pq.pop();

    for (auto edge : adjList[cur_index]) {
      int next_index = edge.first; // considering that edges will be implemented with parameters {to, weight}
      unsigned long weight = edge.second;
      if (dist[next_index] > cur_dist + weight) {
        dist[next_index] = cur_dist + weight;
        parent[next_index] = cur_index;
        pq.push({dist[next_index], next_index});
      }
    }
  }

  int cur_index = getIndex(endLabel);
  while (cur_index != -1) {
    path.push_back(getName(cur_index));
    cur_index = parent[cur_index];
  }

  int r = path.size() - 1;
  int l = 0;
  while (l < r) {
    std::string temp = path[l];
    path[l++] = path[r];
    path[r--] = temp;
  }

  return dist[getIndex(endLabel)];
}
