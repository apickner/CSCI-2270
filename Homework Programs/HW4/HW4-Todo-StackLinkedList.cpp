#include "HW4-Todo-StackLinkedList.hpp"
#include <iostream>

TodoStackLinkedList::TodoStackLinkedList() {
  stackHead = NULL;
}

TodoStackLinkedList::~TodoStackLinkedList() {
  TodoItem *iterator = stackHead;
  while (iterator != NULL) {
    TodoItem *temp = iterator->next;
    delete iterator;
    iterator = temp;
  }
}

bool TodoStackLinkedList::isEmpty() {
  return (stackHead == NULL);
}

void TodoStackLinkedList::push(std::string todoItem) {
  TodoItem *newTodoItem = new TodoItem;
  newTodoItem->todo = todoItem;
  newTodoItem->next = stackHead;
  stackHead = newTodoItem;
}

void TodoStackLinkedList::pop() {
  if (isEmpty()) {
    std::cout<<"Stack empty, cannot pop an item."<<std::endl;
  }
  else {
    TodoItem *newStackHead = stackHead->next;
    delete stackHead;
    stackHead = newStackHead;
  }
}

TodoItem* TodoStackLinkedList::peek() {
  if (isEmpty()) {
    std::cout<<"Stack empty, cannot peek."<<std::endl;
  }
  return stackHead;
}
