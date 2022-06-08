#ifndef HW_7_HASH_TABLE
#define HW_7_HASH_TABLE

#include <string>
#include <iostream>
#include <vector>

struct wordItem
{
    std::string word;
    int count;
    wordItem* next;

    wordItem() {
      next = nullptr;
    }

    wordItem(std::string word) {
      this->word = word;
      count = 1;
      next = nullptr;
    }
};

const int STOPWORD_LIST_SIZE = 50;

class HashTable{
public:
	HashTable(int hashTableSize); //Complete (untested)
	~HashTable();

	void getStopWords(char *ignoreWordFileName); //Complete (TESTED)
	bool isStopWord(std::string word); //Complete (untested)
	bool isInTable(std::string word);
	void incrementCount(std::string word); //Complete (untested)
	void addWord(std::string word);
	int getTotalNumberNonStopWords();
	void printTopN(int n);
	int getNumUniqueWords();
	int getNumCollisions();

  //print functions i wrote to test on my machine
  void printTableContents();
  void printStopWords();

private:
	int getHash(std::string word); //Complete (TESTED)
	wordItem* searchTable(std::string word); //Complete (untested)

	int numUniqueWords;
	int numCollisions;
	int hashTableSize;
	wordItem** hashTable;

	std::vector<std::string> vecIgnoreWords = std::vector<std::string>(STOPWORD_LIST_SIZE);

};

#endif
