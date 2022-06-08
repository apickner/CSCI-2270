#include <iostream>
using namespace std;
// ===========================
struct node {
  int data;
  node *next;
  node();
  node(int);
  node(int, node*);
};

node::node() {}

node::node(int d) {
  data = d;
  next = NULL;
}

node::node(int d, node *n) {
  data = d;
  next = n;
}
// ===========================
class LinkedList {

  private:
    node *head;
    node *tail;
    int size = 0;

  public:
    // =====================================
    // Print functions
    void printValAtIndex(int);
    void printList();

    // =====================================
    // Insert functions
    node* insertAtHead(int);
    void insertAtTail(int);
    bool insertAtIndex(int, int);
    void insertAtNode(int, node*);

    // =====================================
    // Delete functions
    bool deleteAtHead();
    bool deleteAtTail();
    // TODO
    bool deleteAtIndex(int);

    // =====================================
    // getter-functions for head, tail, & size
    node* Head() { return this->head; }
    node* Tail() { return this->tail; }
    int Size() { return this->size; }
};

void LinkedList::printValAtIndex(int index) {
  if (index < Size()) {
    node *iterator = Head();
    for (int i = 0; i < index; i++) {
      iterator = iterator->next;
    }
    cout<<iterator->data<<" @ index: "<<index<<endl;
  }
  else {
    cout<<"Index out of range... (It should be 1 smaller than the size!)"<<endl;
  }
}

void LinkedList::printList() {
  node *iterator = Head();
  while (iterator != NULL) {
    cout<<iterator->data<<" -> ";
    iterator = (iterator)->next;
  }
  cout<<"NULL"<<endl;
}

void LinkedList::insertAtHead(int data) {
  node *newHead = new node(data, Head());
  this->head = newHead;
  (this->size)++;
  if (this->size == 1) {
    this->tail = Head();
  }
}

void LinkedList::insertAtTail(int data) {
  node *newTail = new node(data);
  this->tail->next = newTail;
  this->tail = newTail;
  this->size++;
  if (this->size == 1) {
    this->head = Tail();
  }
}

bool LinkedList::insertAtIndex(int data, int index) {
  if (index == 0) {
    insertAtHead(data);
    return true;
  }
  else if (index > Size()) {
    cout<<"Index out of range... (It should be the same size as the List or smaller!)"<<endl;
    return false;
  } else {
    node *iterator = Head();
    node *nextIterator = Head()->next;
    for (int i = 0; i < (--index); i++) {
      iterator = nextIterator;
      nextIterator = nextIterator->next;
    }
    node *newNode = new node(data, nextIterator);
    iterator->next = newNode;
    (this->size)++;
    return true;
  }
}

void LinkedList::insertAtNode(int data, node *prevNode) {
  node *newNode = new node(data, prevNode->next);
  prevNode->next = newNode;
  (this->size)++;
}

bool LinkedList::deleteAtHead() {
  if (this->size > 0) {
    node *temp = Head()->next;
    delete this->head;
    this->head = temp;
    (this->size)--;
    return true;
  }
  return false;
}

bool LinkedList::deleteAtTail() {
  if (0 < this->size) {
    node *iterator = Head();
    while (iterator->next != Tail()) {
      iterator = iterator->next;
    }
    node *oldTail = iterator->next;
    this->tail = iterator;
    (this->tail)->next = NULL;
    delete oldTail;
    (this->size)--;
    return true;
  }
  return false;
}

