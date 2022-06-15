#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
// ------------------------------------------------------------------------------------------
#include "FileToString.hpp"
// ------------------------------------------------------------------------------------------
std::vector<std::string> fileToString(std::string fileName) {
  std::ifstream ifs(fileName);

  std::vector<std::string> contents;

  std::string word;

  while (ifs >> word) {
    contents.push_back(word);
  }



  return contents;
}
// ------------------------------------------------------------------------------------------
