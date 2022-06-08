#ifndef TREENODE_H
#define TREENODE_H

/*
Each node in the tree has this structure
*/
struct TreeNode
{
  int data;

  TreeNode *left;
  TreeNode *right;

  TreeNode(int data);
};

#endif
