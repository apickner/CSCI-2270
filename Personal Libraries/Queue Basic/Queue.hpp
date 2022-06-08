#ifndef QUEUE_H
#define QUEUE_H

#define EMPTY_QUEUE -999999999

#define MAX_SIZE 5

class Queue {

private:
  int A[MAX_SIZE];
  int front, rear; // indices that point to the front and rear of our queue

  // the user doesn't need access to these functions, they are only used in Queue and Enqueue
  bool isEmpty();
  bool isFull();

public:
    // Constructor
    // assuming for an empty queue, front and rear will be -1
    Queue();
    ~Queue();

    bool printQueue();

    bool Enqueue(int);
    bool Dequeue();
    int Front(); // Peek function

    void deleteQueue();
};

#endif
