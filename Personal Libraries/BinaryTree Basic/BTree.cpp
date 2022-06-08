#include <iostream>
#include <queue>
#include <stack>
#include <vector>

#include "BTree.hpp"
#include "treeNode.hpp"

using namespace std;

#define COUNT 10

/*
Constructor for a Tree object
*/
BTree::BTree()
{
  this->root = nullptr;
}

/*
Creates a tree of 7 elements
*/
void BTree::createTree()
{
  TreeNode *root     = new TreeNode(1);
  root->left         = new TreeNode(2);
  root->right        = new TreeNode(3);
  root->left->left   = new TreeNode(4);
  root->left->right  = new TreeNode(5);
  root->right->left  = new TreeNode(6);
  root->right->right = new TreeNode(7);
  this->root = root;
}

/*
Prints a binary tree in a 2D fashion.
Note: The image of the tree is left rotated by 90 degrees.
*/
void BTree::print2DUtil(TreeNode *root, int space)
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

void BTree::ZigZagTraverse(TreeNode *root)
{
  // if null then return
  if (!root)
  {
    return;
  }

  queue<TreeNode *> queue;
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
    TreeNode *temp = queue.front();
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

TreeNode* BTree::findLCA(TreeNode* root, TreeNode* a, TreeNode* b) {
  if (root == nullptr) {
    return root;
  }
  if (root == a || root == b) {
    return root;
  }
  TreeNode* leftLCA = findLCA(root->left, a, b);
  TreeNode* rightLCA = findLCA(root->right, a, b);

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

void BTree::LevelOrderTraverse(TreeNode *root)
{
    // Base Case
    if (root == nullptr)  return;

    // Create an empty queue for level order tarversal
    queue<TreeNode *> q;
    vector<int> v;


    // Enqueue Root
    q.push(root);
    v.push_back(root->data);

    while (q.empty() == false)
    {
        // Print front of queue
        TreeNode *node = q.front();
        cout << node->data << " ";

        // TODO

        // check left child and right child
        if (node->left != nullptr) {
          q.push(node->left);
        }
        if (node->right != nullptr) {
          q.push(node->right);
        }

        q.pop();

    }
}
