#ifndef MOVIETREE_HPP
#define MOVIETREE_HPP

#include <string>

struct MovieNode
{
  int ranking;
  std::string title;
  int year;
  int quantity;

  MovieNode *parent;
  MovieNode *leftChild;
  MovieNode *rightChild;

  MovieNode(){
    parent = leftChild = rightChild = nullptr;
  }

  MovieNode(int r, std::string t, int y, int q) {
    ranking = r;
    title = t;
    year = y;
    quantity = q;
    parent = leftChild = rightChild = nullptr;
  }
};

class MovieTree
{
public:
  MovieTree(); //COMPLETE
  ~MovieTree(); //TODO
  void printMovieInventory(); //COMPLETE
  void addMovieNode(int ranking, std::string title, int year, int quantity); //COMPLETE
  void findMovie(std::string title); //COMPLETE
  void rentMovie(std::string title); //COMPLETE
private:
  MovieNode *search(std::string title); //COMPLETE

  // void printInorder(MovieNode* root); //COMPLETE
  // void printMovieInfo(MovieNode* node); //COMPLETE

  MovieNode *root;
};

#endif
