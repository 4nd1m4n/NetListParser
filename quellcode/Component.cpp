#include "Component.h"

Component::Component()
{
  name = "";
  parameters = "";
  numberOfConnectedNodes = 0;
  componentType = "";
}

Component::Component(string toParse)
{
  name = "";
  parameters = "";
  numberOfConnectedNodes = 0;
  componentType = "";

  parseComponent(toParse);
}

Component::~Component()
{
}

bool Component::checkPars(const string &str, const string &pars)
{
  if ((str.compare(0, 1, pars, 0, 1) == 0))
  { // || ((str.compare(0, 1, pars, 1, 1) == 0) == true)) {
    return true;
  }
  else
  {
    return false;
  }
}

void Component::parseComponent(string toParse)
{
  name = "";
  parameters = "";
  numberOfConnectedNodes = 0;
  componentType = "";

  stringstream ssToParse(toParse);

  if (checkPars(toParse, PARS_CMNT))
  {
    cout << "* found.\n";

    //ssToParse >> name >> parameters;
    name = PARS_CMNT;
    parameters = toParse.erase(0, 1);
    componentType = PARS_CMNT;

    //cout << "\n " << name << parameters << " \n\n";
  }
  else if (checkPars(toParse, PARS_R))
  {
    cout << "R found.\n";

    string nodeName1;
    string nodeName2;

    componentType = PARS_R;
    numberOfConnectedNodes = 2;
    nodeNames.reserve(numberOfConnectedNodes);
    ssToParse >> name >> nodeName1 >> nodeName2 >> parameters;
    nodeNames.push_back(nodeName1);
    nodeNames.push_back(nodeName2);

    cout << "\n " << name << " " << nodeName1 << " " << nodeName2 << " "
         << parameters << " \n\n";
  }
  else if (checkPars(toParse, PARS_L))
  {
    cout << "L found.\n";
  }
  else if (checkPars(toParse, PARS_C))
  {
    cout << "C found.\n";
  }
  else if (checkPars(toParse, PARS_D))
  {
    cout << "D found.\n";
  }
  else if (checkPars(toParse, PARS_V))
  {
    cout << "V found.\n";

    string nodeName1;
    string nodeName2;

    componentType = PARS_V;
    numberOfConnectedNodes = 2;
    nodeNames.reserve(numberOfConnectedNodes);
    ssToParse >> name >> nodeName1 >> nodeName2 >> parameters;
    nodeNames.push_back(nodeName1);
    nodeNames.push_back(nodeName2);

    cout << "\n " << name << " " << nodeName1 << " " << nodeName2 << " "
         << parameters << " \n\n";
  }
  else if (checkPars(toParse, PARS_I))
  {
    cout << "I found.\n";

    string nodeName1;
    string nodeName2;

    componentType = PARS_I;
    numberOfConnectedNodes = 2;
    nodeNames.reserve(numberOfConnectedNodes);
    ssToParse >> name >> nodeName1 >> nodeName2 >> parameters;
    nodeNames.push_back(nodeName1);
    nodeNames.push_back(nodeName2);

    cout << "\n " << name << " " << nodeName1 << " " << nodeName2 << " "
         << parameters << " \n\n";
  }
  else if (checkPars(toParse, PARS_E))
  {
    cout << "E found.\n";
  }
  else if (checkPars(toParse, PARS_F))
  {
    cout << "F found.\n";

    string nodeName1;
    string nodeName2;

    componentType = PARS_F;
    numberOfConnectedNodes = 2;
    nodeNames.reserve(numberOfConnectedNodes);
    ssToParse >> name >> nodeName1 >> nodeName2 >> parameters;
    nodeNames.push_back(nodeName1);
    nodeNames.push_back(nodeName2);

    cout << "\n " << name << " " << nodeName1 << " " << nodeName2 << " "
         << parameters << " \n\n";
  }
  else if (checkPars(toParse, PARS_G))
  {
    cout << "G found.\n";
  }
  else if (checkPars(toParse, PARS_H))
  {
    cout << "H found.\n";
  }
  else if (checkPars(toParse, PARS_DOT))
  {
    cout << ". found.\n";
  }
  else
  {
    cout << "Unknown found.\n";
  }
}

string Component::getName()
{
  return name;
}

string Component::getNodeNameX(unsigned int x)
{
  if (x < nodeNames.size())
  {
    return nodeNames.at(x);
  }
  else
  {
    return "";
  }
}

//list<string> Component::getNodeList()
//{
//  return nodeNames;
//}

vector<string> Component::getNodeVector()
{
  return nodeNames;
}

string Component::getParameters()
{
  return parameters;
}

unsigned int Component::getNumberOfConnectedNodes()
{
  return numberOfConnectedNodes;
}

string Component::getComponentType()
{
  return componentType;
}
