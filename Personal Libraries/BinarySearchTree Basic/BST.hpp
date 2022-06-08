#ifndef BST_H
#define BST_H

#include <iostream>
#include "treeNode.hpp"

#define COUNT 10

/*
Class variables and methods for a BST
*/
class BST
{
  public:
    TreeNode *root;
    BST();
    TreeNode* insertIntoBST(TreeNode *root, int value);
    TreeNode* deleteNode(TreeNode *root, int value);
    TreeNode* maxValueNode(TreeNode* root);

    // used for traversing the tree
    void preOrderTraverse(TreeNode *root);
    void inOrderTraverse(TreeNode *root);
    void postOrderTraverse(TreeNode *root);

    // uses in-order traversal
    void printTreeInOrder();

    // returns whether or not a given BST is valid or not
    bool isValidBST(TreeNode *root);

    // prints the tree in a 2-D way (stolen from the TAs from recitation)
    void print2DUtil(TreeNode *root, int space);
};

#endif
