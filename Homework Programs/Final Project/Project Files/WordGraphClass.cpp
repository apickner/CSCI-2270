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
  setFileContents(fileName);
  printFileContents();
  std::cout << fileContents.size() << std::endl;
  int wordCount = 0;
  wordCount = fileContents.size() / 5;

  this->wordVertexTable = HashTable(wordCount);
  this->numWordVertices = 0;
  this->author = new Author();

  srand(clock());
}

WordGraph::~WordGraph() {
  // TODO
}

////////////////////////////////////////////////////////////////////////////////
// NECESSARY FOR THE CREATION OF THE GRAPH /////////////////////////////////////

void WordGraph::createGraph() {
  // std::cout << "Adding the Vertices..." << std::endl;
  createGraphVertices();
  // std::cout << "Done Adding Vertices!" << std::endl;

  // std::cout << "Adding the Edges..." << std::endl;
  createGraphEdges();
  // std::cout << "Done Adding Edges!" << std::endl;

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
  // std::cout << "entering createSentence" << std::endl;
  // if ( markovOrder < 2) {
  //   // std::cout << "entering first if, markov is 1 or 0" << std::endl;
  //   return create1stOrderSentence();
  // }
  // std::cout << "after first if, markov order is greater than 1" << std::endl;

  // the "random" sentence length
  int sentenceLength = getRandomSentenceLength();
  // int sentenceLength = this->author->avgMessageLength;
  // int sentenceLength = this->author->avgSentenceLength;
  int avgMessageLength = this->author->avgMessageLength;
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
    strVector.push_back(startingWord);
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

  bool lastWordPunc = false;

  WordVertex* lastTemp;

  while ((lastWordPunc == false) || (lastTemp->sentenceEndCount < 1)) {
    // std::cout << strVector.size() << std::endl;
    // pick a word given
    std::string nextWord = getNextWord(adjLists, markovOrder, wordVertexQueue.size());
    std::cout << nextWord << std::endl;
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
      if (puncInString(nextWord)) {
        lastWordPunc = true;
        break;
      }
    }

    if (strVector.size() > (2 * avgMessageLength)) {
      break;
    }

    std::string lastWord = nextWord;
  }

  int lastIndex = strVector.size() - 1;

  std::string lastWord = strVector[lastIndex];

  if (!(puncInString(lastWord))) {
    strVector[lastIndex] = addPuncuation(lastWord, ".");
  }

  std::string finalStr = createMessage(strVector);

  return finalStr;
}

std::vector<std::vector<WordEdge *> > WordGraph::getAdjLists(std::queue<WordVertex *> wordQueue, int markovOrder) {
  std::vector<std::vector<WordEdge *> > tempAdjList = std::vector<std::vector<WordEdge *> >(markovOrder, std::vector<WordEdge *>());

  if (wordQueue.size() == markovOrder) {
    int counter = markovOrder - 1;
    int i = 0;

    while (!(wordQueue.empty())) {

      WordVertex* temp = wordQueue.front();
      // std::cout << "index = " << i << std::endl
      //           << "Word = " << temp->Word << std::endl
      //           << "counter = " << counter << std::endl;
      for (auto * each: temp->adjacencyList[counter]) {
        tempAdjList[counter].push_back(each);
        // std::cout << each->word->Word << "(" << each->probability << ")" << " -> ";
      }
      // std::cout << "\n";

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
      // std::cout << "index = " << i << std::endl
      //           << "Word = " << temp->Word << std::endl
      //           << "else counter = " << queueSize << std::endl;
      for (auto * each: temp->adjacencyList[queueSize]) {
        tempAdjList[queueSize].push_back(each);
        // std::cout << each->word->Word << "(" << each->probability << ")" << " -> ";
      }
      // std::cout << "\n";

      queueSize--;
      i++;

      wordQueue.pop();
    }
  }

  // std::cout << "\n";

  return tempAdjList;
}

