#include "StringHandler.hpp"

template <typename Out>
void split(const std::string &s, char delim, Out result) {
  std::stringstream ss;
  ss.str(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    *(result++) = item;
  }
}

std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, std::back_inserter(elems));
  return elems;
}

std::string vecOfStrToStr(std::vector<std::string> vecOfStr) {
  std::string concatStrOfVec = "";
  for (auto it = vecOfStr.begin(); it != vecOfStr.end(); it++) {
    if (it != vecOfStr.begin()) {
      concatStrOfVec += " ";
    }
    concatStrOfVec += *it;
  }
  return concatStrOfVec;
}