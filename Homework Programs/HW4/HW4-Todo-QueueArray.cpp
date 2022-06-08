#include "HW4-Todo-QueueArray.hpp"
#include <iostream>

// public methods
TodoQueueArray::TodoQueueArray() {
  queueFront = queueEnd = -1;
}

void TodoQueueArray::enqueue(std::string todoItem) {
  if (isFull()) {
    std::cout<<"Queue full, cannot add new todo item."<<std::endl;
    return;
  }
  else if (isEmpty()) {
    queueFront = queueEnd = 0;
  }
  else {
    queueEnd = (queueEnd+1) % MAX_QUEUE_SIZE;
  }
  TodoItem todoObject;
  todoObject.todo = todoItem;
  queue[queueEnd] = todoObject;
}

void TodoQueueArray::dequeue() {
  if (isEmpty()) {
    std::cout<<"Queue empty, cannot dequeue an item."<<std::endl;
    return;
  }
  else if (getQueueFront() == getQueueEnd()) {
    queueFront = queueEnd = -1;
  }
  else {
    queueFront = (queueFront+1) % MAX_QUEUE_SIZE;
  }
}

TodoItem TodoQueueArray::peek() {
  if (isEmpty()) {
    std::cout<<"Queue empty, cannot peek."<<std::endl;
  }
  return queue[queueFront];
}

// private methods
bool TodoQueueArray::isEmpty() {
  return (queueFront == -1 && queueEnd == -1);
}

bool TodoQueueArray::isFull() {
  return (queueEnd+1) % MAX_QUEUE_SIZE == queueFront ? true : false;
}
