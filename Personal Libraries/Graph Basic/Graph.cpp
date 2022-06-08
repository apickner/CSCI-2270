#include "Graph.hpp"
#include <list>
#include <queue>
#include <iostream>

Graph::Graph(int V) {
  this->V = V;
  adj = new std::list<int>[V];
}

Graph::~Graph() {
  // delete adj;
}

void Graph::addEdge(int v, int e) {
  adj[v].push_back(e);
}

void Graph::BFS(int v) {
    // initialize the visted array to false
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++) {
      visited[i] = false;
    }

    std::list<int> queue;

    visited[v] = true;
    queue.push_back(v);

    std::list<int>::iterator i;

    while (!(queue.empty())) {
      v = queue.front();
      std::cout << v << " ";
      queue.pop_front();

      for (i = adj[v].begin(); i != adj[v].end(); ++i) {
        if (!(visited[*i])) {
          visited[*i] = true;
          queue.push_back(*i);
        }
      }
    }
}

void Graph::DFS(int v) {
  // initialize the visted array to false
  bool *visited = new bool[V];
  for (int i = 0; i < V; i++) {
    visited[i] = false;
  }

  DFSUtility(v, visited);
}

void Graph::DFSUtility(int v, bool visited[]) {
  visited[v] = true;
  std::cout << v << " ";

  std::list<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); i++) {
    if (!(visited[*i])) {
      DFSUtility(*i, visited);
    }
  }
}


// int Graph::mostIncoming() {
//
// }

int Graph::mostOutgoing() {
  std::list<int>::iterator li;
  int max = -1;
  for (int i = 0; i < V; i++) {
    int counter = 0;
    for (li = adj[i].begin(); li != adj[i].end(); ++i) {
      counter++;
    }
    if (counter >= max) {
      max = counter;
    }
  }
  return max;
}
