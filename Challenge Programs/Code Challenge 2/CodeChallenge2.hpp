#ifndef STACK_WITH_QUEUES
#define STACK_WITH_QUEUES

#include <iostream>
#include <stack>
#include <queue>

using namespace std;

class QueueStack {
public:
  QueueStack();
  ~QueueStack();
  int get_size();
  int get_top();
  void push(int);
  void pop();

private:
  bool is_empty();

  queue<int> mainQueue;
  queue<int> holdingQueue;

  int size;
};

#endif