std::string WordGraph::getNextWord(std::vector<std::vector<WordEdge *> > adjList, int markovOrder, int queueSize) {
  std::map<std::string, double> probabilityMap = mapInitializer(adjList, queueSize);

  int lastIndex = queueSize - 1;

  for (int i = lastIndex; i >= 0; i--) {
    // std::cout << "Adj i = " << i << std::endl;
    for (auto * eachEdge : adjList[i]) {
      // std::cout << "\t" << eachEdge->word->Word << std::endl;

      if (i == lastIndex) {
        // std::cout << "setting " << eachEdge->word->Word << "'s" << " probability: " << eachEdge->probability << std::endl;
        // probabilityMap[eachEdge->word->Word] = eachEdge->probability;
        // std::cout << "continuing... " << std::endl;

        continue;
      }
      else {
        // std::cout << "multiplying " << eachEdge->word->Word << "'s" << " probability by: " << eachEdge->probability << std::endl;

        probabilityMap[eachEdge->word->Word] *= eachEdge->probability;

      }
    }
  }

  double maxProbability = 0.00;

  std::vector<std::string> strVector;
  // std::cout << "---------------" << std::endl;
  for (auto each : probabilityMap) {
    // std::cout << each.first << " - " << std::fixed << std::setprecision(5) << each.second <<std::endl;
    if (each.second >= maxProbability) {
      maxProbability = each.second;
      if (each.second == 0) {
        continue;
      }
    }
  }
  for (auto each : probabilityMap) {
    if (each.second >= maxProbability) {
      // std::cout << each.first << " added to maxVector" << std::endl;

      strVector.push_back(each.first);
    }
  }

  int vecSize = strVector.size();
  if (vecSize == 0) {
    return "";
  }
  int randIndex = rand() % vecSize;

  std::cout << "chosen word is " << strVector[randIndex] << std::endl;

  return strVector[randIndex];

}

std::map<std::string, double> WordGraph::mapInitializer(std::vector<std::vector<WordEdge *> > adjList, int queueSize) {
  std::map<std::string, double> probabilityMap;

  std::map<std::string, int> wordMap;

  int numVectorBuckets = adjList.size() - 1;
  int i = 0;

  for (auto eachBucket : adjList) {
    for (auto * eachEdge : eachBucket) {
      wordMap[eachEdge->word->Word] += 1;
    }
  }
  // for (auto each : wordMap) {
  //   std::cout << each.first << " mapped to " << each.second << std::endl;
  // }

  for (auto eachBucket : adjList) {
    for (auto * eachEdge : eachBucket) {
      if (wordMap[eachEdge->word->Word] < queueSize) {
        probabilityMap[eachEdge->word->Word] = 0;
        // std::cout << eachEdge->word->Word << " initializing to 0..." << std::endl;

      }
      else {
        probabilityMap[eachEdge->word->Word] = eachEdge->probability;
        // std::cout << eachEdge->word->Word << " initializing to " << eachEdge->probability << "..." << std::endl;
      }
    }
  }
  int x = 0;
  for (auto each : wordMap) {
    if (each.second < queueSize) {
      continue;
    }
    else {
      x++;
    }
  }
  if (x == 0) {
    for (auto eachBucket : adjList) {
      for (auto * eachEdge : eachBucket) {
        probabilityMap[eachEdge->word->Word] = eachEdge->probability;
      }
    }
  }

  return probabilityMap;
}

std::string WordGraph::pickStartWord() {
  std::vector<std::string> punc = {"-", ",", ".", "!", "?", "..", "...", "....", "*"};

  // stores the size of the startWord vector
  int startWordSize = startWordVertices.size();

  // stores the random index to access the random startWord
  int randNum = rand() % startWordSize;

  std::string startWord = startWordVertices[randNum];

  bool isPunc = true;

  while (isPunc) {
    isPunc = false;
    for (auto each : punc) {
      if (startWord == each) {
        isPunc = true;
        break;
      }
    }

    if (isPunc) {
      randNum = rand() % startWordSize;
      startWord = startWordVertices[randNum];
    }
  }

  // return the start word at the given index
  return startWord;
}

