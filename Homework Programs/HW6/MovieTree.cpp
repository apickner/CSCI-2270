#include "MovieTree.hpp"
#include <iostream>

void deletePostorder(MovieNode* root);
void printInorder(MovieNode* root);
void printMovieInfo(MovieNode *node);
MovieNode* searchRecursive(std::string title, MovieNode *root);
// MovieNode* deleteRecursive(MovieNode* root, std::string title);
MovieNode* deleteNode(MovieNode *root, std::string title);


MovieTree::MovieTree() {
  root = nullptr;
}

MovieTree::~MovieTree() {
  deletePostorder(this->root);
}

void deletePostorder(MovieNode* root) {
  if (root == nullptr) {
    return;
  }

  deletePostorder(root->leftChild);
  deletePostorder(root->rightChild);

  delete root;
}

void MovieTree::printMovieInventory() {
  printInorder(this->root);
}

void printInorder(MovieNode* root) {
  if (root == nullptr) {
    return;
  }

  printInorder(root->leftChild); // recursion

  std::cout<<"Movie: "<<root->title<<" "<<root->quantity<<std::endl;
  // std::cout << &root << '\n';

  printInorder(root->rightChild); // recursion
}

void printMovieInfo(MovieNode *node) {
  std::cout<<"Movie Info:"<<std::endl
          <<"==========="<<std::endl
          <<"Ranking:"<<node->ranking<<std::endl
          <<"Title:"<<node->title<<std::endl
          <<"Year:"<<node->year<<std::endl
          <<"Quantity:"<<node->quantity<<std::endl;
}

void MovieTree::addMovieNode(int ranking, std::string title, int year, int quantity) {
  MovieNode *newMovieNode = new MovieNode(ranking, title, year, quantity);
  MovieNode *temp = this->root;
  MovieNode *parent = temp;
  while (temp != nullptr) {
    parent = temp;
    if ((temp->title) > title) {
      temp = temp->leftChild;
    }
    else {
      temp = temp->rightChild;
    }
  }
  if (parent == nullptr) {
    this->root = newMovieNode;
  }
  else {
    if ((parent->title) > title) {
      parent->leftChild = newMovieNode;
      newMovieNode->parent = parent;
    }
    else {
      parent->rightChild = newMovieNode;
      newMovieNode->parent = parent;
    }
  }
}

void MovieTree::findMovie(std::string title) {
  MovieNode *foundNode = search(title);
  if (foundNode != nullptr) {
    printMovieInfo(foundNode);
  }
  else {
    std::cout<<"Movie not found."<<std::endl;
  }
}

MovieNode* MovieTree::search(std::string title) {
  return searchRecursive(title, this->root);
}

MovieNode* searchRecursive(std::string title, MovieNode *root) {
  if (root != nullptr) {
    if (root->title == title) {
      return root;
    }
    else if ((root->title) <= title) {
      return searchRecursive(title, root->rightChild);
    }
    else {
      return searchRecursive(title, root->leftChild);
    }
  }
  return root;
}

void MovieTree::deleteMovie(std::string title) {
  MovieNode *temp = search(title);
  if (temp == nullptr) {
    std::cout << "Movie not found." << '\n';
  }
  else {
    this->root = deleteNode(this->root, title);
  }
}

MovieNode* deleteNode(MovieNode *root, std::string title)
{
  if(root == nullptr)
  {
    return nullptr;
  }
  // If title to be deleted is less than the root
  // Then we need to search in the left subtree
  else if(title < root->title)
  {
    root->leftChild = deleteNode(root->leftChild, title);
  }
  // If title to be deleted is greater than the root
  // Then we need to search in the right subtree
  else if(title > root->title)
  {
    root->rightChild = deleteNode(root->rightChild, title);
  }
  // We found the node with the title to be deleted
  else
  {
    //Case 1
    // Leaf node
    if(root->leftChild == nullptr && root->rightChild == nullptr)
    {
      delete root;
      root = nullptr;
    }
    /*************************
      Case 2 - Node with one child
      Has a right child
    *************************/
    else if(root->leftChild == nullptr)
    {
        MovieNode *temp = root->rightChild;
        delete root;
        root = temp;
    }
    /*************************
      Case 2 - Node with one child
      Has a left child
    *************************/
    else if(root->rightChild == nullptr)
    {
        MovieNode *temp = root->leftChild;
        delete root;
        root = temp;
    }
    /*************************
      Case 3 - Node with two children
    *************************/
    else
    {
        MovieNode *maxParent = root;
        MovieNode *maxLeft = root->leftChild;

        while (maxLeft->rightChild != nullptr)
        {
          maxParent = maxLeft;
          maxLeft = maxLeft->rightChild;
        }
        root->title = maxLeft->title;
        root->ranking = maxLeft->ranking;
        root->year = maxLeft->year;
        root->quantity = maxLeft->quantity;

        root->leftChild = deleteNode(root->leftChild, root->title);
    }
  }
  return root;
}

void MovieTree::rentMovie(std::string title) {
  MovieNode *foundNode = search(title);
  if (foundNode != nullptr) {
    if (foundNode->quantity > 0) {
      std::cout<<"Movie has been rented."<<std::endl;
      (foundNode->quantity)--;
      printMovieInfo(foundNode);
      if (foundNode->quantity == 0) {
        deleteMovie(foundNode->title);
      }
    }
    else {
      std::cout<<"Movie out of stock."<<std::endl;
    }
  }
  else {
    std::cout<<"Movie not found."<<std::endl;
  }
}

int recursiveCount(MovieNode *root) {
  if (root == nullptr) {
    return 0;
  }

  return recursiveCount(root->leftChild) + recursiveCount(root->rightChild) + 1;
}

void MovieTree::countMovies() {
  std::cout<<"Count = "<<recursiveCount(this->root)<<std::endl;
}

// MovieNode* deleteRecursive(MovieNode* root, std::string title) {
//   // base case
//   if (root == nullptr) {
//     return root;
//   }
//   // recursively call
//   else if (title < root->title) {
//     root->leftChild = deleteRecursive(root->leftChild, title);
//   }
//   else if (title > root->title) {
//     root->rightChild = deleteRecursive(root->rightChild, title);
//   }
//   else {
//
//     // case 1: leaf Node
//     if ((root->leftChild) == nullptr && (root->rightChild) == nullptr) {
//
//       delete root;
//       root = nullptr;
//     }
//     // case 2: left child only
//     else if (root->rightChild == nullptr) {
//       MovieNode* temp = root->leftChild;
//
//       delete root;
//       root = temp;
//     }
//     // case 3: right child only
//     else if (root->leftChild == nullptr) {
//       MovieNode* temp = root->rightChild;
//
//       delete root;
//       root = temp;
//     }
//     // case 4: left and right child
//     else {
//       MovieNode *succParent = root;
//       MovieNode *succ = root->rightChild;
//       while (succ->leftChild != nullptr) {
//         succParent = succ;
//         succ = succ->leftChild;
//       }
//       root->title = succ->title;
//       root->ranking = succ->ranking;
//       root->year = succ->year;
//       root->quantity = succ->quantity;
//
//
//       // delete succ;
//       root->rightChild = deleteRecursive(root->leftChild, root->title);
//     }
//     return root;
//   }
// }
