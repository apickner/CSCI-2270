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
  MovieTree(); //HW5
  ~MovieTree(); //HW5
  void printMovieInventory(); //HW5
  void addMovieNode(int ranking, std::string title, int year, int quantity); //HW5
  void findMovie(std::string title); //HW5
  void rentMovie(std::string title); //HW5
  void deleteMovie(std::string title);
  void countMovies(); // COMPLETE
private:
  MovieNode *search(std::string title); //HW6
  MovieNode *root;
};
#endif
