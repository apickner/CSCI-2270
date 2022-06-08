#include "HW4-Todo-QueueLinkedList.hpp"
#include <iostream>
#include <cstddef>

// public methods
TodoQueueLinkedList::TodoQueueLinkedList() {
  queueFront = queueEnd = NULL;
}

TodoQueueLinkedList::~TodoQueueLinkedList() {
  TodoItem *iterator = queueFront;
  while (iterator != NULL) {
    TodoItem *temp = iterator->next;
    delete iterator;
    iterator = temp;
  }
}

void TodoQueueLinkedList::enqueue(std::string todoItem) {
  if (isEmpty()) {
    TodoItem *newTodoItem = new TodoItem;
    newTodoItem->todo = todoItem;
    newTodoItem->next = NULL;
    queueFront = queueEnd = newTodoItem;
  }
  else {
    TodoItem *newTodoItem = new TodoItem;
    newTodoItem->todo = todoItem;
    newTodoItem->next = NULL;
    queueEnd->next = newTodoItem;
    queueEnd = newTodoItem;
  }
}

void TodoQueueLinkedList::dequeue() {
  if (isEmpty()) {
    std::cout<<"Queue empty, cannot dequeue an item"<<std::endl;
    return;
  }
  else {
    TodoItem *temp = queueFront->next;
    delete queueFront;
    queueFront = temp;
  }
}

TodoItem* TodoQueueLinkedList::peek() {
  if (isEmpty()) {
    std::cout<<"Queue empty, cannot peek"<<std::endl;
    return nullptr;
  }
  return queueFront;
}

TodoItem* TodoQueueLinkedList::getQueueFront() {
  if (isEmpty()) {
    return nullptr;
  }
  return queueFront;
}

TodoItem* TodoQueueLinkedList::getQueueEnd() {
  if (isEmpty()) {
    return nullptr;
  }
  return queueEnd;
}

// private methods
bool TodoQueueLinkedList::isEmpty() {
  return (queueFront == NULL);
}
