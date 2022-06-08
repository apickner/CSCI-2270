#include <iostream>

#include "BST.hpp"
#include "treeNode.hpp"

/*
Constructor for a BST object
*/
BST::BST()
{
  this->root = NULL;
}

/*
This function prints all the elements in a tree in inorder fashion
*/
void BST::preOrderTraverse(TreeNode *root)
{
  // Start your code from here
  if (root == NULL) {
    return;
  }
  std::cout<<root->data<<" "<<std::endl;

  preOrderTraverse(root->left); // recursion

  preOrderTraverse(root->right); // recursion
}

/*
***************************************************************************
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                        Implement this function
This function prints all the elements in a tree in inorder fashion
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
***************************************************************************
*/
void BST::printTreeInOrder() {
  inOrderTraverse(this->root);
}

void BST::inOrderTraverse(TreeNode *root)
{
  // Start your code from here
  if (root == NULL) {
    return;
  }

  inOrderTraverse(root->left); // recursion

  std::cout<<root->data<<" "<<std::endl;

  inOrderTraverse(root->right); // recursion
}

/*
***************************************************************************
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                        Implement this function
This function prints all the elements in a tree in a post order fashion
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
***************************************************************************
*/
void BST::postOrderTraverse(TreeNode *root)
{
  // Start your code from here
  if (root == NULL) {
    return;
  }

  postOrderTraverse(root->left); // recursion

  postOrderTraverse(root->right); // recursion

  std::cout<<root->data<<" "<<std::endl;
}

/*
Forms a binary tree by inserting nodes. It make sures that
the insertion retains the property of a BST.
 */
TreeNode* BST::insertIntoBST(TreeNode *node, int value)
{
  if(this->root == NULL)
  {
    this->root = new TreeNode(value);
  }
  if(!node)
  {
     TreeNode *newNode = new TreeNode(value);
     return newNode;
  }
  else
  {
    if(value < node->data)
    {
        node->left = insertIntoBST(node->left, value);
    }
    else
    {
      node->right = insertIntoBST(node->right, value);
    }
  }
  return node;
}

/*
Returns the maximum node value from a given BST.
*/
TreeNode* BST::maxValueNode(TreeNode* root)
{
    TreeNode *current = node;

    /* loop down to find the rightmost leaf */
    while (current->right != NULL)
        current = current->right;

    return current;
}

/*
Prints a binary tree in a 2D fashion.
Note: The image of the tree is left rotated by 90 degrees.
*/
void BST::print2DUtil(TreeNode *root, int space)
{
    // Base case
    if (root == NULL)
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

TreeNode* BST::deleteNode(TreeNode *root, int value)
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
        TreeNode *temp = root->right;
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
        TreeNode *temp = root->left;
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
        TreeNode *maxLeft = maxValueNode(root->left);
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
bool BST::isValidBST(TreeNode *root)
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
