#include "Graph.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

/*
  class constructor
  Purpose: perform all operations necessary to instantiate a class
  object
  Parameters: none
*/
Graph::Graph() {
}

/*
  class destructor
  Purpose: free all resources that the object has aquired
  Parameters: none
*/
Graph::~Graph() {
}

/*
  Method Name: addEdge
  Purpose: Creates an edge between two vertices (using an adjVertex
  struct)
  Param: v1 - vertex at one end of edge
  Param: v2 - vertex at opposite end of edge
*/
void Graph::addEdge(std::string v1, std::string v2, int distance) {
  // getting the first vertex from v1
  // std::cout << "starting addEdge()" << '\n';

  vertex* vertex1 = findVertex(v1);

  if (vertex1 == nullptr) {
    std::cout << "Could not find the v1 parameter in the set of vertices" << '\n';
    return;
  }

  // getting the second vertex from v2
  vertex* vertex2 = findVertex(v2);
  if (vertex2 == nullptr) {
    std::cout << "Could not find the v2 parameter in the set of vertices" << '\n';
    return;
  }

  // creating the edge for the first vertex with the second vertex
  Edge *edge1 = new Edge;

  edge1->v = vertex2;
  edge1->distance = distance;

  vertex1->Edges.push_back(*edge1);
  // std::cout << "finishing addEdge()" << '\n';

}

/*
  Method Name: addVertex
  Purpose: Creates a vertex
  Param: name - name of the vertex (city name)
*/
void Graph::addVertex(std::string name) {
  // creates the newVertex

  vertex *newVertex = new vertex;

  // sets all the variables for the newVertex
  newVertex->name = name;
  newVertex->visited = false;
  newVertex->district = 0;
  newVertex->Edges = std::vector<Edge>();

  // add the newVertex to the vertices Vector
  vertices.push_back(*newVertex);
}

/*
  Method Name: displayEdges
  Purpose: print all edges in graph (see writeup for format)
  Parameters: none
*/
void Graph::displayEdges() {
  // std::cout << "displayEdges" << '\n';
  std::vector<vertex>::iterator v;
  std::vector<Edge>::iterator e;
  for (v = vertices.begin(); v != vertices.end(); v++) {
    std::cout << v->district << ":" << v->name;
    std::cout << "-->";
    for (e = v->Edges.begin(); e != v->Edges.end(); ++e) {
      std::cout << e->v->name << " (" << e->distance <<" miles)";
      std::vector<Edge>::iterator temp = e + 1;
      if (temp != v->Edges.end()) {
        std::cout << "***";
      }
    }
    std::cout<<"\n";
  }
}

/*
  Method Name: assignDistricts
  Purpose: Iterate through the vertices, perform BFT to find connected
  components, and assign to district
  Parameters: none
*/
void Graph::assignDistricts() {
  std::vector<vertex>::iterator v;
  int distID = 1;
  for (v = vertices.begin(); v != vertices.end(); ++v) {
    if (v->district == 0) {
      BFTraversalLabel(v->name, distID);
      distID++;
    }
  }
  setAllVerticesUnvisited();
}

/*
  Method Name: printDFS
  Purpose: Iterate through the vertices, perform DFS by calling the
  DFTraversal function
  Parameters: none
*/
void Graph::printDFS() {
  setAllVerticesUnvisited();
  for (int i = 0; i < vertices.size(); i++) {
    vertex* v1 = findVertex(vertices[i].name);
    DFTraversal(v1);
  }
}

/*
  Method Name: setAllVerticesUnvisited
  Purpose: Iterate through the vertices, mark them unvisited.
  This function is called prior to calling DFS after BFS
  has been performed so that the nodes can revisited again
  when DFS is called.
  Parameters: None
*/
void Graph::setAllVerticesUnvisited() {

  for (int i = 0; i < vertices.size(); i++) {
    vertices[i].visited = false;
  }
}

/*
  Method Name: findVertex
  Purpose: Find and return the vertex of the specified city
  Param: name - name of the city vertex to be returned
  returns pointer to a vertex
*/
vertex* Graph::findVertex(std::string name) { // works!!!
  // std::vector<vertex>::iterator v;
  for (int i = 0; i < vertices.size(); i++) {
    if (name == vertices[i].name) {
      vertex* foundVertex = &vertices[i];
      return foundVertex;
    }
  }
  return nullptr;
}

/*
  Method Name: BFTraversalLabel
  Purpose: Call BFTraversalLabel from within assignDistricts to label
  the districts. This method should implement a breadth first
  traversal from the startingCity and assign all cities
  encountered the distID value
  Param: name - name of starting city for breadth first traversal
*/
void Graph::BFTraversalLabel(std::string startingCity, int distID) {

  // find the vertex we want to start with
  vertex* v = findVertex(startingCity);

  // initialize a queue for BFS
  std::queue<vertex *> queue;

  v->visited = true;

  queue.push(v);

  while (!queue.empty()) {
    v = queue.front();
    v->district = distID;
    queue.pop();
    for (auto each : v->Edges) {
      vertex* temp = findVertex(each.v->name);
      if (temp->visited == false ) {
        queue.push(temp);
        temp->visited = true;
      }
    }
  }
}

void Graph::DFTraversal(vertex *v) {
  if (!v->visited) {
    std::cout << v->name << '\n';

  }
  v->visited = true;

  for (int i = 0; i < v->Edges.size(); i++) {
    bool visited = v->Edges[i].v->visited;
    vertex* v2 = findVertex(v->Edges[i].v->name);
    if (!visited) {
      DFTraversal(v2);
    }
  }
}
