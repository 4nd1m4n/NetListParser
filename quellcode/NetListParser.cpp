#include <iomanip>
#include <iostream>
#include <string.h>
#include <fstream>
#include <list>
#include <sys/stat.h>
#include <algorithm>

#include "Component.hpp"
#include "GlobalConsts.hpp"
#include "NodeMapper.hpp"

using namespace std;

int main(int argc, char* argv[]) {
  cout << "\nStarting LTSpice netlist parser to generate device and node "
          "terms.\n";

  string filePath;
  string outputDepth = "";
  string tempCompare = "";

  for (int i = 1; i < argc; i++) {
    if ((strcmp(argv[i], "-f") == 0) && (i < argc - 1)) {
      filePath = argv[i + 1];
      i += 2;
    } else if ((strcmp(argv[i], "-o") == 0) && (i < argc - 1)) {
      tempCompare = argv[i + 1];
      if (tempCompare.find(OUT_KIRCHHOFF) != string::npos) {
        outputDepth += OUT_KIRCHHOFF;
      }
      if (tempCompare.find(OUT_EXTENDED) != string::npos) {
        outputDepth += OUT_EXTENDED;
      }
      if (tempCompare.find(OUT_FOUND) != string::npos) {
        outputDepth += OUT_FOUND;
      }
      if (tempCompare.find(OUT_INFILE) != string::npos) {
        outputDepth += OUT_INFILE;
      }
      if (tempCompare.find("a") != string::npos) {
        outputDepth += OUT_ALL;
      }
      i += 2;
    } else if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0)) {
      cout << MSG_USAGE;
      i += 1;
      return 151;
    } else {
      filePath = argv[i];
    }
  }

  // if no output depth was specified output all
  if (outputDepth == "") {
    outputDepth = OUT_ALL;
  }

  struct stat statfile;
  if (stat(filePath.c_str(), &statfile) == 0) {
    if (statfile.st_mode & S_IFDIR) {
      // it's a directory
      cout << "Error: Path points to a directory but must point to a file "
              "instead!\n"
           << endl;
      cout << MSG_USAGE;      
      return -1;
    } else if (statfile.st_mode & S_IFREG) {
      // it's a file
      cout << "Accepted File: " << filePath << "\n";
    } else {
      // something else
      cout << "Error: File is not valid or not a real file! (Might be a "
              "link...)\n"
           << endl;
      cout << MSG_USAGE;
      return -1;
    }
  } else {
    // error
    cout << "Error: File is not valid or may not exist!\n" << endl;
    cout << MSG_USAGE;
    return -1;
  }

  ifstream netListFile(filePath.c_str());
  if (!netListFile.good()) {
    cout << "File does not exist or is otherwise invalid!\n" << endl;
    netListFile.close();
    cout << MSG_USAGE;
    return -1;
  }

  // reading file lines to memory
  // list containing file contents
  list<string> netList;
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

  if (outputDepth.find(OUT_INFILE) != string::npos) {
    for (auto const& itNL : netList) {
      lineNumber++;
      cout << setw(3) << lineNumber << ": " << itNL << "\n";
    }
  }

  list<Component> componentList;
  Component newComponent(outputDepth);

  lineNumber = 0;
  for (auto const& itNL : netList) {
    if ((outputDepth.find(OUT_FOUND) != string::npos) ||
        (outputDepth.find(OUT_EXTENDED) != string::npos)) {
      lineNumber++;
      cout << setw(3) << lineNumber << ": ";
    }

    newComponent.parseComponent(itNL);
    componentList.push_back(newComponent);
  }

  cout << endl;

  if (outputDepth.find(OUT_KIRCHHOFF) != string::npos) {
    cout << "Kirchhoff Equations: \n\n";

    NodeMapper kirchhoffNodeMap;
    kirchhoffNodeMap.mapNodesToComponentsKCL(componentList);

    cout << kirchhoffNodeMap.kirchhoffEquations();
  }

  cout << "\nNetListParser Exit.\n\n";

  return 0;
}
