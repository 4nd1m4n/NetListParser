#ifndef GLOBALCONSTS_HPP
#define GLOBALCONSTS_HPP

#include <string>
using namespace std;

static const string MSG_USAGE = 
  "\n"
  "NetListParser must be called with at least one parameter "
  "wich must be a file containing an expanded netlist from the "
  "LTSpice error log following the line '--- Expanded Netlist ---' "
  "to including '.end.'\n"
  "\n"
  "The filename can follow directly after the program call but can "
  "also be specified after '-f' like '-f netlistfile.exnet'\n"
  "\n"
  "It is also possible to influence the ouput with '-o' followed "
  "by a char or string of chars.\n"
  "a for output all\n"
  "i for output input file\n"
  "f for output components found\n"
  "e for output extended parameters and\n"
  "k for output of the Kirchhoffschen node terms.\n"
  "\n"
  "Example: './NetListParser.exc -o fek -f netlist.exnet' for output "
  "of components found, extended parameters and the Kirchhoffschen "
  "node terms of the netlist.exnet file in one program call.\n"
  "\n";

static const string OUT_KIRCHHOFF = "k";
static const string OUT_EXTENDED = "e";
static const string OUT_FOUND = "f";
static const string OUT_INFILE = "i";
static const string OUT_ALL = "kefi";

static const string PARS_CMNT = "*";
static const string PARS_DOT = ".";

// two nodes
static const string PARS_B = "b";
static const string PARS_R = "r";
static const string PARS_L = "l";
static const string PARS_C = "c";
static const string PARS_D = "d";
static const string PARS_V = "v";
static const string PARS_I = "i";
// two nodes but conditions attached
static const string PARS_F = "f";
static const string PARS_H = "h";
// more than two nodes
static const string PARS_E = "e";
static const string PARS_G = "g";

// all in one string that have at least 2 nodes
static const string PARS_BCDEFGHILRV = "bcdefghilrv";

#endif  // GLOBALCONSTS_HPP
