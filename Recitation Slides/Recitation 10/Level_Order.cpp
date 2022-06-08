#include <iostream>
using namespace std;
#define COUNT 10
#include <queue>

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
    void LevelOrderTraverse(Node *root);
    void print2DUtil(Node *root, int space);
};

/*
Constructor for a Tree object
*/
Tree::Tree()
{
  this->root = NULL;
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
***************************************************************************
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                        Implement this function
This function prints all the elements in a tree in a level order fashion
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
***************************************************************************
*/

void Tree::LevelOrderTraverse(Node *root)
{
    // Base Case
    if (root == nullptr)  return;

    // Create an empty queue for level order tarversal
    queue<Node *> q;
    vector<int> v;


    // Enqueue Root
    q.push(root);
    v.push_back(root->data);

    while (q.empty() == false)
    {
        // Print front of queue
        Node *node = q.front();
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
 Main function that calls create tree, print Tree and the traversal function.
 */
int main()
{
  Tree t;
  t.createTree();
  //cout<<t.root->data<<endl;
  t.print2DUtil(t.root, 0);



  /**********************
    Uncomment this after implementation
  ***********************/


  cout << "\nLevel order traversal of binary tree is \n";
  t.LevelOrderTraverse(t.root);
  cout<<endl;


  return 0;
}
