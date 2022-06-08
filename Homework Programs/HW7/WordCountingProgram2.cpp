#include <iostream>
#include <fstream>
#include <sstream>

#include "HashTable2.hpp"

using namespace std;

int main(int argc, char *argv[]) {

  if (argc != 5) {
    cout<<"There are not enough arguments!\n";
    return 1;
  }
  const int PrintN = stoi(argv[1]);

  char *bookFile = argv[2];
  char *stopWordFile = argv[3];

  int tableSize = stoi(argv[4]);

  HashTable hash1(tableSize);
  hash1.getStopWords(stopWordFile);




  ifstream ifs(bookFile);

  // istringstream iss(ifs);
  string word = "";

	while (ifs >> word) {
    bool inTable = hash1.isInTable(word);
    // cout<<boolalpha<<"in table? "<<inTable<<endl;
    bool stopWord = hash1.isStopWord(word);
    // cout<<boolalpha<<"is stop word? "<<stopWord<<endl;
    if (stopWord) {
      continue;
    }
    else if (!inTable) {
      // cout<<"word being added: "<<word<<endl;

      hash1.addWord(word);
      continue;
    }
    else {
      // cout<<"word being incremented: "<<word<<endl;

      hash1.incrementCount(word);
      continue;

    }
  }

  // hash1.printTableContents();

  hash1.printTopN(PrintN);

  cout<<"#\nNumber of collisions: "<<hash1.getNumCollisions()<<endl;

  cout<<"#\nUnique non-stop words: "<<hash1.getNumUniqueWords()<<endl;

  cout<<"#\nTotal non-stop words: "<<hash1.getTotalNumberNonStopWords()<<endl;



  return 0;
}
