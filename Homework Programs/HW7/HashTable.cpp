#include <iostream>
#include <fstream>
#include <vector>

#include "HashTable.hpp"

void insertIntoSortedArray(wordItem words[], wordItem word, int size);

template <typename T>
void swap_(T &item1, T &item2);

HashTable::HashTable(int hashTableSize) {
  hashTable = new wordItem*[hashTableSize]();
  this->hashTableSize = hashTableSize;
  numUniqueWords = numCollisions = 0;
}

HashTable::~HashTable() {
  for (int i = 0; i < hashTableSize; i++) {
    delete hashTable[i];
  }
}

void HashTable::getStopWords(char *ignoreWordFileName) {
  std::ifstream ifs(ignoreWordFileName);

  std::string stopWord;

	for (int i = 0; i < STOPWORD_LIST_SIZE; i++) {
    getline(ifs, stopWord);

    vecIgnoreWords[i] = stopWord;
  }
}

bool HashTable::isStopWord(std::string word) {
  for (auto stopWord : vecIgnoreWords) {
    if (word == stopWord) {
        return true;
    }
  }
  return false;
}

bool HashTable::isInTable(std::string word) {
  return (searchTable(word) == nullptr) ? false : true;
}

void HashTable::incrementCount(std::string word) {
    int index = getHash(word);
    wordItem *temp = searchTable(word);
    if (temp != nullptr) {
      temp->count += 1;
    }
}

void HashTable::addWord(std::string word) {
    int hashIndex = getHash(word);
    // std::cout << "index = " << hashIndex << '\n';
    wordItem *newWordItem = new wordItem;

    newWordItem->word = word;
    newWordItem->count = 1;
    newWordItem->next = nullptr;

  // std::cout<<hashTable[hashIndex]<<"\n";

  if (hashTable[hashIndex] == nullptr) {
      // std::cout<<"yup, the spot is empty...\n";
      hashTable[hashIndex] = newWordItem;
      // std::cout<<hashTable[hashIndex]->word<<std::endl;
    }
    else {
        wordItem *temp = hashTable[hashIndex];
        while (temp->next != nullptr) {
          temp = temp->next;
        }
          temp->next = newWordItem;
          this->numCollisions++;
      }
    this->numUniqueWords++;
  }

/* PRIVATE METHODS */
//////////////////
int HashTable::getHash(std::string word) { // DJB2 Hash Func
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

wordItem* HashTable::searchTable(std::string word) {
  int index = getHash(word);

  wordItem *temp = hashTable[index];
  while (temp != nullptr) {
      if (word == temp->word) {
          return temp;
      }
      temp = temp->next;
  }
  return nullptr;
}

int HashTable::getTotalNumberNonStopWords() {
  int total = 0;
  for (int i = 0; i < hashTableSize; i++) {
    if (hashTable[i] != nullptr) {
      wordItem *temp = hashTable[i];
      total += hashTable[i]->count;
      while (temp->next != nullptr) {
        temp = temp->next;
        total += temp->count;
      }
    }
  }
  return total;
}

void HashTable::printTopN(int n) {
  wordItem *words = new wordItem[n]();

  for (int i = 0; i < hashTableSize; i++) {
    if (hashTable[i] != nullptr) {
      wordItem *temp = hashTable[i];
      insertIntoSortedArray(words, *temp, n);
      while (temp->next != nullptr) {
        temp = temp->next;
        insertIntoSortedArray(words, *temp, n);
      }
    }
  }

  for (int i = 0; i < n; i++) {
    std::cout << words[i].count << " - " << words[i].word << '\n';
  }

  delete [] words;
}

int HashTable::getNumUniqueWords() {
  return this->numUniqueWords;
}

int HashTable::getNumCollisions() {
  return this->numCollisions;
}

void HashTable::printTableContents() {
  for (int i = 0; i < hashTableSize; i++) {
    if (hashTable[i] != nullptr) {
      wordItem *temp = hashTable[i];
      std::cout << temp->word << " : " << temp->count << std::endl;
      while (temp->next != nullptr) {
        temp = temp->next;
        std::cout << temp->word << " : " << temp->count << std::endl;
      }
    }
    else {
      continue;
    }
  }
}

void HashTable::printStopWords() {
  int i = 1;
  for (auto stopWord : vecIgnoreWords) {
    std::cout << i << " " << stopWord << '\n';
    i++;
  }
}

void insertIntoSortedArray(wordItem* words, wordItem word, int size) {
  // std::cout << word.count << '\n';
  int i = 0;
  while (i < size) {
    if (word.count > words[i].count) {
      swap_(word, words[i]);
    }

    i++;
  }

}

template <typename T>
void swap_(T &item1, T &item2) {
  T temp = item1;
  item1 = item2;
  item2 = temp;
}
