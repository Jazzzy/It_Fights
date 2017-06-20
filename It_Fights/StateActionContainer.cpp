//
//  StateActionContainer.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 19/6/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "StateActionContainer.hpp"


#include <cmath>
#include <iostream>
#include <fstream>
#include "DebugUtilities.hpp"


StateActionContainer& StateActionContainer::Instance(){
    if(MInstance == 0){
        MInstance = new StateActionContainer();
        std::ifstream ifs("StateAction.data");
        if(ifs){
            boost::archive::text_iarchive ia(ifs);
            // read class state from archive
            ia >> *MInstance;
            
            prints("Currently the map has [" << MInstance->getStateActionMap()->size() << "] states in it");
            
        }
    }
    
    return *MInstance;
}

StateActionContainer* StateActionContainer::MInstance = 0;

void StateActionContainer::CleanUp(){
    prints("Currently the map has [" << MInstance->getStateActionMap()->size() << "] states in it");
    
    MInstance->saveToFile();
    delete MInstance;
    MInstance = 0;
}

StateActionContainer::StateActionContainer(){
    
    
    
    atexit(&CleanUp);
}

void StateActionContainer::saveToFile(){
    
    std::ofstream ofs("StateAction.data");
    
    // save data to archive
    {
        boost::archive::text_oarchive oa(ofs);
        // write class instance to archive
        oa << (*MInstance);
        // archive and stream closed when destructors are called
    }
    
}



std::unordered_map<std::string, StateActionSituation>* StateActionContainer::getStateActionMap(){
    return &this->stateActionMap;
}

bool StateActionContainer::hasState(std::string state){
    
    return (this->stateActionMap.find(state) != this->stateActionMap.end());

}

StateActionSituation StateActionContainer::getStateActionSituationFor(std::string state){

    return (this->stateActionMap.at(state));
    
}

void StateActionContainer::putStateActionSituation(std::string state, StateActionSituation situation){
        
    this->stateActionMap[state] = situation;

}



void StateActionContainer::resetPreviousKnowledge(){
    this->stateActionMap.clear();
    this->saveToFile();
}

ActionSituation ActionSituation::getEmptyValue(){
    return ActionSituation{
        .meanDeltaFitness = 0,
        .timesExecuted = 0,
        .maxFitness = std::numeric_limits<double>::min()
    };
}

StateActionSituation StateActionSituation::getEmptyValue(){

    StateActionSituation toReturn;
    
    for(int i = 0 ; i<NumberOfActions ; i++){
        toReturn.actionArray[i] = ActionSituation::getEmptyValue();
    }
    
    return toReturn;
};





