#ifndef BTREE_H
#define BTREE_H

#define COUNT 10

#include "treeNode.hpp"

class BTree
{
public:
  TreeNode *root;

  BTree();

  void createTree();

  void print2DUtil(TreeNode *root, int space);

  void ZigZagTraverse(TreeNode *root);

  TreeNode* findLCA(TreeNode* root, TreeNode* a, TreeNode* b);

  void LevelOrderTraverse(TreeNode *root);
};

#endif
