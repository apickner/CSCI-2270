#ifndef NODE_H
#define NODE_H

struct node {
  int data;
  node *next;

  node();
  node(int);
  node(int, node*);
};

#endif
