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
  for (unsigned int i = 0; i < pars.size(); i++) {
    if ((str.compare(0, 1, pars, i, 1) == 0)) {
      return true;
    }
  }
  return false;
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

    componentType = PARS_L;
    numberOfConnectedNodes = 2;
    parseToMembers(splittedToParse, name, numberOfConnectedNodes, nodeNames,
                   parameters);

    cout << "\n " << name << " " << nodeNames.at(0) << " " << nodeNames.at(1)
         << " " << vecOfStrToStr(parameters) << " \n\n";
  } else if (checkPars(toParse, PARS_C)) {
    cout << "C found.\n";

    componentType = PARS_C;
    numberOfConnectedNodes = 2;
    parseToMembers(splittedToParse, name, numberOfConnectedNodes, nodeNames,
                   parameters);

    cout << "\n " << name << " " << nodeNames.at(0) << " " << nodeNames.at(1)
         << " " << vecOfStrToStr(parameters) << " \n\n";
  } else if (checkPars(toParse, PARS_D)) {
    cout << "D found.\n";

    componentType = PARS_D;
    numberOfConnectedNodes = 2;
    parseToMembers(splittedToParse, name, numberOfConnectedNodes, nodeNames,
                   parameters);

    cout << "\n " << name << " " << nodeNames.at(0) << " " << nodeNames.at(1)
         << " " << vecOfStrToStr(parameters) << " \n\n";
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

    componentType = PARS_E;
    numberOfConnectedNodes = 2;
    parseToMembers(splittedToParse, name, numberOfConnectedNodes, nodeNames,
                   parameters);

    cout << "\n " << name << " " << nodeNames.at(0) << " " << nodeNames.at(1)
         << " " << vecOfStrToStr(parameters) << " \n\n";
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

    componentType = PARS_G;
    numberOfConnectedNodes = 2;
    parseToMembers(splittedToParse, name, numberOfConnectedNodes, nodeNames,
                   parameters);

    cout << "\n " << name << " " << nodeNames.at(0) << " " << nodeNames.at(1)
         << " " << vecOfStrToStr(parameters) << " \n\n";
  } else if (checkPars(toParse, PARS_H)) {
    cout << "H found.\n";

    componentType = PARS_H;
    numberOfConnectedNodes = 2;
    parseToMembers(splittedToParse, name, numberOfConnectedNodes, nodeNames,
                   parameters);

    cout << "\n " << name << " " << nodeNames.at(0) << " " << nodeNames.at(1)
         << " " << vecOfStrToStr(parameters) << " \n\n";
  } else if (checkPars(toParse, PARS_DOT)) {
    cout << ". found.\n";

    componentType = PARS_DOT;
    name = PARS_DOT;
    // cuts off the comment indicator "." = PARS_DOT
    parameters.push_back(toParse.substr(1));

    cout << vecOfStrToStr(parameters) << "\n";
  } else {
    cout << "Unknown found.\n";
  }
}

const string Component::getName() { return name; }

const string Component::getXthNodeName(unsigned int x) {
  if ((x > 0) && ((x - 1) < nodeNames.size())) {
    // cout << "\n x = " << x << " " << nodeNames.at(x - 1) << "\n";
    return nodeNames.at(x - 1);
  } else {
    return "";
  }
}

// list<string> Component::getNodeList()
//{
//  return nodeNames;
//}

// const vector<string> Component::getNodeVector() { return nodeNames; }

const vector<string> Component::getParameters() { return parameters; }

const unsigned int Component::getNumberOfConnectedNodes() {
  return numberOfConnectedNodes;
}

const string Component::getComponentType() { return componentType; }
