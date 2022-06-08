#include <iostream>
#include <fstream>

using namespace std;

int insertIntoSortedArray(int Array[], int numEntries, int newValue);

// =================================================================================
int main(int argc, char const * argv[]) {
  // I think it's better to initialize the array to zeros rather than leave
  // the default constructor to fill up some values with garbage
  int numArray[100] = { 0 };

  ifstream ifs(argv[1]);

  int numEntries = 0;
  int number;

  while (ifs >> number) {
    // cout<<number<<endl;
    numEntries = insertIntoSortedArray(numArray, numEntries, number);
    for (int i = 0; i < numEntries; i++) {
      if (i != numEntries-1) {
        cout<<numArray[i]<<", ";
      } else {
        cout<<numArray[i];
      }
    }
    cout<<endl;
  }
  return 0;
}
// =================================================================================

int insertIntoSortedArray(int* Array, int numEntries, int newValue) {
  // if Array has more entries than 0
  if (numEntries > 0) {

    // indexCounter will hold the index of the correct position for newValue
    int indexCounter = 0;

    //
    for (int i = 0; indexCounter <= numEntries && i < numEntries; i++) {

      // if our newValue is greater than the value in our Array at i
      if (newValue > Array[i]) {

        // indexCounter increments everytime our newValue is greater than the array value
        indexCounter++;
      }
    }

    // loop through array from the end up to the index we found earlier
    for (int i = numEntries; i > indexCounter; i--) {

      // current spot in array set equal to the previous spot (shifting the array)
      Array[i] = Array[i-1];
    }

    // Put the new value into the array now that we have made room
    Array[indexCounter] = newValue;

  // else the array is empty, so we need to set the first element equal to the newValue
  } else {
    Array[0] = newValue;
  }

  // increment numEntries before we return it
  numEntries++;
  return numEntries;
}
