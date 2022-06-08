#include <iostream> // needed for: allowing output to be printed to terminal
#include <string> // needed for: our graph is dealing with a lot of strings
#include <vector> // needed for: all of the vectors that our graph holds
#include <queue> // needed for: creating a string queue in our markov chain
#include <algorithm> // needed for: make_heap so we can sort our adjList vector
#include <time.h> // needed for: clock() to seed random numbers and to test execution time
#include <cstdlib> // needed for: random numbers
#include <map> // unused currently
#include <iomanip> // needed for: printing the probabilities nicely
// #include <functional> // needed for: bit_xor in hash_func


// ------------------------------------------------------------------------------------------

#include "WordGraphClass.hpp"

#include "WordVertexStruct.hpp"
#include "AuthorStruct.hpp"
#include "HashTable.hpp"
#include "FileToString.hpp"
#include "TextTools.hpp"

// ------------------------------------------------------------------------------------------

////////////////////
/* PUBLIC METHODS */
////////////////////

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR/DESTRUCTOR FUNCTIONS ////////////////////////////////////////////

WordGraph::WordGraph(std::string fileName) {
  int wordCount = 0;
  setFileContents(fileName);
  wordCount = fileContents.size() / 10;
  wordVertexTable = HashTable(wordCount);
  numWordVertices = 0;
  author = new Author();
  srand(clock());
}

WordGraph::~WordGraph() {
  // TODO
}

////////////////////////////////////////////////////////////////////////////////
// NECESSARY FOR THE CREATION OF THE GRAPH /////////////////////////////////////

void WordGraph::createGraph() {
  // clock_t t1, t2, t3, t4;
  // float d1, d2;

  // t1 = clock();
  createGraphVertices();
  // t2 = clock();

  // t3 = clock();
  createGraphEdges();
  // t4 = clock();


  // d1 = ((float)t2 - (float)t1);
  // d2 = ((float)t4 - (float)t3);

  // std::cout << "Time taken to create vertices: " << d1 / CLOCKS_PER_SEC << std::endl;
  // std::cout << "Time taken to create edges: " << d2 / CLOCKS_PER_SEC << std::endl;


}

// ------------------------------------------------------------------------------------------

/////////////////////
/* PRIVATE METHODS */
/////////////////////

////////////////////////////////////////////////////////////////////////////////
// MARKOV CHAIN FUNCTIONS //////////////////////////////////////////////////////

std::string WordGraph::create1stOrderSentence() {
  // the "random" sentence length
  int sentenceLength = getRandomSentenceLength();

  // std::cout << "sen len: " << sentenceLength << std::endl;

  // initializes the vector for the string
  std::vector<std::string> strVector;

  // gets the first word as a string
  std::string startingWord = pickStartWord();

  // WordVertex of the 'startingWord'
  WordVertex* temp = wordVertexTable.searchTable(startingWord);


  if (temp == nullptr) { return ""; } // if the starting word doesn't exist, return an empty string

  else { // else we can do stuff with the startingWord
    std::string capitalizedWord = capitalizeWord(startingWord);
    strVector.push_back(capitalizedWord);
  } // end else

  WordVertex* lastTemp;

  bool lastWordBad = false;

  while ((strVector.size() < sentenceLength) || ((lastTemp->sentenceEndCount < 2) || (lastWordBad == true))) {
    lastWordBad = false;

    WordVertex* nextWord;

    nextWord = get1stOrderWord(temp);

    std::string  nextWordString = nextWord->Word;

    if (nextWordString == "i") {
      nextWordString = capitalizeWord(nextWordString);
    }

    strVector.push_back(nextWordString);

    temp = nextWord;

    if (strVector.size() >= sentenceLength) {
      lastTemp = temp;
      if (lastTemp->Word == "and" || lastTemp->Word == "or" || lastTemp->Word == "the") {
        lastWordBad = true;
      }
    }
  }

  int lastIndex = strVector.size() - 1;

  strVector[lastIndex] = addPuncuation(strVector[lastIndex], ".");


  std::string finalStr = "";
  for (auto each : strVector) {
    std::string newEach = each + " ";
    finalStr += newEach;
  }

  return finalStr;
}

WordVertex* WordGraph::get1stOrderWord(WordVertex* temp) {
  WordVertex* nextWord;

  std::vector<WordVertex *> wordVertices;

  double maxWordProb = 0;

  for (auto each : temp->adjacencyList[0]) {
    if (maxWordProb <= each->probability) {
      maxWordProb = each->probability;
      wordVertices.push_back(each->word);
    }
  }
  int randIndex = rand() % wordVertices.size();

  return wordVertices[randIndex];
}

