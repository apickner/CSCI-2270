#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

struct Student {
  int ID;
  string name, major;
  Student(){}
  Student(int id, string n, string m) {
    ID = id;
    name = n;
    major = m;
  }
};

class Date {
  private:
    int day, month, year;

  public:
    Date(){}
    Date(int d, int m, int y) {
      day = d;
      month = m;
      year = y;
    }

    void printDate() {
      cout<<month<<" "<<day<<" "<<year<<endl;
    }

    void setMonth(int m) {
      if (m>0 && m<13) {
        month = m;
      } else {
        cout<<"Month is out of range"<<endl;
      }
    }
    void setYear(int y) {
      if (y>0 && y<2019) {
        year = y;
      } else {
        cout<<"Year is out of range"<<endl;
      }
    }
    void setDay(int d) {
      if (d>0 && d<32) {
        day = d;
      } else {
        cout<<"Day is out of range"<<endl;
      }
    }
};

int main() {
  Date d(31,8,2018); // still breaks the program because m = 31 is out of range

  d.printDate();

  // generates an error because we can't return a private variable
  // cout<<d.month;

  // d.setMonth(13); // illegal value, no update
  // d.setMonth(12); // legal value, there is an update
  // d.setYear(2019); // illegal value, no update
  // d.setYear(2017); // legal value, there is an update
  // d.setDay(32); // illegal value, no update
  // d.setDay(31); // legal value, there is an update

  d.printDate();
}
