#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "GlobalConsts.hpp"
#include "StringHandler.hpp"

using namespace std;

class Component {
 public:
  Component();
  Component(string toParse);
  ~Component();

  static bool checkPars(const string &str, const string &pars);
  void parseToMembers(vector<string> &vecOfStr, string &componentName,
                      unsigned int &numberOfNodeConnections,
                      vector<string> &vecOfNodeNames, vector<string> &params);
  void parseComponent(const string &toParse);

  const string getName();
  const string getXthNodeName(unsigned int x);
  // list<string> getNodeList();
  // const vector<string> getNodeVector();
  const vector<string> getParameters();
  const unsigned int getNumberOfConnectedNodes();
  const string getComponentType();

 protected:
 private:
  string name;
  vector<string> nodeNames;
  vector<string> parameters;
  unsigned int numberOfConnectedNodes;
  string componentType;
};

#endif  // COMPONENT_HPP
