#include"HashTable.hpp"

/*
Inserts an item in the hash table.
Use the hash function on the key to get the slot.
Insert the key in that slot of hash table.
*/
void Hash::insertItem(int key)
{
     // TODO
     int index = hashFunc(key);
     hashTable[index].push_back(key);
}

/*
Given a key, search if the key exists in the hash table.
*/
void Hash::searchItem(int key)
{
     //Compute the index by using the hash function
     int index = hashFunc(key);
    //Search the list at that specific index, write print statements to justify if you did/didn't find the key

    bool found = false;

    // TODO
    for (auto i : hashTable[index])
    {
      if (key == i) {
        cout<<key<<"  found in the hash table"<<endl;
        found = true;
      }
    }

    if(!found)
    {
      cout<<key<<"  not found in the hash table"<<endl;
    }
}

// main program
int main()
{
  // array that contains keys to be mapped
  int a[] = {15, 11, 27, 8, 12, 7, 18};
  int n = 7;

  // Creates a hash table of size 7
  Hash h(7);

  // insert the keys into the hash table
  // Contents of the hash table are
  //////////////////////////////////////
  // 0 --> 7
  // 1 --> 15 --> 8
  // 2
  // 3
  // 4 --> 11 --> 18
  // 5 --> 12
  // 6 --> 27
  for (int i = 0; i < n; i++)
    h.insertItem(a[i]);

  // search the hash table for 8 and then 10
  // 8 is there, 10 is not there
  h.searchItem(8);
  h.searchItem(10);

  cout<<endl<<endl;

  cout<<"Contents of the hash table are"<<endl;
  // display the Hash table
  h.displayHash();

  return 0;
}
