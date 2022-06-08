#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

#include "Graph.hpp"

using namespace std;

void readFile(string fileName, Graph &graphObject);

int main(int argc, char const *argv[]) {

  if (argc < 2) {
    cout << "Need more command line arguments than that!"<<endl;
  }

  Graph G1;

  readFile(argv[1], G1);

  G1.assignDistricts();

  G1.displayEdges();

  G1.printDFS();

  //////////////////////////////////////////////////////////////////////////////
  return 0;
}

void readFile(string fileName, Graph &graphObject) {
  ifstream ifs(fileName);

  vector<string> names;

  // strings that will hold important info from the
  string firstLine, line, token, state1;

  // getting the first line to add the vertices
  getline(ifs, firstLine);

  // splitting the first line into a string stream
  stringstream iss(firstLine);

  // trashing 'cities' that appears at the beginning of the first line
  getline(iss, token, ',');

  // getting all of the cities of the first line
  while (getline(iss, token, ',')) {
    graphObject.addVertex(token);
    names.push_back(token);
  }


  int namesSize = names.size();
  while (getline(ifs, line)) {
    stringstream iss2(line);
    getline(iss2, state1, ',');
    for (int i = 0; i < namesSize; i++) {
      getline(iss2, token, ',');
      int distance = stoi(token);
      if (distance > 0) {
        cout<<" ... Reading in "<<state1<<" -- "<<names[i]<<" -- "<<distance<<endl;
        graphObject.addEdge(state1, names[i], distance);
      }
    }
  }

}
