//
//  ReinforcementLearningBehaviour_1.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 19/6/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "ReinforcementLearningBehaviour_1.hpp"
#include "SomeMath.hpp"
#include "DebugUtilities.hpp"
#include "StateActionContainer.hpp"

ReinforcementLearningBehaviour_1::ReinforcementLearningBehaviour_1(EnemyCharacterController* controller, AIObserver* observer) : Behaviour(controller, observer){
    
    this->currentDiscreteState = observer->getDiscreteState();
    this->lastDiscreteState = this->currentDiscreteState;
    this->lastAction = DO_NOTHING;
    
    printv(StateActionContainer::Instance().getStateActionMap()->size());

}


ReinforcementLearningBehaviour_1::~ReinforcementLearningBehaviour_1(){
    
}

bool first = true;

void ReinforcementLearningBehaviour_1::update(FightState_Discrete discreteState){
    
    this->lastDiscreteState = this->currentDiscreteState;
    this->currentDiscreteState = discreteState;
    
    int deltaFitness = this->currentDiscreteState.fitness - this->lastDiscreteState.fitness;
    
    std::string lastStateString = lastDiscreteState.to_short_string();
    
    prints(lastStateString);
    
    /*
     
     First we update the structure regarding the last action we took to update the
     average delta fitness
     
     */
    
    if(StateActionContainer::Instance().hasState(lastStateString)){
        
        StateActionSituation sas = StateActionContainer::Instance().getStateActionSituationFor(lastStateString);
        
        ActionSituation oldSituation = sas.actionArray[this->lastAction];
        
        ActionSituation newSituation{
            .meanDeltaFitness = oldSituation.meanDeltaFitness + ((deltaFitness - oldSituation.meanDeltaFitness)/(int)(oldSituation.timesExecuted+1)),
            .timesExecuted = oldSituation.timesExecuted+1
        };
        
        sas.actionArray[this->lastAction] = newSituation;
        
        StateActionContainer::Instance().putStateActionSituation(lastStateString, sas);
        
    }else{
        
        StateActionSituation sas = StateActionSituation::getEmptyValue();
        
        ActionSituation as{
            .meanDeltaFitness = deltaFitness,
            .timesExecuted = 1
        };
        
        sas.actionArray[this->lastAction] = as;
        
        StateActionContainer::Instance().putStateActionSituation(lastStateString, sas);
    }
    
    
    /*
     
     Now we pick one action to do
     
     */
    
//    if(StateActionContainer::Instance().hasState(this->currentDiscreteState.to_short_string())){
//        
//        StateActionSituation sas = StateActionContainer::Instance().getStateActionSituationFor(this->currentDiscreteState.to_short_string());
//        
//        this->lastAction = (Action) 0;
//        
//        for(int i = 0 ; i < NumberOfActions ; i++){
//            if(sas.actionArray[this->lastAction].meanDeltaFitness < sas.actionArray[i].meanDeltaFitness){
//                this->lastAction = (Action) i;
//            }
//        }
//    }else{
    
        this->lastAction = (Action) getRandomBetween(0, 7);
    
//    }
    
    this->actions->execute(lastAction);
    
}















//    if(first){
//        StateActionContainer::Instance().resetPreviousKnowledge();
//        printv(StateActionContainer::Instance().getStateActionMap()->size());
//        first = false;
//    }

//    FightState_Discrete converted = from_short_string(discreteState.to_short_string());
//
//    printv(discreteState);
//
//    prints("UP AND DOWN SHOULD BE THE SAME BESIDES THE FITNESS\n");
//
//    printv(converted);
//
//    if((converted.myState.action != discreteState.myState.action) ||
//       (converted.myState.health != discreteState.myState.health) ||
//       (converted.myState.position.angle != discreteState.myState.position.angle) ||
//       (converted.myState.position.distance != discreteState.myState.position.distance) ||
//       (converted.myState.position.lookingAtOpponent != discreteState.myState.position.lookingAtOpponent) ||
//       (converted.myState.position.wallPositions != discreteState.myState.position.wallPositions) ||
//       (converted.otherState.action != discreteState.otherState.action) ||
//       (converted.otherState.health != discreteState.otherState.health)
//       ){
//        prints("IT FAILED");
//        exit(2);
//    }



