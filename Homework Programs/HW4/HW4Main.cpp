#include <iostream>
#include <string>

#include "HW4-Todo-QueueArray.hpp"
#include "HW4-Todo-StackArray.hpp"
#include "HW4-Todo-QueueLinkedList.hpp"
#include "HW4-Todo-StackLinkedList.hpp"

using namespace std;

int main(int argc, char* const argv[]) {

  // ======================================================================
  TodoQueueArray queue1;

  cout<<"Queues with Arrays --------------------------------->"<<endl
      <<"Adding 6 items..."<<endl;

  queue1.enqueue("queue todo1"); // 1
  queue1.enqueue("queue todo2"); // 2
  queue1.enqueue("queue todo3"); // 3
  queue1.enqueue("queue todo4"); // 4
  queue1.enqueue("queue todo5"); // 5
  queue1.enqueue("queue todo6"); // 6

  cout<<"Checking each front item, then Dequeuing that item..."<<endl;

  cout<<"Peek: "<<queue1.peek().todo<<endl;
  queue1.dequeue(); // 1
  cout<<"Peek: "<<queue1.peek().todo<<endl;
  queue1.dequeue(); // 2
  cout<<"Peek: "<<queue1.peek().todo<<endl;
  queue1.dequeue(); // 3
  cout<<"Peek: "<<queue1.peek().todo<<endl;
  queue1.dequeue(); // 4
  cout<<"Peek: "<<queue1.peek().todo<<endl;
  queue1.dequeue(); // 5
  queue1.peek();
  queue1.dequeue(); // 6
  // ======================================================================
  // ======================================================================
  TodoStackArray stack1;

  cout<<"Stacks with Arrays --------------------------------->"<<endl
      <<"Adding 6 items..."<<endl;
  stack1.push("stack todo1"); // 1
  stack1.push("stack todo2"); // 2
  stack1.push("stack todo3"); // 3
  stack1.push("stack todo4"); // 4
  stack1.push("stack todo5"); // 5
  stack1.push("stack todo6"); // 6

  cout<<"Checking each top item, then Popping that item..."<<endl;
  cout<<"Peek: "<<stack1.peek().todo<<endl;
  stack1.pop(); // 1
  cout<<"Peek: "<<stack1.peek().todo<<endl;
  stack1.pop(); // 2
  cout<<"Peek: "<<stack1.peek().todo<<endl;
  stack1.pop(); // 3
  cout<<"Peek: "<<stack1.peek().todo<<endl;
  stack1.pop(); // 4
  cout<<"Peek: "<<stack1.peek().todo<<endl;
  stack1.pop(); // 5
  stack1.peek();
  stack1.pop(); // 6
  // ======================================================================
  // ======================================================================
  TodoQueueLinkedList queue2;

  cout<<"Queues with Linked Lists --------------------------->"<<endl
      <<"Adding 5 items..."<<endl;
  queue2.enqueue("queue todo1"); // 1
  queue2.enqueue("queue todo2"); // 2
  queue2.enqueue("queue todo3"); // 3
  queue2.enqueue("queue todo4"); // 4
  queue2.enqueue("queue todo5"); // 5

  cout<<"Peek: "<<queue2.peek()->todo<<endl;
  queue2.dequeue(); // 1
  cout<<"Peek: "<<queue2.peek()->todo<<endl;
  queue2.dequeue(); // 2
  cout<<"Peek: "<<queue2.peek()->todo<<endl;
  queue2.dequeue(); // 3
  cout<<"Peek: "<<queue2.peek()->todo<<endl;
  queue2.dequeue(); // 4
  cout<<"Peek: "<<queue2.peek()->todo<<endl;
  queue2.dequeue(); // 5
  queue2.peek();
  queue2.dequeue(); // 6
  // ======================================================================
  // ======================================================================
  TodoStackLinkedList stack2;

  cout<<"Stacks with Linked Lists --------------------------->"<<endl
      <<"Adding 5 items..."<<endl;

  stack2.push("stack todo1"); // 1
  stack2.push("stack todo2"); // 2
  stack2.push("stack todo3"); // 3
  stack2.push("stack todo4"); // 4
  stack2.push("stack todo5"); // 5

  cout<<"Checking each top item, then Popping that item..."<<endl;
  cout<<"Peek: "<<stack2.peek()->todo<<endl;
  stack2.pop(); // 1
  cout<<"Peek: "<<stack2.peek()->todo<<endl;
  stack2.pop(); // 2
  cout<<"Peek: "<<stack2.peek()->todo<<endl;
  stack2.pop(); // 3
  cout<<"Peek: "<<stack2.peek()->todo<<endl;
  stack2.pop(); // 4
  cout<<"Peek: "<<stack2.peek()->todo<<endl;
  stack2.pop(); // 5
  stack2.peek();
  stack2.pop(); // 6




  return 0;
}
