#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <sstream>
#include <iostream>
//#include <list>
#include <vector>
#include "globalConsts.h"

using namespace std;

class Component
{
public:
  Component();
  Component(string toParse);
  virtual ~Component();

  bool checkPars(const string &str, const string &pars);
  void parseComponent(string toParse);

  string getName();
  string getNodeNameX(unsigned int x);
  //list<string> getNodeList();
  vector<string> getNodeVector();
  string getParameters();
  unsigned int getNumberOfConnectedNodes();
  string getComponentType();

protected:
private:
  string name;
  //list<string> nodeNames;
  vector<string> nodeNames;
  //string nodeName1;
  //string nodeName2;
  string parameters;
  unsigned int numberOfConnectedNodes;
  string componentType;
};

#endif // COMPONENT_H
