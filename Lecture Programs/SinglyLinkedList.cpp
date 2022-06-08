#include <iostream>

using namespace std;

struct node {
  int key;
  node *next;
  node(int k, node* n) {
    key = k;
    next = n;
  }
};

int main(int argc, char * argv[]) {
// ====================================
  int i = 1;
  node *head = new node(i,NULL);
  node *p = head;
// ====================================
  i++;
  while (i<=10) {
    // creating a new node
    node *n = new node(i, NULL); // n->key = i, n->next = NULL
    p->next = n; //
    p = n;
    i++;
  }

  while (head != NULL) {
    cout<<head->key<<endl;
    head = head->next;
  }


  return 0;
}
