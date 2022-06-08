#include <iostream>
/////////////////////////
using namespace std;
/////////////////////////
struct Node
{
  int key;
  Node *left, *right;
};
/////////////////////////
struct Node *newNode(int k)
{
  Node *temp = (Node *)malloc(sizeof(Node));
  temp->key = k;
  temp->left = temp->right = NULL;
  return temp;
};
/////////////////////////
class BST
{
private:

public:
  BST() {}
  /////////////////////////
  void inorder(Node*);
  Node* insert(Node*, int);
  Node* minValueNode(Node*);
  Node* deleteNode(Node*, int);
};
/////////////////////////
void BST::inorder(Node* root){
  if (root != NULL) {
    inorder(root->left);
    /////////////////////////
    cout<<root->key<<" ";
    /////////////////////////
    inorder(root->right);
  }
}

Node* BST::insert(Node* root, int key){
  if (root == NULL) return newNode(key);
  /////////////////////////
  if (key < root->key)
      root->left = insert(root->left, key);
  else
      root->right = insert(root->right, key);
  /////////////////////////
  return root;
}

Node* BST::minValueNode(Node* root){
  Node *temp = root;
  /////////////////////////
  while (temp != NULL) {
    temp = temp->left;
  }
  /////////////////////////
  return temp;
}

Node* BST::deleteNode(Node* root, int key){
  // base case
  if (root == NULL) {
    return root;
  }

  // recursively calls for ancestors of node
  if (key < root->key) {
    root->left = deleteNode(root->left, key);
  }
  else if (key > root->key) {
    root->right = deleteNode(root->right, key);
  }
  cout<<root->key<<" ";
  //
  if (root->left == NULL && root->right == NULL) {
    delete root;
    return NULL;
  }
  else if (root->left == NULL) {
    Node *temp = root->right;
    delete root;
    return temp;
  }
  else if (root->right == NULL) {
    Node *temp = root->right;
    delete root;
    return temp;
  }
  else {
    Node *succParent = root;
    Node *succ = root->right;
    while (succ->left != NULL) {
      succParent = succ;
      succ = succ->left;
    }

    succParent->left = succ->right;
    root->key = succ->key;

    delete succ;
    return root;
  }


}
/////////////////////////
/////////////////////////
/////////////////////////
int main(int argc, char const *argv[]) {

  BST bst;
  Node* root = NULL;

  root = bst.insert(root, 50);
  root = bst.insert(root, 30);
  root = bst.insert(root, 20);
  root = bst.insert(root, 40);
  root = bst.insert(root, 70);
  root = bst.insert(root, 60);
  root = bst.insert(root, 80);

  cout<<"Inorder traversal of the tree...\n";
  bst.inorder(root);

  cout<<"\nDelete 20\n";
  root = bst.deleteNode(root, 20);
  cout<<"Inorder traversal of the modified tree...\n";
  bst.inorder(root);

  cout<<"\nDelete 30\n";
  root = bst.deleteNode(root, 30);
  cout<<"Inorder traversal of the modified tree...\n";
  bst.inorder(root);

  cout<<"\nDelete 50\n";
  root = bst.deleteNode(root, 50);
  cout<<"Inorder traversal of the modified tree...\n";
  bst.inorder(root);

  delete root;

  return 0;
}
