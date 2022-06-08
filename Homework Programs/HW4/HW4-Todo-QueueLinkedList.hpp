#ifndef HW4_TODO_QUEUELINKEDLIST
#define HW4_TODO_QUEUELINKEDLIST

#include <string>
#include "TodoItemLinkedListStruct.hpp"

class TodoQueueLinkedList
{
public:
  TodoQueueLinkedList();
  ~TodoQueueLinkedList();
  void enqueue(std::string todoItem);
  void dequeue();
  TodoItem* peek();
  TodoItem* getQueueFront();
  TodoItem* getQueueEnd();
private:
  TodoItem* queueFront; // the item in the list that will be dequeued next
  TodoItem* queueEnd; // the item in the list that was most recently enqueued

  bool isEmpty();
};

#endif
