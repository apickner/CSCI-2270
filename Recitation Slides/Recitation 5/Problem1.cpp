#include <iostream>

#include "LinkedListClass.hpp"
#include "node.hpp"

using namespace std;
// ========================================
int main(int argc, char const *argv[]) {

  int n = 5;

  LinkedList list1;

  for (int i = 1; i < n; i++) {
    list1.insertAtTail(i+1);
  }

  list1.printList();















  return 0;
}
