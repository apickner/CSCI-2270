#include "HW5-MovieTree.hpp"
#include <iostream>

void deletePostorder(MovieNode* root);
void printInorder(MovieNode* root);
void printMovieInfo(MovieNode *node);
MovieNode* searchRecursive(std::string title, MovieNode *root);

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

void MovieTree::rentMovie(std::string title) {
  MovieNode *foundNode = search(title);
  if (foundNode != nullptr) {
    if (foundNode->quantity > 0) {
      std::cout<<"Movie has been rented."<<std::endl;
      (foundNode->quantity)--;
      printMovieInfo(foundNode);
    }
    else {
      std::cout<<"Movie out of stock."<<std::endl;
    }
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
    // std::cout<<"true"<<std::endl;
    if (root->title == title) {
      // std::cout<<"true"<<std::endl;
      // std::cout<<root->title<<std::endl;
      return root;
    }
    else if ((root->title) <= title) {
      // std::cout<<"true"<<std::endl;
      return searchRecursive(title, root->rightChild);
    }
    else {
      // std::cout<<"true"<<std::endl;
      return searchRecursive(title, root->leftChild);
    }
  }
  return root;
}
