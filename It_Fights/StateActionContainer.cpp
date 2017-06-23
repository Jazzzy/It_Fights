//
//  StateActionContainer.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 19/6/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "StateActionContainer.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include "DebugUtilities.hpp"
#include "ResourcePath.hpp"

bool canAccessFiles = true;

StateActionContainer& StateActionContainer::Instance() {
  if (MInstance == 0) {
    MInstance = new StateActionContainer();
    std::ifstream ifs("./Active_StateAction.data");
    if (ifs) {
      boost::archive::text_iarchive ia(ifs);
      // read class state from archive
      ia >> *MInstance;

      prints("Currently the map has [" << MInstance->getStateActionMap()->size()
                                       << "] states in it");
      canAccessFiles = true;
    }else{
      canAccessFiles = false;
        
      std::ifstream ifs(resourcePath() + "Saved_StateAction.data");

      boost::archive::text_iarchive ia(ifs);
      // read class state from archive
      ia >> *MInstance;
        
      prints("Currently the map has [" << MInstance->getStateActionMap()->size()
             << "] states in it");
        
    }
  }

  return *MInstance;
}

StateActionContainer* StateActionContainer::MInstance = 0;

std::shared_mutex M_mutex;

void StateActionContainer::CleanUp() {
  std::unique_lock<std::shared_mutex> lock(M_mutex);

  if (MInstance == 0) return;

  prints("Currently the map has [" << MInstance->getStateActionMap()->size()
                                   << "] states in it");

  MInstance->saveToFile();
  delete MInstance;
  MInstance = 0;
}

StateActionContainer::StateActionContainer() { atexit(&CleanUp); }

void StateActionContainer::saveToFile() {
  std::unique_lock<std::shared_mutex> lock(MInstance->mutex);
  if(!canAccessFiles) return;
    
  std::ofstream ofs("./Active_StateAction.data");
  // save data to archive
  {
    boost::archive::text_oarchive oa(ofs);
    // write class instance to archive
    oa << (*MInstance);
    // archive and stream closed when destructors are called
  }
}

std::unordered_map<std::string, StateActionSituation>*
StateActionContainer::getStateActionMap() {
  return &this->stateActionMap;
}

bool StateActionContainer::hasState(std::string state) {
  std::shared_lock<std::shared_mutex> lock(this->mutex);
  return (this->stateActionMap.find(state) != this->stateActionMap.end());
}

StateActionSituation StateActionContainer::getStateActionSituationFor(
    std::string state) {
  std::shared_lock<std::shared_mutex> lock(this->mutex);
  return (this->stateActionMap.at(state));
}

void StateActionContainer::putStateActionSituation(
    std::string state, StateActionSituation situation) {
  std::unique_lock<std::shared_mutex> lock(this->mutex);
  this->stateActionMap[state] = situation;
}

void StateActionContainer::resetPreviousKnowledge() {
  std::unique_lock<std::shared_mutex> lock(this->mutex);
  this->stateActionMap.clear();
  this->saveToFile();
}

ActionSituation ActionSituation::getEmptyValue() {
  return ActionSituation{.meanDeltaFitness = 0,
                         .timesExecuted = 0,
                         .maxFitness = std::numeric_limits<double>::min()};
}

StateActionSituation StateActionSituation::getEmptyValue() {
  StateActionSituation toReturn;

  for (int i = 0; i < NumberOfActions; i++) {
    toReturn.actionArray[i] = ActionSituation::getEmptyValue();
  }

  return toReturn;
};
