 /*=================================
Recap of Circular Arrays
MAX_SIZE = 5;
0%5 = 0
1%5 = 1
2%5 = 2
3%5 = 3
4%5 = 4
5%5 = 0
6%5 = 1
===================================*/
#include <iostream>

#include "Queue.hpp"

using namespace std;

// #define EMPTY_QUEUE -999999999
// const int MAX_SIZE = 3;

Queue::Queue() {
  front = rear = -1;
}

Queue::~Queue() {
  deleteQueue();
}

bool Queue::printQueue() {
  if (!isEmpty()) {
    cout<<"<<>><<>><<>><<>><<>>"<<endl
        <<"<< Printing Queue >>"<<endl
        <<"<<>><<>><<>><<>><<>>"<<endl;
    for (int i = front; i <= rear; i++) {
      if (i == rear){
        cout<<A[i]<<endl;
      }
      else {
        cout<<A[i]<<" <- ";
      }
    }
    return true;
  }
  return false;
}

bool Queue::isEmpty() {
  return (front == -1 && rear == -1);
}
bool Queue::isFull() {
  return (rear+1) % MAX_SIZE == front ? true : false;
}

bool Queue::Enqueue(int data) {
  if (isFull()) {
    // cout<<"The Queue is full! Could not Enqueue "<<data<<endl;
    return false;
  }
  else if (isEmpty()) {
    rear = front = 0;
  }
  else {
    rear = (rear+1) % MAX_SIZE;
  }
  A[rear] = data;
  return true;
}

bool Queue::Dequeue() {
  if (isEmpty()) {
    // cout<<"The Queue is empty! Could not Dequeue anything"<<endl;
    return false;
  }
  else if (front == rear) {
    front = rear = -1;
  }
  else {
    front = (front+1) % MAX_SIZE;
  }
  return true;
}

int Queue::Front() {
  if (isEmpty()) {
    return EMPTY_QUEUE;
  }
  return A[front];
}

void Queue::deleteQueue() {
  delete A;
}
//=============================================
void TestSeperator() {
  cout<<endl<<">"<<endl
      <<"# # # # #"<<endl
      <<">"<<endl<<endl;
}
// ============================================