std::string WordGraph::createSentence(int markovOrder) {
  // the "random" sentence length
  int sentenceLength = getRandomSentenceLength();
  std::cout << "This sentence's avg length will be: " << sentenceLength << std::endl;

  // initializes the vector for the string
  std::vector<std::string> strVector;

  // initializes the queue
  std::queue<WordVertex *> wordVertexQueue;

  // gets the first word as a string
  std::string startingWord = pickStartWord();

  // WordVertex of the 'startingWord'
  WordVertex* temp = wordVertexTable.searchTable(startingWord);

  if (temp == nullptr) { return ""; } // if the starting word doesn't exist, return an empty string

  else { // else we can do stuff with the startingWord
    std::string capitalizedWord = capitalizeWord(startingWord);
    strVector.push_back(capitalizedWord);
  } // end else

  int wordCounter = 1;
  int maxAdjListIndex = markovOrder - 1;

  wordVertexQueue.push(temp);

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // okay, so this line sucks, gotta figure out a way to make sense of this...                                      //
  std::vector<std::vector<WordEdge *> > adjLists = std::vector<std::vector<WordEdge *> > (                           //
  /*                                |                                 vector of size: */  markovOrder,              //
  /*                                |           initially: vector of WordEdge vectors */  std::vector<WordEdge *>() //
  /*                                |                                                 */ );                         //
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  adjLists = getAdjLists(wordVertexQueue, markovOrder);

  bool lastWordBad = false;

  WordVertex* lastTemp;

  while ((wordCounter <= sentenceLength) || (lastTemp->sentenceEndCount < 2) || (lastWordBad == true)) {
    // pick a word given
    std::string nextWord = getNextWord(adjLists, markovOrder, wordVertexQueue.size());

    temp = wordVertexTable.searchTable(nextWord);
    if (temp == nullptr) {
      nextWord = "I";
    }

    if (nextWord == "i") {
      nextWord = capitalizeWord(nextWord);
    }

    strVector.push_back(nextWord);

    if (wordVertexQueue.size() < markovOrder) {
      wordVertexQueue.push(temp);
    }
    else {
      wordVertexQueue.pop();
      wordVertexQueue.push(temp);
    }

    adjLists = getAdjLists(wordVertexQueue, markovOrder);

    wordCounter++;

    if (strVector.size() >= sentenceLength) {
      lastTemp = temp;
      if (lastTemp->Word == "and" || lastTemp->Word == "or" || lastTemp->Word == "the") {
        lastWordBad = true;
      }
    }
  }

  int lastIndex = strVector.size() - 1;

  strVector[lastIndex] = addPuncuation(strVector[lastIndex], ".");


  std::string finalStr = "";
  for (auto each : strVector) {
    std::string newEach = each + " ";
    finalStr += newEach;
  }

  return finalStr;
}

std::vector<std::vector<WordEdge *> > WordGraph::getAdjLists(std::queue<WordVertex *> wordQueue, int markovOrder) {
  std::vector<std::vector<WordEdge *> > tempAdjList = std::vector<std::vector<WordEdge *> >(markovOrder, std::vector<WordEdge *>());

  if (wordQueue.size() == markovOrder) {
    int counter = markovOrder - 1;
    int i = 0;

    while (!(wordQueue.empty())) {
      WordVertex* temp = wordQueue.front();
      for (auto * each: temp->adjacencyList[counter]) {
        tempAdjList[counter].push_back(each);
      }

      counter--;
      i++;

      wordQueue.pop();
    }
  }
  else {
    int queueSize = wordQueue.size() - 1;

    int i = 0;

    while (!(wordQueue.empty())) {
      WordVertex* temp = wordQueue.front();

      for (auto * each: temp->adjacencyList[i]) {
        tempAdjList[queueSize].push_back(each);
      }

      queueSize--;
      i++;

      wordQueue.pop();
    }
  }
  int i = 1;
  for (auto eachVec : tempAdjList) {
    std::cout << i << std::endl;
    for (auto * eachEdge : eachVec) {
      std::cout << eachEdge->word->Word << " - " << eachEdge->pathCount << std::endl;
    }
    i++;
  }


  return tempAdjList;
}

