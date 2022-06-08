#include <cstddef>
#include <iostream>

#include "LinkedList.hpp"
#include "node.hpp"

LinkedList::LinkedList() {
  head = tail = NULL;
}

void LinkedList::printList() {
  node *iterator = Head();
  while (iterator != NULL) {
    std::cout<<iterator->data<<" -> ";
    iterator = (iterator)->next;
  }
  std::cout<<"NULL"<<std::endl;
}

void LinkedList::insertAtHead(int data) {
  node *newHead = new node(data, Head());
  this->head = newHead;
  if ((this->head)->next == NULL) {
    this->tail = Head();
  }
}

void LinkedList::insertAtTail(int data) {
  if (this->head == NULL) {
    insertAtHead(data);
  }
  else {
    node *newTail = new node(data);
    this->tail->next = newTail;
    this->tail = newTail;
    if (Head()->next == NULL) {
      this->head = Tail();
    }
  }
}

void LinkedList::insertAtNode(int data, node *prevNode) {
  node *newNode = new node(data, prevNode->next);
  prevNode->next = newNode;

}

bool LinkedList::deleteAtHead() {
  if (!isEmpty()) {
    node *temp = Head()->next;
    delete this->head;
    this->head = temp;
    return true;
  }
  return false;
}

bool LinkedList::deleteAtTail() {
  if (!isEmpty()) {
    node *iterator = Head();
    while (iterator->next != Tail()) {
      iterator = iterator->next;
    }
    node *oldTail = iterator->next;
    this->tail = iterator;
    (this->tail)->next = NULL;
    delete oldTail;
    return true;
  }
  return false;
}

bool LinkedList::isEmpty() {
  return (Head() == NULL);
}
