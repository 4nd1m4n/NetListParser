#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "GlobalConsts.hpp"
#include "StringHandler.hpp"

using namespace std;

class Component {
 public:
  Component(const string &setOutputDepth = OUT_ALL);
  ~Component();

  void mapFirstComponentValue(const string mapKey, const vector<string> &params,
                              map<string, string> &paramMap);
  void checkStringForExpressions(const string &str, const vector<string> &exp,
                                 map<string, string> &paramMap);
  static bool checkPars(const string &str, const string &pars);
  void parseToMembers(vector<string> &vecOfStr, string &componentName,
                      unsigned int &numberOfNodeConnections,
                      vector<string> &vecOfNodeNames, vector<string> &params);
  void parseComponent(const string &toParse, const string &setOutputDepth = "");

  const string getName();
  const string getXthNodeName(unsigned int x);
  const vector<string> getParameters();
  const unsigned int getNumberOfConnectedNodes();
  const string getComponentType();

 protected:
 private:
  string name;
  vector<string> nodeNames;
  vector<string> parameters;
  map<string, string> parameterMap;
  unsigned int numberOfConnectedNodes;
  string componentType;

  string outputDepth;
};

#endif  // COMPONENT_HPP
