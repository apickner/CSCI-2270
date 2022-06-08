#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Movie {
private:
  string title;
  int year;
  float rating;
public:
  Movie() {
    title = "unknown";
    year = 2018;
    rating = 0.0;
  }
  Movie(string _title, int _year, float _rating) {
    title = _title;
    year = _year;
    rating = _rating;
  }

  string getTitle() { return title; }
  void setTitle(string newTitle) {
    title = newTitle;
  }

  int getYear() { return year; }
  void setYear(int newYear) {
    year = newYear;
  }

  float getRating() { return rating; }
  void setRating(float newRating) {
    rating = newRating;
  }
};