// TODO
bool LinkedList::deleteAtIndex(int index) {
  if (index < Size() && index > 0) {
    node *iterator = Head();
    node *nextIterator = Head()->next;
    for (int i = 0; i < (--index); i++) {
      iterator = nextIterator;
      nextIterator = nextIterator->next;
    }
    iterator->next = nextIterator->next;
    delete nextIterator;
    (this->size)--;
    return true;
  }
  else if (index == 0) {
    if (deleteAtHead()) {
      return true;
    }
    return false;
  }
  else {
    return false;
  }
}
// ===========================
void TestSeperator() {
  cout<<endl<<">"<<endl
      <<"# # # # #"<<endl
      <<">"<<endl<<endl;
}
// ===========================
int main(int argc, char const *argv[]) {

  LinkedList list1;

  TestSeperator();
  // Test: insert at HEAD & at TAIL
  cout<<"Inserting 0  @  Head"<<endl;
  list1.insertAtHead(0);
  list1.printList();
  cout << "Size = "<<list1.Size()<<endl;

  cout<<"Inserting 10  @  Tail"<<endl;
  list1.insertAtTail(10);
  list1.printList();
  cout<<"Size = "<<list1.Size()<<endl;

  /*
  Expected 0 --> 10 --> NULL
  */
  cout<<"Expected Output:"<<endl
      <<"0 -> 10 -> NULL"<<endl
      <<"Actual Output:"<<endl;
  list1.printList();
  TestSeperator();

  // Complicated Test: insert at HEAD & at TAIL
  cout<<"For-Loop adding elements to LinkedList object: list1"<<endl;
  for (int i = 1; i <= 5; i++) {
    list1.insertAtTail(i);
    list1.insertAtHead(i);
    cout<<"Size = "<<list1.Size()<<endl;
  }
  /*
  Expected 5 --> 4 --> 3 --> 2 --> 1 --> 0 --> 10 --> 1 --> 2 --> 3 --> 4 --> 5 --> NULL
  */
  cout<<"Expected Output:"<<endl
      <<"5 -> 4 -> 3 -> 2 -> 1 -> 0 -> 10 -> 1 -> 2 -> 3 -> 4 -> 5 -> NULL"<<endl
      <<"Actual Output:"<<endl;
  list1.printList();
  TestSeperator();

  cout<<"Deleting head x3 times..."<<endl;
  if (list1.deleteAtHead()) {
    cout<<"Deleting head..."<<endl;
    cout<<"Size = "<<list1.Size()<<endl;
  }
  if (list1.deleteAtHead()) {
    cout<<"Deleting head..."<<endl;
    cout<<"Size = "<<list1.Size()<<endl;
  }
  if (list1.deleteAtHead()) {
    cout<<"Deleting head..."<<endl;
    cout<<"Size = "<<list1.Size()<<endl;
  }
  /*
  Expected 2 --> 1 --> 0 --> 10 --> 1 --> 2 --> 3 --> 4 --> 5 --> NULL
  */
  cout<<"Expected Output:"<<endl
      <<"2 -> 1 -> 0 -> 10 -> 1 -> 2 -> 3 -> 4 -> 5 -> NULL"<<endl
      <<"Actual Output:"<<endl;
  list1.printList();
  TestSeperator();
  cout<<"Deleting tail x3 times..."<<endl;
  if (list1.deleteAtTail()) {
    cout<<"Deleting tail..."<<endl;
    cout<<"Size = "<<list1.Size()<<endl;
  }
  if (list1.deleteAtTail()) {
    cout<<"Deleting tail..."<<endl;
    cout<<"Size = "<<list1.Size()<<endl;
  }
  if (list1.deleteAtTail()) {
    cout<<"Deleting tail..."<<endl;
    cout<<"Size = "<<list1.Size()<<endl;
  }
  /*
  Expected 2 --> 1 --> 0 --> 10 --> 1 --> 2 --> NULL
  */
  cout<<"Expected Output:"<<endl
      <<"2 -> 1 -> 0 -> 10 -> 1 -> 2 -> NULL"<<endl
      <<"Actual Output:"<<endl;
  list1.printList();
  TestSeperator();

  if (list1.insertAtIndex(123, 0)) {
    cout<<"123 added at index 0"<<endl;
    cout<<"Size = "<<list1.Size()<<endl;
  }
  if (list1.insertAtIndex(456, 1)) {
    cout<<"456 added at index 1"<<endl;
    cout<<"Size = "<<list1.Size()<<endl;
  }
  if (list1.insertAtIndex(789, 2)) {
    cout<<"789 added at index 2"<<endl;
    cout<<"Size = "<<list1.Size()<<endl;
  }
  if (list1.insertAtIndex(123, 10)) {
    cout<<"123 added at index 10"<<endl;
    cout<<"Size = "<<list1.Size()<<endl;
  } else {
    cout<<"123 was NOT added at index 10"<<endl;
    cout<<"Size = "<<list1.Size()<<endl;
  }
  cout<<"Expected Output:"<<endl
      <<"123 -> 456 -> 789 -> 2 -> 1 -> 0 -> 10 -> 1 -> 2 -> NULL"<<endl
      <<"Actual Output:"<<endl;
  list1.printList();
  TestSeperator();

  list1.insertAtNode(5, (list1.Head()->next)->next);
  cout<<"Insert: 5  @  prevNode: 789"<<endl
      <<"Expected Output:"<<endl
      <<"123 -> 456 -> 789 -> 5 -> 2 -> 1 -> 0 -> 5 -> 10 -> 1 -> 2 -> NULL"<<endl
      <<"Actual Output:"<<endl;
  list1.printList();
  cout<<"Size = "<<list1.Size()<<endl;

  list1.insertAtNode(100, list1.Tail());
  cout<<"Insert: 100  @  prevNode: Tail()"<<endl
      <<"Expected Output:"<<endl
      <<"123 -> 456 -> 789 -> 0 -> 2 -> 1 -> 0 -> 10 -> 1 -> 2 -> 100 -> NULL"<<endl
      <<"Actual Output:"<<endl;
  list1.printList();
  cout<<"Size = "<<list1.Size()<<endl;
  TestSeperator();

  cout<<"PrintValAtIndex: 8, 9, 10, 11"<<endl;
  for (int i = 8; i < 12; i++) {
    list1.printValAtIndex(i);
  }
  TestSeperator();

  list1.printList();
  if (list1.deleteAtIndex(0)) {
    cout<<"index: 0 DELETED"<<endl;
    cout<<"Size = "<<list1.Size()<<endl;
  }
  list1.printList();
  if (list1.deleteAtIndex(1)) {
    cout<<"index: 1 DELETED"<<endl;
    cout<<"Size = "<<list1.Size()<<endl;
  }
  list1.printList();
  if (list1.deleteAtIndex(2)) {
    cout<<"index: 2 DELETED"<<endl;
    cout<<"Size = "<<list1.Size()<<endl;
  }
  if (list1.deleteAtIndex(7)) {
    cout<<"index: 7 DELETED"<<endl;
    cout<<"Size = "<<list1.Size()<<endl;
  }
  if (list1.deleteAtIndex(7)) {
    cout<<"index: 7 DELETED"<<endl;
    cout<<"Size = "<<list1.Size()<<endl;
  }
  else {
    cout<<"index: 7 NOT DELETED!!"<<endl;
    cout<<"Size = "<<list1.Size()<<endl;
  }
  list1.printList();
  // cout<<"Expected Output:"<<endl
  //     <<"456 -> 5 -> 1 -> 0 -> 10 -> 1 -> 2 -> 100 -> NULL"<<endl
  //     <<"Actual Output:"<<endl;
  // list1.printList();
  // TestSeperator();









  return 0;
}
// ===========================
