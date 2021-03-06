#include <iostream>
#include "BST.hpp"
using namespace std;
#define COUNT 10

/*
Silver Challenge
Deletes a node in a BST, by retaining the BST property.
*/
Node* BST::deleteNode(Node *root, int value)
{
  if(root == NULL)
  {
    return NULL;
  }
  // If value to be deleted is less than the root
  // Then we need to search in the left subtree
  else if(value < root->data)
  {
    root->left = deleteNode(root->left, value);
  }
  // If value to be deleted is greater than the root
  // Then we need to search in the right subtree
  else if(value > root->data)
  {
    root->right = deleteNode(root->right, value);
  }
  // We found the node with the value to be deleted
  else
  {
    //Case 1
    // Leaf node
    if(root->left == NULL && root->right == NULL)
    {
      delete root;
      root = NULL;
    }
    /*************************
      Case 2 - Node with one child
      Has a right child
      Complete this function
    *************************/
    else if(root->left == NULL)
    {
        // TODO
        Node *temp = root->right;
        delete root;
        root = temp;
    }
    /*************************
      Case 2 - Node with one child
      Has a left child
      Complete this function
    *************************/
    else if(root->right == NULL)
    {
        // TODO
        Node *temp = root->left;
        delete root;
        root = temp;
    }
    /*************************
      Case 3 - Node with two children
      Complete this function
    *************************/
    else
    {
        // TODO
        Node *maxLeft = maxValueNode(root->left);
        root->data = maxLeft->data;
        root->left = deleteNode(root->left, root->data);
    }
  }
  return root;
}

/*
Gold Challenge
Checks if a binary tree is a valid binary search tree.
*/
bool isValidBST(Node *root)
{
    // TODO
    /**************
    Base Base
    **************/
    if (root == NULL) {
      return true;
    }
    /**************
    left child data greater than parent
    **************/
    if ((root->left != NULL) && (root->data < (root->left)->data)) {
      return false;
    }
    /**************
    right child data less than parent
    **************/
    if ((root->right != NULL) && (root->data > (root->right)->data)) {
      return false;
    }


    return isValidBST(root->left) && isValidBST(root->left);

}

/*
 Main function that calls create,
 print, delete and other required functions.
 */
int main()
{
    BST t;
    t.insertIntoBST(t.root, 5);
    t.insertIntoBST(t.root, 2);
    t.insertIntoBST(t.root, 1);
    t.insertIntoBST(t.root, 4);
    t.insertIntoBST(t.root, 7);
    t.insertIntoBST(t.root, 10);
    t.insertIntoBST(t.root, 8);
    t.insertIntoBST(t.root, 6);

    cout<<"----------------Intial tree is ---------------"<<endl;
    t.print2DUtil(t.root, 1);

    cout << "\nInorder traversal of the binary search tree is \n"<<endl;
    t.inOrderTraverse(t.root);
    cout<<endl;

    // Deleting node with 1 child
    cout<<"----------------After deleting 2---------------"<<endl;
    t.root = t.deleteNode(t.root, 2);
    t.print2DUtil(t.root, 1);
    cout << "\nInorder traversal of the binary search tree is \n"<<endl;
    t.inOrderTraverse(t.root);
    cout<<endl;

    // Deleting Leaf
    cout<<"----------------After deleting 4---------------"<<endl;
    t.root = t.deleteNode(t.root, 4);
    t.print2DUtil(t.root, 1);
    cout << "\nInorder traversal of the binary search tree is \n"<<endl;
    t.inOrderTraverse(t.root);
    cout<<endl;

    // Deleting Node with 2 children
    cout<<"----------------After deleting 7---------------"<<endl;
    t.root = t.deleteNode(t.root, 7);
    t.print2DUtil(t.root, 1);
    cout << "\nInorder traversal of the binary search tree is \n"<<endl;
    t.inOrderTraverse(t.root);


    // Gold challenge - Check if a tree is a valid BST
    cout<<boolalpha<<isValidBST(t.root);

    cout<<endl;

    return 0;
}
