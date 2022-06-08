#include <iostream>

using namespace std;

struct node {
	int key;
	node *next;
	node(int k, node *n) {
		key = k;
		next = n;
	}
};


int main(int argc, char const * argv[]) {

	node *x = new node(5, NULL); //using the constructor
	// first node in my linked-list will be the head and the tail
	// first node points to NULL because we only have the one node
	cout<<x->key<<endl;
	cout<<(*x).key<<endl;


	node *x2 = new node(6, NULL); //creating a new node

	x->next = x2;
	cout<<x2<<endl;
	cout<<x2->next<<endl;

	//traversal
	node *ptr = x;
	while (ptr != NULL) {
		cout<<ptr->key<<endl;
		ptr = ptr->next;
	}


	return 0;
}