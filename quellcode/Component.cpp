#include "Component.hpp"

Component::Component() {
  name = "";
  parameters.clear();
  numberOfConnectedNodes = 0;
  nodeNames.clear();
  componentType = "";
}

Component::Component(string toParse) {
  name = "";
  parameters.clear();
  numberOfConnectedNodes = 0;
  nodeNames.clear();
  componentType = "";

  parseComponent(toParse);
}

Component::~Component() {}

bool Component::checkPars(const string &str, const string &pars) {
  // if (str.size)
  if ((str.compare(0, 1, pars, 0, 1) == 0)) {
    return true;
  } else {
    return false;
  }
}

void Component::parseToMembers(vector<string> &vecOfStr, string &componentName,
                               unsigned int &numberOfNodeConnections,
                               vector<string> &vecOfNodeNames,
                               vector<string> &params) {
  componentName = vecOfStr.at(0);

  vecOfNodeNames.reserve(numberOfNodeConnections);
  for (unsigned int i = 1; i <= numberOfNodeConnections; i++) {
    vecOfNodeNames.push_back(vecOfStr.at(i));
  }

  params.assign(vecOfStr.begin() + 1 + numberOfNodeConnections, vecOfStr.end());
}

void Component::parseComponent(const string &toParse) {
  name = "";
  parameters.clear();
  numberOfConnectedNodes = 0;
  nodeNames.clear();
  componentType = "";

  vector<string> splittedToParse = split(toParse, ' ');

  if (checkPars(toParse, PARS_CMNT)) {
    cout << "* found.\n";

    componentType = PARS_CMNT;
    name = PARS_CMNT;
    // cuts off the comment indicator "*" = PARS_CMNT
    parameters.push_back(toParse.substr(1));

    cout << vecOfStrToStr(parameters) << "\n";

  } else if (checkPars(toParse, PARS_R)) {
    cout << "R found.\n";

    componentType = PARS_R;
    numberOfConnectedNodes = 2;
    parseToMembers(splittedToParse, name, numberOfConnectedNodes, nodeNames,
                   parameters);

    cout << "\n " << name << " " << nodeNames.at(0) << " " << nodeNames.at(1)
         << " " << vecOfStrToStr(parameters) << " \n\n";

  } else if (checkPars(toParse, PARS_L)) {
    cout << "L found.\n";
  } else if (checkPars(toParse, PARS_C)) {
    cout << "C found.\n";
  } else if (checkPars(toParse, PARS_D)) {
    cout << "D found.\n";
  } else if (checkPars(toParse, PARS_V)) {
    cout << "V found.\n";

    componentType = PARS_V;
    numberOfConnectedNodes = 2;
    parseToMembers(splittedToParse, name, numberOfConnectedNodes, nodeNames,
                   parameters);

    cout << "\n " << name << " " << nodeNames.at(0) << " " << nodeNames.at(1)
         << " " << vecOfStrToStr(parameters) << " \n\n";
  } else if (checkPars(toParse, PARS_I)) {
    cout << "I found.\n";

    componentType = PARS_I;
    numberOfConnectedNodes = 2;
    parseToMembers(splittedToParse, name, numberOfConnectedNodes, nodeNames,
                   parameters);

    cout << "\n " << name << " " << nodeNames.at(0) << " " << nodeNames.at(1)
         << " " << vecOfStrToStr(parameters) << " \n\n";
  } else if (checkPars(toParse, PARS_E)) {
    cout << "E found.\n";
  } else if (checkPars(toParse, PARS_F)) {
    cout << "F found.\n";

    componentType = PARS_F;
    numberOfConnectedNodes = 2;
    parseToMembers(splittedToParse, name, numberOfConnectedNodes, nodeNames,
                   parameters);

    cout << "\n " << name << " " << nodeNames.at(0) << " " << nodeNames.at(1)
         << " " << vecOfStrToStr(parameters) << " \n\n";
  } else if (checkPars(toParse, PARS_G)) {
    cout << "G found.\n";
  } else if (checkPars(toParse, PARS_H)) {
    cout << "H found.\n";
  } else if (checkPars(toParse, PARS_DOT)) {
    cout << ". found.\n";
  } else {
    cout << "Unknown found.\n";
  }
}

string Component::getName() { return name; }

string Component::getNodeNameX(unsigned int x) {
  if (x < nodeNames.size()) {
    return nodeNames.at(x);
  } else {
    return "";
  }
}

// list<string> Component::getNodeList()
//{
//  return nodeNames;
//}

vector<string> Component::getNodeVector() { return nodeNames; }

vector<string> Component::getParameters() { return parameters; }

unsigned int Component::getNumberOfConnectedNodes() {
  return numberOfConnectedNodes;
}

string Component::getComponentType() { return componentType; }
