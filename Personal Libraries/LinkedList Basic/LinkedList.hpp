#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// ===========================
#include "node.hpp"
// ===========================
class LinkedList {

  private:
    node *head;
    node *tail;

    bool isEmpty();

  public:
    // =====================================
    // Initializer
    LinkedList();

    // =====================================
    // Print functions
    void printList();

    // =====================================
    // Insert functions
    void insertAtHead(int);
    void insertAtTail(int);
    void insertAtNode(int, node*);

    // =====================================
    // Delete functions
    bool deleteAtHead();
    bool deleteAtTail();

    // =====================================
    // getter-functions for head, tail, & size
    node* Head() { return this->head; }
    node* Tail() { return this->tail; }
};

#endif