int WordGraph::getRandomSentenceLength() {
  // avg sentence length provided by the author object
  int sentenceLength = this->author->avgSentenceLength;

  // the range is 40% of the avg sentence length
  int range = (0.33) * (this->author->avgSentenceLength);

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

std::string WordGraph::createMessage(std::vector<std::string> strVector) {
  std::string message;
  std::vector<std::string> punc = {",", ".", "!", "?", "..", "...", "....", "*"};
  int i = 0;
  bool puncFound = false;

  for (auto eachWord : strVector) {

    puncFound = false;

    for (auto eachPunc : punc) {
      if (eachPunc == eachWord) {
        puncFound = true;
      }
    }

    if (i == 0) {
      std::string capitalWord = capitalizeWord(eachWord);
      message += capitalWord;
    }

    else if (puncFound) {
      message += eachWord;
    }

    else {
      std::string fixed = " " + eachWord;
      message += fixed;
      puncFound = false;
    }
    i++;
  }
  return message;

}

////////////////////////////////////////////////////////////////////////////////
// VERTEX FUNCTIONS ////////////////////////////////////////////////////////////

void WordGraph::createGraphVertices() {
  // std::cout << "-----" << std::endl;
  // variable declaration
  // char array of the puncuation we are counting
  std::vector<std::string> punc = {".", "!", "?", "..", "...", "....", "*"};
  int puncSize = punc.size();

  // int that holds onto the number of sentences used by the author
  int sentenceCounter = 0;
  int wordCount = fileContents.size();

  int wordEndCounter = 0;
  bool sentenceEnd = false;
  bool newMessage = true;

  int astCounter = -1;

  int i = 1;
  // std::cout << "Entering for each_word loop: " << std::endl;
  for (int index = 0; index < wordCount; index++, i++) { // for each word in the file
    std::string word = fileContents[index];

    // std::cout << "currentWord = " << word << " @ index = " << index << std::endl;

    std::string nextWord = "";
    std::string nextNextWord = "";
    int newI = i + 1;
    if (i < wordCount - 1) {
      nextWord = fileContents[i];
      nextNextWord = fileContents[newI];
    }

    // std::cout << "nextWord = " << nextWord << " @ index = " << i << std::endl;
    // std::cout << "nextNextWord = " << nextNextWord << " @ index = " << newI << std::endl;


    if (word != "*") { // if the current word is not the "*"
    // std::cout << "IF -> current word is NOT the asterisk" << std::endl;

      // std::cout << "word == " << word << std::endl;
      if (!(wordVertexTable.isInTable(word))) {
        // std::cout << "adding word = " << word << std::endl;
        addWord(word);
      }

      // std::cout << "incrementing count word = " << word << std::endl;

      wordVertexTable.incrementCount(word);

      if (newMessage == true) {
        // std::cout << "newMessage = true - > word == " << word << std::endl;
        // std::cout << "incrementing start count word = " << word << std::endl;

        wordVertexTable.incrementStartCount(word);
        newMessage = false;
      }

      if (nextWord != "" && nextWord != "*") { // if the next word is not empty & nextWord is not the "*"

        for (auto each : punc) { // for each elem in punctuation vector

          if (each == nextWord) { // if nextWord contains punctuation

            sentenceEnd = true; // we have found the sentence end

            if (nextNextWord != "" && nextNextWord != "*") { // if the nextNextWord is not empty & nextNextWord is not equal to "*"

              if (!(wordVertexTable.isInTable(nextNextWord))) { // if the word is not in the table yet

                addWord(nextNextWord); // add the word

                // std::cout << "adding nextNextWord = " << nextNextWord << std::endl;

              } // end if

              // std::cout << "incrementing start count nextNextWord = " << nextNextWord << std::endl;
              wordVertexTable.incrementStartCount(nextNextWord); // then increment the start count
            } // end if

          } // end if

          else { // else our word doesn't contain punc

            continue; // continue
          } // end else

        } // end for loop

      } // end if

      if (sentenceEnd == true) { // if we have found the end of the sentence (nextWord is puncuation or "*")
        // std::cout << "incrementing end count word = " << word << std::endl;

        wordVertexTable.incrementEndCount(word);
        sentenceEnd = false;
      } // end if

      sentenceCounter++;

    } // end if
    else { // else our current word is the asterisk "*"
      // std::cout << "IF -> current word is the asterisk" << std::endl;
      astCounter++;
      newMessage = true;

      if (nextWord != "*" && nextWord != "") { // if the nextWord is not the asterisk or empty

        if (!(wordVertexTable.isInTable(nextWord))) {
          addWord(nextWord);

          // std::cout << "adding nextWord = " << nextWord << std::endl;

        }
        // std::cout << "incrementing start count nextWord = " << nextWord << std::endl;
        // wordVertexTable.incrementStartCount(nextWord);
      } // end if
    }

  }
  // std::cout << "-----" << std::endl;

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
  // std::cout << "3" << '\n';

  //////////////////////////////////////////////////////////////////
  // sets the author object for the graph object                  //
  //                                                              //
  // sets the punctuation counts of the author                    //
  WordVertex* period = wordVertexTable.searchTable(".");
  WordVertex* excl = wordVertexTable.searchTable("!");
  WordVertex* quest = wordVertexTable.searchTable("?");
  if (period != nullptr) {
    this->author->numPeriods = period->totalCount;
  }
  else {
    this->author->numPeriods = 0;
  }

  if (excl != nullptr) {
    this->author->numExclPoints = excl->totalCount;
  }
  else {
    this->author->numExclPoints = 0;
  }

  if (quest != nullptr) {
    this->author->numQuestMarks = quest->totalCount;
  }
  else {
    this->author->numQuestMarks = 0;
  }

  int puncCount = this->author->numPeriods + this->author->numQuestMarks + this->author->numExclPoints;

  // gets the avg. sentence length for later
  int avgSentenceLength = wordCount / (puncCount + astCounter + 1);
  this->author->avgSentenceLength = avgSentenceLength;

  // sets the total word count and sentence count of the author
  this->author->totalWordCount = wordCount;
  this->author->totalMessageCount = astCounter;

  this->author->avgMessageLength = wordCount / astCounter;

}

void WordGraph::addWord(std::string word) {
  // we just add the word here; we handle problematic cases in createGraphVertices()
  wordVertexTable.addWord(word);
}

////////////////////////////////////////////////////////////////////////////////
// EDGE FUNCTIONS //////////////////////////////////////////////////////////////

void WordGraph::createGraphEdges() {
  fixFileContents();

  int vecSize = fileContents.size();
  // std::cout << "vecSize = "<< vecSize << std::endl;
  int current_I = 0;


  while (current_I < vecSize) {
    // std::cout << fileContents[current_I] << std::endl;
    int counter = 0;
    int adjListIndex = 0;
    int wordIndex = current_I + 1;

    while (counter < MAX_ADJ_VEC_SIZE) {
      if (wordIndex >= vecSize) {
        break;
      }

      std::string currentWord = fileContents[current_I];

      std::string wordToAdd = fileContents[wordIndex];
      // std::cout << "current word @ index = " << current_I << ": " << currentWord << " -> word to add @ index =  " << wordIndex << ": " << wordToAdd << std::endl;
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
  // std::cout << currentWord << wordToAdd << std::endl;

  if (currentTemp == nullptr || addTemp == nullptr) { return; }

  else { // else, we found both of the words
    // std::cout << currentTemp->Word << addTemp->Word << std::endl;
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

void WordGraph::fixFileContents() {
  std::vector<std::string> tempVec;
  for (auto each : this->fileContents) {
    if (each != "*") {
      tempVec.push_back(each);
    }
  }
  this->fileContents = tempVec;
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
  std::cout << "Unique Vertices" << std::endl;
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
  std::cout << "# word vertices " << this->wordVertices.size() << std::endl;
}

void WordGraph::setStartWordVertices() {
  for (auto each : wordVertices) {
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
