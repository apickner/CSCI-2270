#include <iostream>
#include <queue>
#include <stack>
using namespace std;
#define COUNT 10

/*
Each node in the tree has this structure
*/
struct Node
{
  int data;
  Node *left;
  Node *right;
  Node(int data)
  {
    this->data = data;
    this->left = this->right = nullptr;
  }
};

/*
Variables and functions for Tree ADT
*/
class Tree
{
public:
  Node *root;
  Tree();
  void createTree();
  void ZigZagTraverse(Node *root);
  void print2DUtil(Node *root, int space);

  Node* findLCA(Node* root, Node* a, Node* b);
};

/*
Constructor for a Tree object
*/
Tree::Tree()
{
  this->root = nullptr;
}

/*
Prints a binary tree in a 2D fashion.
Note: The image of the tree is left rotated by 90 degrees.
*/
void Tree::print2DUtil(Node *root, int space)
{
  // Base case
  if (root == nullptr)
  return;

  // Increase distance between levels
  space += COUNT;

  // Process right child first
  print2DUtil(root->right, space);

  // Print current node after space
  // count
  printf("\n");
  for (int i = COUNT; i < space; i++)
  printf(" ");
  printf("%d\n", root->data);

  // Process left child
  print2DUtil(root->left, space);
}

/*
Creates a tree of 7 elements
*/
void Tree::createTree()
{
  Node *root         = new Node(1);
  root->left         = new Node(2);
  root->right        = new Node(3);
  root->left->left   = new Node(4);
  root->left->right  = new Node(5);
  root->right->left  = new Node(6);
  root->right->right = new Node(7);
  this->root = root;
}

/*
***************************************************************************
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                      Implement this function
    This function prints all the elements in a tree in a zigzag order
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
***************************************************************************
*/

void Tree::ZigZagTraverse(Node *root)
{
  // if null then return
  if (!root)
  {
    return;
  }

  queue<Node *> queue;
  stack<int> stack;

  // push the root
  queue.push(root);

  // Push a marker to indicate end of level
  queue.push(NULL);

  // Tells us if we need to print elements left to right
  // or right to left
  bool lefttoright = true;



  while (!queue.empty())
  {

    // Done with traversing all the levels
    // Break the loop
    if(queue.size() == 1 && queue.front() == NULL)
    {
      break;
    }

    // pop out of queue
    Node *temp = queue.front();
    queue.pop();

    if(temp == NULL) {
      // Marker for next level
      queue.push(NULL);

      // Print the elements from the stack
      // Prints a level in right to left fashion
      if(!lefttoright) {
        // Print the contents of the stack and empty it
        while (!stack.empty()) {
          cout<<stack.top()<<endl;
          stack.pop();
        }
      }
      // Invert the order for next level
      // TODO
      if (!lefttoright) {
        lefttoright = true;
      }

      else {
        lefttoright = false;
      }
    }
    else
    {

      // Print the elements normally
      if(lefttoright) {
        cout<<temp->data<<endl;
      }

      else {
        stack.push(temp->data);
      }

      // Add the node's children to the queue
      // TODO
      if (temp->left) {
        queue.push(temp->left);
      }

      if (temp->right) {
        queue.push(temp->right);
      }
    }
  }
}

Node* Tree::findLCA(Node* root, Node* a, Node* b) {
  if (root == nullptr) {
    return root;
  }
  if (root == a || root == b) {
    return root;
  }
  Node* leftLCA = findLCA(root->left, a, b);
  Node* rightLCA = findLCA(root->right, a, b);

  if (leftLCA != nullptr && rightLCA != nullptr) {
    return root;
  }
  else if (leftLCA != nullptr) {
    return leftLCA;
  }
  else {
    return rightLCA;
  }
}
