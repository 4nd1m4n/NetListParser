#include "Component.hpp"

Component::Component() {
  name = "";
  nodeNames.clear();
  parameters.clear();
  parameterMap.clear();
  numberOfConnectedNodes = 0;
  componentType = "";
}

Component::Component(string toParse) {
  name = "";
  nodeNames.clear();
  parameters.clear();
  parameterMap.clear();
  numberOfConnectedNodes = 0;
  componentType = "";

  parseComponent(toParse);
}

Component::~Component() {}

void Component::mapFirstComponentValue(const string mapKey,
                                       const vector<string> &params,
                                       map<string, string> &paramMap) {
  double value = 0;
  char *pEnd;

  value = strtod((*params.begin()).c_str(), &pEnd);

  // if pEnd does not point to the end of the string
  if (*pEnd != '\0') {
    switch (*pEnd) {
      case 'f':
        value *= 1.0e-15;
        break;
      case 'p':
        value *= 1.0e-12;
        break;
      case 'n':
        value *= 1.0e-9;
        break;
      case 'u':
        value *= 1.0e-6;
        break;
      case 'm':
        if ((*(pEnd + 1) == 'e') && (*(pEnd + 2) == 'g')) {
          value *= 1.0e+6;
        } else {
          value *= 1.0e-3;
        }
        break;
      case 'k':
        value *= 1.0e+3;
        break;
      case 'g':
        value *= 1.0e+9;
        break;
      case 't':
        value *= 1.0e+12;
        break;
      default:  // nothing
        break;
    }
  }

  paramMap[mapKey] = to_string(value);
}

