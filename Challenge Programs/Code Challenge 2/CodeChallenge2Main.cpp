#include <iostream>
#include "CodeChallenge2.hpp"

using namespace std;

int main(int argc, char const *argv[]) {

  QueueStack queueStack1;

  cout<<"Adding 1, 2, 3, 4, 5 to the stack (in that order)\n";
  queueStack1.push(1);
  queueStack1.push(2);
  queueStack1.push(3);
  queueStack1.push(4);
  queueStack1.push(5);

  cout<<"Printing the top element of the stack and then popping it\n";
  for (int i = 0; i < 5; i++) {
    cout<<queueStack1.get_top()<<endl;
    queueStack1.pop();
  }


  return 0;
}
