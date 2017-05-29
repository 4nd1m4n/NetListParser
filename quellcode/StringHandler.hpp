#ifndef STRINGHANDLER_HPP
#define STRINGHANDLER_HPP

#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

template <typename Out>
void split(const std::string &s, char delim, Out result);

std::vector<std::string> split(const std::string &s, char delim);

std::string vecOfStrToStr(std::vector<std::string> vecOfStr);

std::string mapToStr(std::map<std::string, std::string> mapOfStr);

#endif  // STRINGHANDLER_HPP