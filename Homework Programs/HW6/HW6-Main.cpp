#include "MovieTree.hpp"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//////////////////////////////
// List of Helper Functions //
//////////////////////////////

void MovieFileReader(MovieTree *Tree, string filename);

void displayMenu();

int main(int argc, char const *argv[]) {

  ///////////////////////////////
  // File from command line args
  string filename = argv[1];
  cout<<"Trying to read movies in from the file: "<<argv[1]<<endl;

  ///////////////////////////////
  // Creating a Tree and reading movies into it from the specified file
  MovieTree Tree1;
  MovieFileReader(&Tree1, filename);

  ///////////////////////////////
  // Variable creation
  bool quit = false;
  int input; // I was having difficulty using standard cin, so I resorted to using getline
  string s_input; // basically used the switch statement implementation from assignment #3
  string title;

  while (!quit) {
    displayMenu();

    try {
      getline(cin, s_input);
      input = stoi(s_input);
    }

    catch (exception a) {
      cout<<"Invalid input"<<endl;
      continue;
    }

    switch (input) {
      case 1:
        cout<<"Title:"<<endl;
        getline(cin, title);
        Tree1.findMovie(title);
        break;

      case 2:
        cout<<"Title:"<<endl;
        getline(cin, title);
        Tree1.rentMovie(title);
        break;

      case 3:
        Tree1.printMovieInventory();
        break;

      case 4:
        cout<<"Title:"<<endl;
        getline(cin, title);
        Tree1.deleteMovie(title);
        break;

      case 5:
        Tree1.countMovies();
        break;

      case 6:
        quit = true;
        cout<<"Goodbye!"<<endl;
        break;

      default:
        cout<<"Invalid input!"<<endl;
        break;
    }

  }

  return 0;
}

void MovieFileReader(MovieTree *Tree, string filename) {

  ifstream ifs(filename);

  string title;
  string year, rank, q;

  int releaseYear, imdbRank, quantity = 0;

  if (ifs.is_open()) {
    while (!ifs.eof()) {
      getline(ifs, rank, ',');
      imdbRank = stoi(rank);
      getline(ifs, title, ',');
      getline(ifs,year, ',');
      releaseYear = stoi(year);
      getline(ifs,q);
      quantity = stoi(q);

      // cout<<"Movie:"<<endl<<"\t"<<imdbRank<<endl<<"\t"<<title<<endl<<"\t"<<releaseYear<<endl<<"\t"<<quantity<<endl;

      Tree->addMovieNode(imdbRank, title, releaseYear, quantity);
    }
  }
  else { cout << "File not opened!" << endl; }
}

void displayMenu() {
  cout<<"======Main Menu======"<<endl
      <<"1. Find a movie"<<endl
      <<"2. Rent a movie"<<endl
      <<"3. Print the inventory"<<endl
      <<"4. Delete a movie"<<endl
      <<"5. Count movies"<<endl
      <<"6. Quit"<<endl;
}
