#ifndef NODEMAPPER_HPP
#define NODEMAPPER_HPP

#include <iterator>
#include <list>
#include <map>
#include <string>
#include <vector>

#include "Component.hpp"
#include "GlobalConsts.hpp"

using namespace std;

class NodeMapper {
 public:
  NodeMapper();
  ~NodeMapper();

  void mapNodesToComponentsKCL(list<Component> componentList);
  string kirchhoffEquations(void);

 protected:
 private:
  struct KirchhoffCLComponents {
    vector<Component> currentDrains;
    vector<Component> currentSources;
  };

  map<string, KirchhoffCLComponents> NodeMapKirchhoffCL;
};

#endif  // NODEMAPPER_HPP