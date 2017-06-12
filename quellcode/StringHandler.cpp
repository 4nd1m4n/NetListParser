#include "StringHandler.hpp"

// source of this section is from:
// https://stackoverflow.com/questions/236129/split-a-string-in-c/7408245

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

// https://stackoverflow.com/questions/236129/split-a-string-in-c/7408245
// end of this section

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

std::string mapToStr(std::map<std::string, std::string> mapOfStr) {
  std::string concatStr = "";
  for (auto &it : mapOfStr) {
    concatStr += it.first + " | " + it.second + "\n";
  }
  return concatStr;
}
