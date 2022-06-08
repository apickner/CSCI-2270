// headers
#include <iostream>
#include <string>
#include <fstream>

// namespace
using namespace std;

// function declarations
// ============================================
struct wordItem {
	string word;
	int count;
};

// Assignment required functions
void getStopWords(char *ignoreWordsFileName, string ignoreWords[]);

bool isStopWord(string word, string ignoreWords[]);

int getTotalNumberNonStopWords(wordItem list[], int length);

void arraySort(wordItem list[], int length);

void printTopN(wordItem wordItemList[], int topN);

// ============================================
// functions I wrote
void resize(wordItem **arrayPtr, int *capacity, int &allocationCounter);

bool isInArray(string word, int length, wordItem list[]);

void countIncrementer(string word, int length, wordItem list[]);

// ============================================
// main
int main(int argc, char * argv[]) {
	// if our program is not supplied the correct # of arguments, let the user know and exit
	if(argc < 4) {
		cout<<"You need more arguments!"<<endl;
		return -1;
	}

	// command line args
	int n = stoi(argv[1]);
	char* hungerGamesFile = argv[2];
	char* ignoreWordsFile = argv[3];

	// tracking the dynamic-array
	int capacity = 100;
	int numEntries = 0;
	int allocationCounter = 0;

	// word arrays
	// #1 for the dynamic wordItem array
	// #2 for the list of words to ignore
	wordItem *list= new wordItem[capacity];;
	string ignoreWords[50];

	// reading the words to be ignored from a file, and populating an array with the words
	getStopWords(ignoreWordsFile, ignoreWords);

	// open the text to be analyzed with an input file stream
	ifstream ifs(hungerGamesFile);
	string word;
	bool stopWord;
	bool inArray;

	if (ifs.is_open()) {

		while (ifs >> word) {

			stopWord = isStopWord(word, ignoreWords);

			if (!stopWord) {

				inArray = isInArray(word, numEntries, list);

				if (!inArray) {
					if(numEntries == capacity) {
						resize(&list, &capacity, allocationCounter);
					}
					list[numEntries].word = word;
					list[numEntries].count = 1;
					numEntries++;
				}
				else {
					countIncrementer(word, numEntries, list);
				}
			}

		}

		ifs.close();
	}


	// final data manipulation and calculations
	int totalNumberNonStopWords = getTotalNumberNonStopWords(list, numEntries);
	arraySort(list, numEntries);

	// print statements
	printTopN(list, n);
	cout<<"#"<<endl
		<<"Array doubled: "<<allocationCounter<<endl;
	cout<<"#"<<endl
		<<"Unique non-common words: "<<numEntries<<endl;
	cout<<"#"<<endl
		<<"Total non-common words: "<<totalNumberNonStopWords<<endl;

	return 0;
}
// ===================================================================


// ===================================================================
// function definitions
void getStopWords(char *ignoreWordsFileName, string ignoreWords[]) {
	ifstream ifs(ignoreWordsFileName);

	string stopWord;

	for (int i = 0; i < 50; i++) {

		getline(ifs, stopWord);

		ignoreWords[i] = stopWord;
	}
}

bool isStopWord(string word, string ignoreWords[]) {
	for (int i = 0; i < 50; i++) {

		if (word == ignoreWords[i]) {

			return true;
		}
	}

	return false;
}

int getTotalNumberNonStopWords(wordItem list[], int length) {
	int totalNumberNonStopWords = 0;

	for (int i = 0; i < length; i++) {

		totalNumberNonStopWords += list[i].count;
	}

	return totalNumberNonStopWords;
}

void arraySort(wordItem list[], int length) {
	for (int i = 1; i < length; i++) {

		int lastPos = i - 1;

		int currentPos = i;

		while (lastPos >= 0 && list[lastPos].count <= list[currentPos].count) {

			wordItem current = list[currentPos];

			list[currentPos] = list[lastPos];

			list[lastPos] = current;

			lastPos--;

			currentPos--;
		}
	}
}

void printTopN(wordItem wordItemList[], int topN) {
	for (int i = 0; i < topN; i++) {

		cout<<wordItemList[i].count<<" - "<<wordItemList[i].word<<endl;
	}
}

void resize(wordItem **arrayPtr, int *capacity, int &allocationCounter) {
	// Implement the resizing logic here
	int size = *capacity; // saving for the for-loop
	*capacity *= 2; // doubling the cap

	wordItem* newPtr = new wordItem[*capacity];

	for (int i = 0; i < size; i++) {
		newPtr[i] = (*arrayPtr)[i];
	}

	delete[] *arrayPtr;

	*arrayPtr = newPtr;

	allocationCounter++;// incrementing the allocation counter each time the function is called
}


bool isInArray(string word, int length, wordItem list[]) {
	for (int i = 0; i < length; i++) {
		if (word == list[i].word) {
			return true;
		}
	}
	return false;
}

void countIncrementer(string word, int length, wordItem list[]) {
	for (int i = 0; i < length; i++) {
		if (word == list[i].word) {
			list[i].count++;
			break;
		}
	}
}

// ===================================================================
