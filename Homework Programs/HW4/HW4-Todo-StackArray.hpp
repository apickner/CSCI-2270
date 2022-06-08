#ifndef HW4_TODO_STACKARRAY
#define HW4_TODO_STACKARRAY

#include "TodoItemArrayStruct.hpp"
#include <string>

const int MAX_STACK_SIZE = 5;

class TodoStackArray
{
public:
  TodoStackArray();

  void push(std::string todoItem);
  void pop();
  TodoItem peek();
  int getStackTop() { return stackTop; }
  TodoItem* getStack() {return stack; }
private:
  int stackTop; //the index in stack[] that will be popped next
  TodoItem stack[MAX_STACK_SIZE];

  bool isEmpty();
  bool isFull();
};

#endif
