#include <iostream> // needed for: being able to print to the terminal
#include <vector> // needed for: vectorizeTable so we can iterate through the table in our graph
// ------------------------------------------------------------------------------------------
#include "HashTable.hpp"
// ------------------------------------------------------------------------------------------
using namespace std;
// ------------------------------------------------------------------------------------------

////////////////////
/* PUBLIC METHODS */
////////////////////

// Constructor ------------------------------------------------------------------------------
HashTable::HashTable() {
  hashTable = new WordVertex*[0]();
  this->numCollisions = this->numUniqueWords = this->hashTableSize = 0;
}
// Constructor ------------------------------------------------------------------------------
HashTable::HashTable(int hashTableSize) {
  hashTable = new WordVertex*[hashTableSize]();
  this->hashTableSize = hashTableSize;
  this->numCollisions = this->numUniqueWords = 0;
}
// Destructor -------------------------------------------------------------------------------
HashTable::~HashTable() {
  for (int i = 0; i < hashTableSize; i++) {
    delete hashTable[i];
  }
}

// is a word in the table? ------------------------------------------------------------------
bool HashTable::isInTable(std::string word) {
  return (searchTable(word) == nullptr) ? false : true;
}
// adds a word to the table -----------------------------------------------------------------
void HashTable::addWord(std::string word) {
  int hashIndex = hashFunc(word);
  // std::cout << "index = " << hashIndex << '\n';
  WordVertex *newWordVertex = new WordVertex(word);

  // std::cout<<hashTable[hashIndex]<<"\n";

  if (hashTable[hashIndex] == nullptr) {
      // std::cout<<"yup, the spot is empty...\n";
      hashTable[hashIndex] = newWordVertex;
      // std::cout<<hashTable[hashIndex]->word<<std::endl;
    }
    else {
        WordVertex *temp = hashTable[hashIndex];
        while (temp->nextInTable != nullptr) {
          temp = temp->nextInTable;
        }
          temp->nextInTable = newWordVertex;
          this->numCollisions++;
      }
    this->numUniqueWords++;
}
// serach function that returns the Vertex if found, otherwise nullptr ----------------------
WordVertex* HashTable::searchTable(std::string word) {
  int index = hashFunc(word);

  WordVertex *temp = hashTable[index];
  while (temp != nullptr) {
      if (word == temp->Word) {
          return temp;
      }
      temp = temp->nextInTable;
  }
  return nullptr;
}
// specific count incrementer ---------------------------------------------------------------
void HashTable::incrementCount(std::string word) {
    if (isInTable(word)) {
      WordVertex *temp = searchTable(word);
      temp->totalCount += 1;
    }
  }
// specific count incrementer ---------------------------------------------------------------
void HashTable::incrementStartCount(std::string word) {
  if (isInTable(word)) {
    WordVertex *temp = searchTable(word);

    temp->sentenceStartCount += 1;
  }
}
// specific count incrementer ---------------------------------------------------------------
void HashTable::incrementEndCount(std::string word) {
  if (isInTable(word)) {
    WordVertex *temp = searchTable(word);
    temp->sentenceEndCount += 1;
  }
}
// prints the contents of the table  --------------------------------------------------------
void HashTable::printTableContents() {
  for (int i = 0; i < hashTableSize; i++) {
    if (hashTable[i] != nullptr) {
      WordVertex *tempVertex = hashTable[i];
      std::cout << *tempVertex << std::endl;
      while (tempVertex->nextInTable != nullptr) {
        tempVertex = tempVertex->nextInTable;
        std::cout << *tempVertex << std::endl;
      }
    }
    else {
      continue;
    }
  }
}
// ------------------------------------------------------------------------------------------

/////////////////////
/* PRIVATE METHODS */
/////////////////////

int HashTable::hashFunc(std::string word) { // DJB2 Hash Func
  int hash = 5381;
  for (auto c : word) {
    hash = (hash * 33) + c;
  }
  hash = hash % (this->hashTableSize);
  if (hash < 0) {
    hash += (this->hashTableSize);
  }
  return hash;
}
// -------------------------------------------------------------------------------------------
int HashTable::getTotalNumUniqueWords() {
  return numUniqueWords;
}
// -------------------------------------------------------------------------------------------
vector<string> HashTable::vectorizeHashTable() {
  vector<string> tableVector = vector<string>();

  for (int i = 0; i < hashTableSize; i++) {
    if (hashTable[i] != nullptr) {
      WordVertex *temp = hashTable[i];
      tableVector.push_back(temp->Word);
      while (temp->nextInTable != nullptr) {
        temp = temp->nextInTable;
        tableVector.push_back(temp->Word);
      }
    }
  }
  return tableVector;
}
// -------------------------------------------------------------------------------------------
int HashTable::getTotalWordCount() {
  int total = 0;

  for (int i = 0; i < hashTableSize; i++) {
    if (hashTable[i] != nullptr) {
      WordVertex *temp = hashTable[i];
      total += hashTable[i]->totalCount;

      while (temp->nextInTable != nullptr) {
        temp = temp->nextInTable;
        total += temp->totalCount;
      }
    }
  }
  return total;
}
// ------------------------------------------------------------------------------------------
