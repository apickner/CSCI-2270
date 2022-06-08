#ifndef GRAPH_H
#define GRAPH_H

#include <list>

class Graph {
  public:

    Graph(int); // Constructor

    ~Graph();

    void addEdge(int, int);

    void DFS(int);

    void BFS(int);

    // problem 3 functions

    int mostIncoming();

    int mostOutgoing();

  private:

    int V; // number of vertices

    std::list<int> *adj; // list that holds the edges

    void DFSUtility(int, bool visited[]);

};

#endif
