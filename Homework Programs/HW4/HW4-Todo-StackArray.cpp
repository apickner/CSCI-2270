#include "HW4-Todo-StackArray.hpp"
#include <iostream>

// public methods
TodoStackArray::TodoStackArray() {
  stackTop = - 1;
}

void TodoStackArray::push(std::string todoItem) {
  if (isFull()) {
    std::cout<<"Stack full, cannot add new todo item"<<std::endl;
  }
  else {
    stackTop++;
    TodoItem Todo;
    Todo.todo = todoItem;
    stack[stackTop] = Todo;
  }
}

void TodoStackArray::pop() {
  if (isEmpty()) {
    std::cout<<"Stack empty, cannot pop an item"<<std::endl;
  }
  else {
    stackTop--;
  }
}

TodoItem TodoStackArray::peek() {
  if (isEmpty()) {
    std::cout<<"Stack empty, cannot peek"<<std::endl;
  }
  return stack[stackTop];
}

// private methods
bool TodoStackArray::isEmpty() {
  return stackTop == -1;
}

bool TodoStackArray::isFull() {
  return stackTop < (MAX_STACK_SIZE - 1) ? false : true;
}
