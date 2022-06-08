#include "CodeChallenge2.hpp"

using namespace std;



// constructor initializes size to 0
QueueStack::QueueStack() {
 this->size = 0;
}

// destructor empties out the two queues
QueueStack::~QueueStack() {
  for (int i = 0; i < this->mainQueue.size(); i++) {
    this->mainQueue.pop();
  }
  for (int i = 0; i < this->holdingQueue.size(); i++) {
    this->holdingQueue.pop();
  }
}

// returns the size of the virtual stack (the mainQueue)
int QueueStack::get_size() {
  return this->size;
}

// returns the top of the virtual stack (the mainQueue)
int QueueStack::get_top() {
  if (this->mainQueue.empty()) { return -999999; } // if the mainQueue is empty, return -999999 because the stack is empty
  return this->mainQueue.front();
}

// push value onto the stack
void QueueStack::push(int value) {
  this->holdingQueue.push(value);
  while (!mainQueue.empty()) {
    holdingQueue.push(mainQueue.front());
    mainQueue.pop();
  }
  swap(mainQueue, holdingQueue); // queue method that swaps the contents of two queues... perfect for this application
  for (int i = 0; i < holdingQueue.size(); i++) {
    holdingQueue.pop();
  }
  this->size = mainQueue.size();
}

void QueueStack::pop() {
  if (this->mainQueue.empty()) {
    cout<<"Cannot pop, stack is empty!\n";
  }
  else {
    this->mainQueue.pop();
    this->size = mainQueue.size();
  }
}

bool QueueStack::is_empty() {
  return (this->size == 0) ? true : false;
}
