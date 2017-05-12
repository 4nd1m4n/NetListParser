#include <iostream>
#include <iomanip>
//#include <stdio.h>
//#include <string>
#include <string.h>
#include <list>
#include <fstream>
//#include <sstream>
//#include <cctype>
//#include <ctype.h>
#include <algorithm>
#include <sys/stat.h>

#include "Component.hpp"
#include "globalConsts.hpp"

using namespace std;

// functions
bool checkPars(const string &str, const string &pars)
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
// Verlinkte Listen nutzen um die Bauteile intern zu repräsentieren
// Über die args der main Funktion Parameterübgergabe realisieren, damit man die
// Datei sampt Pfad angeben kann, die geparst werden soll.
// Parsen über case Fälle -> Regeln stehen in den PDF Datein prinzipiell sollte
// das mit sscanf gehen denkbar, dass man das auch in case Fälle packt.
// z.B. scannen des ersten Buchstaben und dann entscheiden, wie weiter gescannt
// wird; Oder gucken, wie viele Parameter maximal in einer Zeile vorkommen können
// getrennt von Leerzeichen und einfach immer die maximale Anzahl einlesen und
// dann nach Fall die sinnvollen auslesen.

/* Muss höchstwahrscheinlich nen eigenen Datentyp schreiben, die Frage ist, ob
 ich den aus strings oder schon als interne Darstellung abspeicher?
 Theoretisch brauche ich keine "besondere" Darstellung... Ich könnte alles
 per Buchstaben 'chars' abwickeln, bzw. über Konstanten Repräsentationen. */

int main(int argc, char *argv[])
{
  cout << "LTSpice netlist parser to generate device and knot terms.\n"; // << endl;

  string filePath;

  for (int i = 1; i < argc; i++)
  {
    if ((strcmp(argv[i], "-f") == 0) && (i < argc - 1))
    {
      filePath = argv[i + 1];
      i += 2;
    }
    else
    {
      filePath = argv[i];
    }
  }

  struct stat statfile;
  if (stat(filePath.c_str(), &statfile) == 0)
  {
    if (statfile.st_mode & S_IFDIR)
    {
      // it's a directory
      cout << "Error: Path points to a directory but must point to a file instead!\n"
           << endl;
      return -1;
    }
    else if (statfile.st_mode & S_IFREG)
    {
      // it's a file
      cout << "Accepted File: " << filePath << "\n";
    }
    else
    {
      // something else
      cout << "Error: File is not valid or not a real file! (Might be a link...)\n"
           << endl;
      return -1;
    }
  }
  else
  {
    // error
    cout << "Error: File is not valid or may not exist!\n"
         << endl;
    return -1;
  }

  // reading file lines to memory
  // list containing file contents
  list<string> netList;
  ifstream netListFile(filePath.c_str());
  if (!netListFile.good())
  {
    cout << "File does not exist or is otherwise invalid!\n"
         << endl;
    netListFile.close();
    return -1;
  }

  string lineContents;

  while (!netListFile.eof())
  {
    getline(netListFile, lineContents);

    //boost::algorithm::string::to_lower(lineContents);
    transform(lineContents.begin(), lineContents.end(), lineContents.begin(),
              ::tolower);

    netList.push_back(lineContents);
  }
  netListFile.close();

  // output of list contents
  unsigned int lineNumber = 0;

  for (auto const &itNL : netList)
  {
    lineNumber++;
    cout << setw(3) << lineNumber << ": " << itNL << "\n";
  }

  cout << endl;

  //list<string> deviceTermList;
  list<Component> ComponentList;
  Component newComponent;

  /*unsigned int*/ lineNumber = 0;
  for (auto const &itNL : netList)
  {
    lineNumber++;
    cout << setw(3) << lineNumber << ": ";

    //stringstream currentLine(itNL);

    newComponent.parseComponent(itNL);
    ComponentList.push_back(newComponent);

    //cout << "\nParameters: " << newComponent.getParameters() << "\n";

    /*if (checkPars(itNL, PARS_CMNT)) {
     cout << "* found.\n";
     } else if (checkPars(itNL, PARS_R)) {
     cout << "R found.\n";
     } else if (checkPars(itNL, PARS_L)) {
     cout << "L found.\n";
     } else if (checkPars(itNL, PARS_C)) {
     cout << "C found.\n";
     } else if (checkPars(itNL, PARS_D)) {
     cout << "D found.\n";
     } else if (checkPars(itNL, PARS_V)) {
     cout << "V found.\n";
     } else if (checkPars(itNL, PARS_I)) {
     cout << "I found.\n";
     } else if (checkPars(itNL, PARS_E)) {
     cout << "E found.\n";
     } else if (checkPars(itNL, PARS_F)) {
     cout << "F found.\n";
     } else if (checkPars(itNL, PARS_G)) {
     cout << "G found.\n";
     } else if (checkPars(itNL, PARS_H)) {
     cout << "H found.\n";
     } else if (checkPars(itNL, PARS_DOT)) {
     cout << ". found.\n";
     } else {
     cout << "Unknown found.\n";
     }*/
  }

  cout << "NetListParser Exit.\n\n";

  return 0;
}
