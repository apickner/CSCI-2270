#include "BST.hpp"
#include "treeNode.hpp"
#include <iostream>

int main(int argc, char const *argv[]) {

  BST bst1;

  bst1.insertIntoBST(bst1.root, 5);
  bst1.insertIntoBST(bst1.root, 2);
  bst1.insertIntoBST(bst1.root, 3);
  bst1.insertIntoBST(bst1.root, 4);
  bst1.insertIntoBST(bst1.root, 1);
  bst1.insertIntoBST(bst1.root, 8);

  bst1.print2DUtil(bst1.root, 0);

  bst1.deleteNode(bst1.root, 5);

  bst1.print2DUtil(bst1.root, 0);

  std::cout << "max data: " << bst1.maxValueNode(bst1.root)->data << std::endl;

  return 0;
}