std::string WordGraph::getNextWord(std::vector<std::vector<WordEdge *> > adjList, int markovOrder, int queueSize) {
  std::map<std::string, double> probabilityMap;
  int lastIndex = markovOrder - 1;


  if (queueSize != markovOrder) {
    int i = 0;
    for (int i = 0; i < queueSize; i++) {
      for (auto eachEdge : adjList[i]) {
        if (i == 0) {
          probabilityMap[eachEdge->word->Word] = eachEdge->probability;
        }
        else {
          probabilityMap[eachEdge->word->Word] *= eachEdge->probability;
        }
        i++;
      }
    }
  }
  else {
    int i = 0;
    for (auto eachBucket : adjList) {
      for (auto * eachEdge : eachBucket) {
        if (i == 0) {
          probabilityMap[eachEdge->word->Word] = eachEdge->probability;
        }
        else {
          probabilityMap[eachEdge->word->Word] *= eachEdge->probability;
        }
        i++;
      }
    }
  }
  double maxProbability = 0.00;

  std::vector<std::string> strVector;
  // std::cout << "---------------" << std::endl;

  for (auto each : probabilityMap) {
    // std::cout << each.first << " - " << std::fixed << std::setprecision(5) << each.second <<std::endl;
    if (each.second >= maxProbability) {
      if (each.second == 0) {
        continue;
      }
      strVector.push_back(each.first);
    }
  }

  int vecSize = strVector.size();
  if (vecSize == 0) {
    return "";
  }
  int randIndex = rand() % vecSize;

  return strVector[randIndex];

}


std::string WordGraph::pickStartWord() {
  // stores the size of the startWord vector
  int startWordSize = startWordVertices.size();

  // stores the random index to access the random startWord
  int randNum = rand() % startWordSize;

  // return the start word at the given index
  return startWordVertices[randNum];
}

double WordGraph::getEdgeProbability(std::string inAdjListOf, std::string wordToGet, int vecIndex) {
  WordVertex* ofTemp = wordVertexTable.searchTable(inAdjListOf);
  WordVertex* checkTemp = wordVertexTable.searchTable(wordToGet);

  if (ofTemp == nullptr || checkTemp == nullptr) { // at least one word was not found in table
    return 0.0;
  } // end if
  else {
    if (!(ofTemp->adjacencyList[vecIndex].empty())) {
      for (auto each : ofTemp->adjacencyList[vecIndex]) {
        if (each->word->Word == wordToGet) {
          return each->probability;
        } // end if
      } // end for
      return 0.0; // not found in adj List
    } // end if
    else {
      return 0.0; // not found in adj List
    } // end else
  } // end else
}

int WordGraph::getRandomSentenceLength() {
  // avg sentence length provided by the author object
  int sentenceLength = this->author->avgSentenceLength;

  // the range is 40% of the avg sentence length
  int range = (0.4) * this->author->avgSentenceLength;

  // multiply range by 2 and add 1 to get encapsulate what we need random numbers for
  int actualRange = (2 * range) + 1;

  // gets the random number in the range [0,actualRange] (inclusive)
  int randNum = rand() % actualRange;

  // gets the number in the range [range,range] (inclusive)
  int fixedNum = range - randNum;

  // adds the fixedNum to the average for a pseudo-avg sentence length
  sentenceLength += fixedNum;

  // returns the new avg sentence length
  return sentenceLength;
}


////////////////////////////////////////////////////////////////////////////////
// VERTEX FUNCTIONS ////////////////////////////////////////////////////////////

void WordGraph::createGraphVertices() {
  // variable declaration

  // char array of the puncuation we are counting
  char punc[] = ".!?";

  // int that holds onto the number of sentences used by the author
  int sentenceCounter = 0;


  int wordEndCounter = 0;
  bool sentenceEnd = false;

  // ints that hold the actual counts of each of our puncuation
  int perCounter = 0; int excCounter = 0; int queCounter = 0;

  for (auto word : fileContents) { // for each word in the file


    if (!(puncInString(word))) { // if there is no puncuation in the word
      if (!(wordVertexTable.isInTable(word))) { // if the word is not in the table
        addWord(word);
      } // end if
    } // end if
    else { // else there is puncuation in the word
      sentenceCounter++;

      // increments period, exclamation point, and question mark counts
      perCounter += countChar(word, '.');
      excCounter += countChar(word, '!');
      queCounter += countChar(word, '?');

      // now we can strip the word of its puncuation
      word = replacePuncuation(word);

      if (!(wordVertexTable.isInTable(word))) { // if the word is not in the table already
        addWord(word); // we'll add the word
      } // end if

      // we're in the else statement that encapsulates words with puncuation
      wordVertexTable.incrementEndCount(word); // increment the word's end count
      sentenceEnd = true; // the sentenceEnd bool is set to true because we have found the end to a sentence

    } // end else

    if (wordEndCounter == 0) { // if the word counter is equal to 0, we know we have found a start word
      wordVertexTable.incrementStartCount(word); // increment that word's start count
    } // end if

    // increments the counter that keeps track of how many words were at in our sentence
    wordEndCounter++;

    if (sentenceEnd) { // if sentenceEnd is true, we need to reset some variables
      wordEndCounter = 0; // back to 0
      sentenceEnd = false; // back to false
    } // end if

    // increment total count (everytime)
    wordVertexTable.incrementCount(word);

  }

  ///////////////////////////
  // sets the word vectors //
  // of the graph object   //
  setWordVertices();       //
  setStartWordVertices();  //
  //                       //
  ///////////////////////////

  ////////////////////////////////////////////////////////////////////
  // sets the number of word vertices for the graph object          //
  this->numWordVertices = wordVertexTable.getTotalNumUniqueWords(); //
  ////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////
  // sets the author object for the graph object                  //
  //                                                              //
  // sets the punctuation counts of the author                    //
  this->author->numPeriods = perCounter;                          //
  this->author->numExclPoints = excCounter;                       //
  this->author->numQuestMarks = queCounter;                       //
  //                                                              //
  // gets the avg. sentence length for later                      //
  int avgSentenceLength = fileContents.size() / sentenceCounter;  //
  //                                                              //
  // sets the total word count and sentence count of the author   //
  this->author->totalWordCount = fileContents.size();             //
  this->author->totalSentenceCount = sentenceCounter;             //
  //                                                              //
  // sets the avg. sentence length of the author                  //
  this->author->avgSentenceLength = avgSentenceLength;            //
  //                                                              //
  //////////////////////////////////////////////////////////////////

}

