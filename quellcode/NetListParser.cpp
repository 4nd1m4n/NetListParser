#include <iomanip>
#include <iostream>
//#include <stdio.h>
//#include <string>
#include <string.h>
#include <fstream>
#include <list>
//#include <sstream>
//#include <cctype>
//#include <ctype.h>
#include <sys/stat.h>
#include <algorithm>

#include "Component.hpp"
#include "GlobalConsts.hpp"
#include "NodeMapper.hpp"

using namespace std;

int main(int argc, char* argv[]) {
  cout << "LTSpice netlist parser to generate device and knot terms.\n";  // <<
  // endl;

  string filePath;

  for (int i = 1; i < argc; i++) {
    if ((strcmp(argv[i], "-f") == 0) && (i < argc - 1)) {
      filePath = argv[i + 1];
      i += 2;
    } else {
      filePath = argv[i];
    }
  }

  struct stat statfile;
  if (stat(filePath.c_str(), &statfile) == 0) {
    if (statfile.st_mode & S_IFDIR) {
      // it's a directory
      cout << "Error: Path points to a directory but must point to a file "
              "instead!\n"
           << endl;
      return -1;
    } else if (statfile.st_mode & S_IFREG) {
      // it's a file
      cout << "Accepted File: " << filePath << "\n";
    } else {
      // something else
      cout << "Error: File is not valid or not a real file! (Might be a "
              "link...)\n"
           << endl;
      return -1;
    }
  } else {
    // error
    cout << "Error: File is not valid or may not exist!\n" << endl;
    return -1;
  }

  // reading file lines to memory
  // list containing file contents
  list<string> netList;
  ifstream netListFile(filePath.c_str());
  if (!netListFile.good()) {
    cout << "File does not exist or is otherwise invalid!\n" << endl;
    netListFile.close();
    return -1;
  }

  string lineContents;

  while (!netListFile.eof()) {
    getline(netListFile, lineContents);

    transform(lineContents.begin(), lineContents.end(), lineContents.begin(),
              ::tolower);

    netList.push_back(lineContents);
  }
  netListFile.close();

  // output of list contents
  unsigned int lineNumber = 0;

  for (auto const& itNL : netList) {
    lineNumber++;
    cout << setw(3) << lineNumber << ": " << itNL << "\n";
  }

  cout << endl;

  list<Component> componentList;
  Component newComponent;

  lineNumber = 0;
  for (auto const& itNL : netList) {
    lineNumber++;
    cout << setw(3) << lineNumber << ": ";

    newComponent.parseComponent(itNL);
    componentList.push_back(newComponent);
  }

  cout << endl;

  cout << "Kirchhoff Equations: \n\n";

  NodeMapper kirchhoffNodeMap;
  kirchhoffNodeMap.mapNodesToComponentsKCL(componentList);
  cout << kirchhoffNodeMap.kirchhoffEquations();

  cout << "\nNetListParser Exit.\n\n";

  return 0;
}
