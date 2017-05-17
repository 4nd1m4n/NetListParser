#include "NodeMapper.hpp"
#include "Component.hpp"

NodeMapper::NodeMapper() {}

NodeMapper::~NodeMapper() {}

void NodeMapper::mapNodesToComponentsKCL(list<Component> componentList) {
  map<string, KirchhoffCLComponents>::iterator itMap;
  KirchhoffCLComponents editedNodeMapKirchhoffCL;

  for (auto itList = componentList.begin(); itList != componentList.end();
       itList++) {
    if (Component::checkPars(itList->getComponentType(), PARS_CDEFGHILRV)) {
      // get first node of current iterated component which is the current drain
      // of the component
      editedNodeMapKirchhoffCL.currentDrains.clear();
      editedNodeMapKirchhoffCL.currentSources.clear();

      string drainNodeName = itList->getXthNodeName(1);
      itMap = this->NodeMapKirchhoffCL.find(drainNodeName);
      // If node name already in map
      if (itMap != this->NodeMapKirchhoffCL.end()) {
        // editedNodeMapKirchhoffCL = itMap->second;
        editedNodeMapKirchhoffCL = this->NodeMapKirchhoffCL[drainNodeName];
        editedNodeMapKirchhoffCL.currentDrains.push_back(*itList);
        this->NodeMapKirchhoffCL[drainNodeName] = editedNodeMapKirchhoffCL;
      } else {
        editedNodeMapKirchhoffCL.currentDrains.push_back(*itList);
        this->NodeMapKirchhoffCL[drainNodeName] = editedNodeMapKirchhoffCL;
      }

      editedNodeMapKirchhoffCL.currentDrains.clear();
      editedNodeMapKirchhoffCL.currentSources.clear();

      string sourceNodeName = itList->getXthNodeName(2);
      itMap = this->NodeMapKirchhoffCL.find(sourceNodeName);
      // If node name already in map
      if (itMap != NodeMapKirchhoffCL.end()) {
        editedNodeMapKirchhoffCL = itMap->second;
        editedNodeMapKirchhoffCL.currentSources.push_back(*itList);
        NodeMapKirchhoffCL[sourceNodeName] = editedNodeMapKirchhoffCL;
      } else {
        editedNodeMapKirchhoffCL.currentSources.push_back(*itList);
        NodeMapKirchhoffCL[sourceNodeName] = editedNodeMapKirchhoffCL;
      }
    }
  }
}

string NodeMapper::kirchhoffEquations(void) {
  string concatKirchhoffEquations = "";

  for (auto& itMap : this->NodeMapKirchhoffCL) {
    concatKirchhoffEquations += itMap.first + ": 0 =";
    for (auto& itVec : itMap.second.currentDrains) {
      concatKirchhoffEquations += " - I(" + itVec.getName() + ")";
    }
    for (auto& itVec : itMap.second.currentSources) {
      concatKirchhoffEquations += " + I(" + itVec.getName() + ")";
    }
    concatKirchhoffEquations += "\n";
  }

  return concatKirchhoffEquations;
}