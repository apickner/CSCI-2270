#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct User {
  string username;
  float gpa;
  int age;
};

ostream& operator<<(ostream& os, const User& user) {
  os<<user.username<<" ["<<user.gpa<<"] age: "<<user.age<<endl;
  return os;
}

void addUser(vector<User> *users, string _username, float _gpa, int _age);
void printList(const vector<User> users);

int main(int argc, char const * argv[]) {
  vector<User> users;

  ifstream ifs("StudentFile");

  string line;
  while (getline(ifs, line)) {
    string username;
    float gpa;
    int age;

    istringstream iss(line);

    iss>>username;
    iss>>gpa;
    iss>>age;

    addUser(&users, username, gpa, age);
  }
  printList(users);

  return 0;
}

void addUser(vector<User> *users, string _username, float _gpa, int _age) {
  User user;

  user.username = _username;
  user.gpa = _gpa;
  user.age = _age;

  users->push_back(user);
}

void printList(const vector<User> users) {
  for (auto user : users) {
    cout<<user<<endl;
  }
}
