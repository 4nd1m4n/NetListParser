#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>
#include <sstream>
#include <string>
//#include <list>
#include <vector>
#include "GlobalConsts.hpp"
#include "StringHandler.hpp"

using namespace std;

class Component {
 public:
  Component();
  Component(string toParse);
  virtual ~Component();

  bool checkPars(const string &str, const string &pars);
  void parseToMembers(vector<string> &vecOfStr, string &componentName,
                      unsigned int &numberOfNodeConnections,
                      vector<string> &vecOfNodeNames, vector<string> &params);
  void parseComponent(const string &toParse);

  string getName();
  string getNodeNameX(unsigned int x);
  // list<string> getNodeList();
  vector<string> getNodeVector();
  vector<string> getParameters();
  unsigned int getNumberOfConnectedNodes();
  string getComponentType();

 protected:
 private:
  string name;
  vector<string> nodeNames;
  vector<string> parameters;
  unsigned int numberOfConnectedNodes;
  string componentType;
};

#endif  // COMPONENT_HPP