void Component::checkStringForExpressions(const string &str,
                                          const vector<string> &exp,
                                          map<string, string> &paramMap) {
  map<unsigned int, string> expPositions;

  for (auto expIt = exp.begin(); expIt != exp.end(); expIt++) {
    if (str.length() >= (*expIt).length()) {
      size_t found = str.find(*expIt);
      if (found != string::npos) {
        expPositions[str.find(*expIt)] = *expIt;
      }
    }
  }
  for (auto expPosIt = expPositions.begin(); expPosIt != expPositions.end();
       expPosIt++) {
    unsigned int start = (*expPosIt).first + (*expPosIt).second.length();
    unsigned int length = (*next(expPosIt, 1)).first - start;
    paramMap[(*expPosIt).second] = str.substr(start, length);
  }
}

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
  nodeNames.clear();
  parameters.clear();
  parameterMap.clear();
  numberOfConnectedNodes = 0;
  componentType = "";

  vector<string> splittedToParse = split(toParse, ' ');

  if (checkPars(toParse, PARS_CMNT)) {
    cout << "* found.\n";

    componentType = PARS_CMNT;
    name = PARS_CMNT;
    // cuts off the comment indicator "*" = PARS_CMNT
    parameters.push_back(toParse.substr(1));

    cout << vecOfStrToStr(parameters) << "\n";

  } else if (checkPars(toParse, PARS_B)) {
    cout << "B found.\n";

    componentType = PARS_B;
    numberOfConnectedNodes = 2;
    parseToMembers(splittedToParse, name, numberOfConnectedNodes, nodeNames,
                   parameters);

    // string params = vecOfStrToStr(parameters);
    // vector<string> expressions = split("i i= v v=", ' ');
    // parameterMap = checkStringForExpressions(params, expressions);
    checkStringForExpressions(vecOfStrToStr(parameters), split("i= v=", ' '),
                              parameterMap);

  } else if (checkPars(toParse, PARS_R)) {
    cout << "R found.\n";

    componentType = PARS_R;
    numberOfConnectedNodes = 2;
    parseToMembers(splittedToParse, name, numberOfConnectedNodes, nodeNames,
                   parameters);

    mapFirstComponentValue("_resistance", parameters, parameterMap);

  } else if (checkPars(toParse, PARS_L)) {
    cout << "L found.\n";

    componentType = PARS_L;
    numberOfConnectedNodes = 2;
    parseToMembers(splittedToParse, name, numberOfConnectedNodes, nodeNames,
                   parameters);

    mapFirstComponentValue("_inductance", parameters, parameterMap);

  } else if (checkPars(toParse, PARS_C)) {
    cout << "C found.\n";

    componentType = PARS_C;
    numberOfConnectedNodes = 2;
    parseToMembers(splittedToParse, name, numberOfConnectedNodes, nodeNames,
                   parameters);

    mapFirstComponentValue("_capacitance", parameters, parameterMap);

  } else if (checkPars(toParse, PARS_D)) {
    cout << "D found.\n";

    componentType = PARS_D;
    numberOfConnectedNodes = 2;
    parseToMembers(splittedToParse, name, numberOfConnectedNodes, nodeNames,
                   parameters);

  } else if (checkPars(toParse, PARS_V)) {
    cout << "V found.\n";

    componentType = PARS_V;
    numberOfConnectedNodes = 2;
    parseToMembers(splittedToParse, name, numberOfConnectedNodes, nodeNames,
                   parameters);

    mapFirstComponentValue("_voltage", parameters, parameterMap);
    checkStringForExpressions(vecOfStrToStr(parameters), split("ac ac=", ' '),
                              parameterMap);

  } else if (checkPars(toParse, PARS_I)) {
    cout << "I found.\n";

    componentType = PARS_I;
    numberOfConnectedNodes = 2;
    parseToMembers(splittedToParse, name, numberOfConnectedNodes, nodeNames,
                   parameters);

    mapFirstComponentValue("_current", parameters, parameterMap);

  } else if (checkPars(toParse, PARS_E)) {
    cout << "E found.\n";

    componentType = PARS_E;
    numberOfConnectedNodes = 4;
    parseToMembers(splittedToParse, name, numberOfConnectedNodes, nodeNames,
                   parameters);

    mapFirstComponentValue("_gain", parameters, parameterMap);
    checkStringForExpressions(vecOfStrToStr(parameters),
                              split("value value=", ' '), parameterMap);

  } else if (checkPars(toParse, PARS_F)) {
    cout << "F found.\n";

    // F Ausgabe ist momentan falsch, da vnam fehlt.

    componentType = PARS_F;
    numberOfConnectedNodes = 2;
    parseToMembers(splittedToParse, name, numberOfConnectedNodes, nodeNames,
                   parameters);

    if (!parameters.empty()) {
      string vName = parameters.at(0);
      parameters.erase(parameters.begin());
      parameterMap["_vnam"] = vName;
    }
    mapFirstComponentValue("_gain", parameters, parameterMap);
    checkStringForExpressions(vecOfStrToStr(parameters),
                              split("value value=", ' '), parameterMap);

  } else if (checkPars(toParse, PARS_G)) {
    cout << "G found.\n";

    componentType = PARS_G;
    numberOfConnectedNodes = 4;
    parseToMembers(splittedToParse, name, numberOfConnectedNodes, nodeNames,
                   parameters);

    mapFirstComponentValue("_gain", parameters, parameterMap);
    checkStringForExpressions(vecOfStrToStr(parameters),
                              split("value value=", ' '), parameterMap);

  } else if (checkPars(toParse, PARS_H)) {
    cout << "H found.\n";

    componentType = PARS_H;
    numberOfConnectedNodes = 2;
    parseToMembers(splittedToParse, name, numberOfConnectedNodes, nodeNames,
                   parameters);

    if (!parameters.empty()) {
      string vName = parameters.at(0);
      parameters.erase(parameters.begin());
      parameterMap["_vnam"] = vName;
    }
    mapFirstComponentValue("_transresistance", parameters, parameterMap);
    checkStringForExpressions(vecOfStrToStr(parameters),
                              split("value value=", ' '), parameterMap);

  } else if (checkPars(toParse, PARS_DOT)) {
    cout << ". found.\n";

    componentType = PARS_DOT;
    name = PARS_DOT;
    // cuts off the comment indicator "." = PARS_DOT
    parameters.push_back(toParse.substr(1));

  } else {
    cout << "Unknown found.\n";
  }

  // Output every parsed component
  cout << /*"\n" <<*/ name << " ";
  for (auto it : nodeNames) {
    cout << it << " ";
  }

  // will output the name in _vnam for f and h to complete the output line
  auto iter = parameterMap.find("_vnam");
  if (iter != parameterMap.end()) {
    cout << iter->second << " ";
  }

  cout << vecOfStrToStr(parameters) << "\n" << mapToStr(parameterMap) << "\n";
}

const string Component::getName() { return name; }

const string Component::getXthNodeName(unsigned int x) {
  if ((x > 0) && ((x - 1) < nodeNames.size())) {
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
