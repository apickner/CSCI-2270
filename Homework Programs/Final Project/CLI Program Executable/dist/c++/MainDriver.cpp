#include <iostream>
// ------------------------------------------------------------------------------------------
#include "ProductionWordGraphClass.hpp"
// ------------------------------------------------------------------------------------------
using namespace std;
// ------------------------------------------------------------------------------------------
int main(int argc, char const *argv[]) {

  std::string fileName = argv[1];

  WordGraph Graph(fileName);

  Graph.createGraph();

  cout << Graph.createSentence(2) << endl;

  return 0;
}
// ------------------------------------------------------------------------------------------