void WordGraph::addWord(std::string word) {
  // we just add the word here; we handle problematic cases in createGraphVertices()
  wordVertexTable.addWord(word);
}

////////////////////////////////////////////////////////////////////////////////
// EDGE FUNCTIONS //////////////////////////////////////////////////////////////

void WordGraph::createGraphEdges() {
  int vecSize = fileContents.size();
  // std::cout << "vecSize = "<< vecSize << std::endl;
  int current_I = 0;


  while (current_I < vecSize) {
    // std::cout << fileContents[current_I] << std::endl;
    int counter = 0;
    int adjListIndex = 0;
    int wordIndex = current_I + 1;
    while (counter < MAX_ADJ_VEC_SIZE) {
      std::string currentWord = fileContents[current_I];
      // std::cout << "currentWord = " << currentWord << std::endl;
      std::string wordToAdd = fileContents[wordIndex];
      // std::cout << "wordToAdd = " << wordToAdd << std::endl;
      if (puncInString(currentWord)) {
        currentWord = replacePuncuation(currentWord);
        // std::cout << "currentWord = " << currentWord << std::endl;
      }
      if (puncInString(wordToAdd)) {
        wordToAdd = replacePuncuation(wordToAdd);
        // std::cout << "wordToAdd = " << wordToAdd << std::endl;
      }
      // std::cout << "wordToAdd = " << wordToAdd << std::endl;
      addEdge(currentWord, wordToAdd, adjListIndex);
      counter++;
      adjListIndex++;
      wordIndex++;
    }
    current_I++;
  }
  setEdgeProbabilities();
  heapifyAdjLists();
}

void WordGraph::addEdge(std::string currentWord, std::string wordToAdd, int vecIndex) {
  WordVertex* currentTemp = wordVertexTable.searchTable(currentWord); // search the table for the word in which we want to update the adjacencyList
  WordVertex* addTemp = wordVertexTable.searchTable(wordToAdd); // search the table for the word in which we want to add to the specific adjacencyList

  if (currentTemp == nullptr || addTemp == nullptr) { // if either word is not found in the table, just return
    return; // return
  } // end if
  else { // else, we found both of the words

    if (!(isInAdjList(currentWord,wordToAdd, vecIndex))) { // if the word is not in the specified adjacencyList
      // dynamically create a new Edge
      WordEdge *newEdge = new WordEdge(addTemp);

      // push_back the new edge to the correct spot
      currentTemp->adjacencyList[vecIndex].push_back(newEdge);

      // increment the number of edges of the specified Word Vertex
      incrementNumEdges(currentWord, vecIndex);

      // increment the total sum of edges of the specified Word Vertex
      incrementTotalSumEdges(currentWord, vecIndex);
    } // end if
    else { // the word is in the adjacencyList
      // increments the total path count if the word IS found in the adjacencyList
      incrementPathCount(currentWord, wordToAdd, vecIndex);

      // increment the total sum of edges of the specified Word Vertex
      incrementTotalSumEdges(currentWord, vecIndex);
    } // end else
  } // end else
}

