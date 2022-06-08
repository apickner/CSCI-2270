#include"BinaryTree.hpp"
#include <stack>
#include <queue>

/*
Main function that calls create tree, print Tree and the traversal function.
*/
int main()
{
  Tree t;
  t.createTree();
  //cout<<t.root->data<<endl;
  t.print2DUtil(t.root, 0);

  cout << "Zig Zag traversal of binary tree is \n";
  t.ZigZagTraverse(t.root); // 1 3 2 4 5 6 7
  cout<<endl;

  Node* LCA = t.findLCA(t.root, t.root->right, t.root->left->left);

  cout << LCA->data << endl;

  return 0;
}
