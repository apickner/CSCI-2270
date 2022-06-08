#include <iostream>

#include "PriorityQueue.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int parentIndex(int); // returns the index of a a given indices parent

int leftChildIndex(int); // returns the index of a a given indices left child

int rightChildIndex(int); // returns the index of a a given indices right child

void swapPatients(PatientNode&, PatientNode&); // swaps two references of Patient Nodes (pointers basically are references...)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// class methods

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// constructor
PriorityQueue::PriorityQueue(int queueSize) {
  priorityQueue = new PatientNode[queueSize+1];
  maxQueueSize = queueSize;
  currentQueueSize = 0;

  // dummy value at index 0
  PatientNode *newPatient = new PatientNode;
  priorityQueue[0] = *newPatient;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// destructor
PriorityQueue::~PriorityQueue() {
  delete [] priorityQueue;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// enqueue()
/* Uses these methods internally:
isFull()
repairUpward()
*/
// purpose: Adds a PatientNode to the PriorityQueue, and fixes the PriorityQueue if needed.
void PriorityQueue::enqueue (std::string _name, int _injurySeverity, int _treatmentTime) {

  if (isFull()) {

    std::cout << "Priority Queue full. Send remaining patients to another hopsital.\n";

  }
  else {
    currentQueueSize++;

    PatientNode *newPatient = new PatientNode;

    newPatient->name = _name;
    newPatient->injurySeverity = _injurySeverity;
    newPatient->treatmentTime = _treatmentTime;

    priorityQueue[currentQueueSize] = *newPatient;

    if (currentQueueSize > 1) {

      repairUpward(currentQueueSize);
      ///////////////////////////
    }

  }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// dequeue()
/* Uses these methods internally:
isEmpty()
repairDownward()
*/
// purpose: Removes a PatientNode from the PriorityQueue, and fixes the PriorityQueue if needed.
void PriorityQueue::dequeue() {
  if (isEmpty()) {
    std::cout << "Queue Empty.\n";
  }
  else {
    /////////////////
    // extract max //
    swapPatients(priorityQueue[1], priorityQueue[currentQueueSize]);
    /////////////////

    ///////////////////////////
    currentQueueSize--;
    ///////////////////////////
    // repair priority queue //
    repairDownward(1);
    ///////////////////////////
  }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// peekName()
/* Uses these methods internally:
isEmpty()
*/
// purpose: Peeks at the name attribute of the PatientNode at the front of the PriorityQueue
std::string PriorityQueue::peekName() {
  if (isEmpty()) {
    std::cout << "Queue Empty.\n";
    return "";
  }
  else {
    return priorityQueue[1].name;
  }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// peekInjurySeverity()
/* Uses these methods internally:
isEmpty()
*/
// purpose: Peeks at the injurySeverity attribute of the PatientNode at the front of the PriorityQueue
int PriorityQueue::peekInjurySeverity() {
  if (isEmpty()) {
    std::cout << "Queue Empty." << '\n';
    return 999999;
  }
  else {
    return priorityQueue[1].injurySeverity;
  }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// peekTreatmentTime()
/* Uses these methods internally:
isEmpty()
*/
// purpose: Peeks at the treatmentTime attribute of the PatientNode at the front of the PriorityQueue
int PriorityQueue::peekTreatmentTime() {
  if (isEmpty()) {
    std::cout << "Queue Empty." << '\n';
    return 999999;
  }
  else {
    return priorityQueue[1].treatmentTime;
  }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// isFull()
// purpose: returns "T" if the PriorityQueue has reached its limit, returns "F" otherwise
bool PriorityQueue::isFull() {
  return currentQueueSize == maxQueueSize ? true : false;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// isEmpty()
// purpose: returns "T" if the PriorityQueue is empty, returns "F" otherwise
bool PriorityQueue::isEmpty() {
  return currentQueueSize == 0 ? true : false;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// repairUpward()
/* Uses these methods internally:
parentIndex()
swapPatients()
repairUpward() ---> recursion
*/
// purpose: repairs the PriorityQueue (Binary Heap) upwards
/* common english:
Checks whether a PatientNode's injurySeverity is less than or equal to its parent's injurySeverity,
because otherwise there is no need for the Queue to be repaired!
If the PatientNode's injurySeverity is less than the parent's injurySeverity,
then we can safely swap the two Nodes and call repairUpward() recursively,
with the index of the parent which is now actually the index of the original PatientNode!
Else If the PatientNode's injurySeverity is equal to the parent's injurySeverity,
then we need the tiebreaker which is treatmentTime, so we compare the PatientNode & parent Node's
treatmentTime; If the PatientNode's time is less than its parent's, then it has won, and we can continue much like
we did above! Otherwise, we have found our spot in the Queue so the function ends!
*/
void PriorityQueue::repairUpward(int nodeIndex) {
  int tempParentIndex = parentIndex(nodeIndex);
  if (priorityQueue[tempParentIndex].injurySeverity < priorityQueue[nodeIndex].injurySeverity && tempParentIndex > 0) {
    swapPatients(priorityQueue[tempParentIndex], priorityQueue[nodeIndex]);
    repairUpward(tempParentIndex);
  }
  else if (priorityQueue[tempParentIndex].injurySeverity == priorityQueue[nodeIndex].injurySeverity && tempParentIndex > 0) {
    if (priorityQueue[tempParentIndex].treatmentTime > priorityQueue[nodeIndex].treatmentTime) {
      swapPatients(priorityQueue[tempParentIndex], priorityQueue[nodeIndex]);
      repairUpward(tempParentIndex);
    }
  }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// repairDownward()
/* Uses these methods internally:
leftChildIndex()
rightChildIndex()
swapPatients()
repairUpward() ---> recursion
*/
// purpose: repairs the PriorityQueue (Binary Heap) in the downward direction
/* common english:

*/
void PriorityQueue::repairDownward(int nodeIndex) {
  int leftIndex = leftChildIndex(nodeIndex);
  int rightIndex = rightChildIndex(nodeIndex);
  int largestIndex = nodeIndex;

  if (leftIndex <= currentQueueSize && priorityQueue[nodeIndex].injurySeverity <= priorityQueue[leftIndex].injurySeverity) {
    if (priorityQueue[nodeIndex].injurySeverity == priorityQueue[leftIndex].injurySeverity) {
      if (priorityQueue[nodeIndex].treatmentTime > priorityQueue[leftIndex].treatmentTime) {
        largestIndex = leftIndex;
      }
      else {
          largestIndex = nodeIndex;
      }
    }
    else {
      largestIndex = leftIndex;
    }
  }
  if (rightIndex <= currentQueueSize && priorityQueue[largestIndex].injurySeverity <= priorityQueue[rightIndex].injurySeverity) {
    if (priorityQueue[largestIndex].injurySeverity == priorityQueue[rightIndex].injurySeverity) {
      if (priorityQueue[largestIndex].treatmentTime > priorityQueue[rightIndex].treatmentTime) {
        largestIndex = rightIndex;
      }
    }
    else {
     largestIndex  = rightIndex;
    }
  }

// ---------------------------------------------------------------- //

  if (largestIndex != nodeIndex) {
    swapPatients(priorityQueue[largestIndex], priorityQueue[nodeIndex]);
    repairDownward(largestIndex);
  }

}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// helper functions

// returns the index of a given indices parent
int parentIndex(int i) { return (i/2); } //  || i / 2 || \\

// returns the index of a given indices leftChild
int leftChildIndex(int i) { return (i*2); } // || i * 2 || \\

// returns the index of a given indices rightChild
int rightChildIndex(int i) { return (i*2)+1; } // || (i * 2) + 1 || \\

// swaps two patient nodes given two patient node pointers
void swapPatients(PatientNode& patient1, PatientNode& patient2) {
  PatientNode temp = patient1;
  patient1 = patient2;
  patient2 = temp;
}