void WordGraph::heapifyAdjLists() {
  for (auto each : wordVertices) {
    WordVertex* temp = wordVertexTable.searchTable(each);
    if (temp != nullptr) { // indicates that the temp WordVertex is not a nullptr
      for (int i = 0; i < MAX_ADJ_VEC_SIZE; i++) {
        if (!(temp->adjacencyList[i].empty())) {
          std::make_heap(temp->adjacencyList[i].begin(), temp->adjacencyList[i].end(), MakeHeap_Comp());
        }
      }
    }
  }
}

bool WordGraph::isInAdjList(std::string currentWord, std::string wordToAdd, int vecIndex) {
  WordVertex* currentTemp = wordVertexTable.searchTable(currentWord);
  WordVertex* addTemp = wordVertexTable.searchTable(wordToAdd);

  if (currentTemp == nullptr || addTemp == nullptr) {
    return false;
  }

  if (currentTemp->adjacencyList[vecIndex].empty()) {
    return false;
  }
  else {
    for (auto each : currentTemp->adjacencyList[vecIndex]) {
      if (each->word->Word == wordToAdd) {
        return true;
      }
    }
    return false;
  }
}

void WordGraph::incrementPathCount(std::string currentWord, std::string wordToAdd, int vecIndex) {
  WordVertex* currentTemp = wordVertexTable.searchTable(currentWord);
  WordVertex* addTemp = wordVertexTable.searchTable(wordToAdd);

  if (currentTemp == nullptr || addTemp == nullptr) {
    return;
  }
  else {
    if (!(currentTemp->adjacencyList[vecIndex].empty())) {
      for (auto each : currentTemp->adjacencyList[vecIndex]) {
        if (each->word->Word == wordToAdd) {
          each->pathCount += 1;
        }
      }
    }
  }
}

void WordGraph::incrementNumEdges(std::string currentWord, int vecIndex) {
  WordVertex* currentTemp = wordVertexTable.searchTable(currentWord);

  if (currentTemp == nullptr) {
    return;
  }
  else {
    currentTemp->totalNumEdges[vecIndex] += 1;
  }
}

void WordGraph::incrementTotalSumEdges(std::string currentWord, int vecIndex) {
  WordVertex* currentTemp = wordVertexTable.searchTable(currentWord);

  if (currentTemp == nullptr) {
    return;
  }
  else {
    currentTemp->totalSumEdgePaths[vecIndex] += 1;
  }
}

void WordGraph::setEdgeProbabilities() {
  // iterating through the word vertices
  for (auto each : wordVertices) {
    WordVertex* temp = wordVertexTable.searchTable(each);
    if (temp != nullptr) { // indicates that the temp WordVertex is not a nullptr
      for (int i = 0; i < MAX_ADJ_VEC_SIZE; i++) {
        if (!(temp->adjacencyList[i].empty())) {
          for (auto each : temp->adjacencyList[i]) {
            each->probability = (double)each->pathCount / (double)temp->totalSumEdgePaths[i];
          }
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
// PRINT FUNCTIONS /////////////////////////////////////////////////////////////

void WordGraph::printVertices() {
  wordVertexTable.printTableContents();
}

void WordGraph::printVertex(std::string word) {
  WordVertex* temp = wordVertexTable.searchTable(word);
  if (temp != nullptr) {
    std::cout << *temp << std::endl;
  }
  else {
    std::cout << "Word not present in the table!" << std::endl;
  }
}

void WordGraph::printVerticesFromVector() {
  int i = 1;
  for (auto each : wordVertices) {
    std::cout << i << ". " << each << std::endl;
    i++;
  }
}

void WordGraph::printStartWords() {
  int i = 1;
  for (auto each : startWordVertices) {
    std::cout << i << ". " << each << std::endl;
    i++;
  }
}

void WordGraph::printFileContents() {
  for (auto each : fileContents) {
    std::cout << each << " ";
  }
  std::cout << std::endl;
}

void WordGraph::printAuthor() {
  std::cout << *(this->author) << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
// MISCELLANEOUS FUNCTIONS /////////////////////////////////////////////////////

void WordGraph::setWordVertices() {
  this->wordVertices = wordVertexTable.vectorizeHashTable();
}

void WordGraph::setStartWordVertices() {
  for (auto each : this->wordVertices) {
    WordVertex* temp = wordVertexTable.searchTable(each);
    if (temp != nullptr) {
      if (temp->sentenceStartCount > 0) {
        startWordVertices.push_back(each);
      }
    }
  }
}

void WordGraph::setFileContents(std::string fileName) {
  std::vector<std::string> contents;
  contents = fileToString(fileName);
  this->fileContents = contents;
}

// ------------------------------------------------------------------------------------------
