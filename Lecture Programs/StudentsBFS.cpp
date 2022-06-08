
// Program to print BFS traversal from a given
// source vertex. BFS(int s) traverses vertices
// reachable from s.
#include<iostream>
#include <list>

using namespace std;

// This class represents a directed graph using
// adjacency list representation
class Graph
{
    // No. of vertices
    int V;

    // Pointer to an array containing adjacency
    // lists
    list<int> *adj;
public:
    Graph(int V);  // Constructor

    // function to add an edge to graph
    void addEdge(int v, int w);

    // prints BFS traversal from a given source s
    void BFS(int s);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.

    // if we wanted a bidirectional graph or undirected Graph
    // adj[w].push_back(v)
}

void Graph::BFS(int s)
{
  if (s >= V) {
    cout << "'s' is out of bounds" << endl;
    return;
  }

  // Mark all the vertices as not visited
  bool *visited = new bool[V]; // array of size 'V' holding booleans
  for (int i = 0; i < V; i++) {
    visited[i] = false; // setting each index of the boolean array to false
  }

  // initialize a queue for BFS
  list<int> queue;

  // mark the current node as visitied, and enqueue it
  visited[s] = true;
  queue.push_back(s);

  // 'i' will be used to get all adjacent
  // vertices of a vertex
  list<int>::iterator i;


  while (!queue.empty()) {
    // dequeue a vertex from the queue and print it
    s = queue.front();
    cout << s << " ";
    queue.pop_front();


    // get all adjacent vertices of the dequeued vertex 's'
    // if the adjacent node has not been visited, then mark it visited and enqueue it
    for (i = adj[s].begin(); i != adj[s].end(); ++i) {
      if (!visited[*i]) {
        visited[*i] = true;
        queue.push_back(*i);
      }
    }

  }



}

// Driver program to test methods of graph class
int main()
{
    // Create a graph given in the above diagram
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    cout << "Following is Breadth First Traversal "
         << "(starting from vertex 2) \n";
    g.BFS(2);
    cout << endl;
    return 0;
}
