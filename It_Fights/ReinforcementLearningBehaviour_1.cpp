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

ReinforcementLearningBehaviour_1::ReinforcementLearningBehaviour_1(EnemyCharacterController* controller, AIObserver* observer) : Behaviour(controller, observer){
    
    this->currentDiscreteState = observer->getDiscreteState();
    this->lastDiscreteState = this->currentDiscreteState;
    this->lastAction = DO_NOTHING;
        
}


ReinforcementLearningBehaviour_1::~ReinforcementLearningBehaviour_1(){
    
}

bool first = true;

void ReinforcementLearningBehaviour_1::update(FightState_Discrete discreteState){
    
    this->lastDiscreteState = this->currentDiscreteState;
    this->currentDiscreteState = discreteState;
    
    double deltaFitness = static_cast<double>(this->currentDiscreteState.fitness) - static_cast<double>(this->lastDiscreteState.fitness);
  
    std::string lastStateString = lastDiscreteState.to_short_string();
    
    /*
     
     First we update the structure regarding the last action we took to update the
     average delta fitness
     
     */
    
    if(StateActionContainer::Instance().hasState(lastStateString)){
        
        StateActionSituation sas = StateActionContainer::Instance().getStateActionSituationFor(lastStateString);
        
        ActionSituation oldSituation = sas.actionArray[this->lastAction];
        
        double auxMaxFitness = (static_cast<double>(oldSituation.maxFitness) > deltaFitness) ? static_cast<double>(oldSituation.maxFitness) : static_cast<double>(deltaFitness);
        
        ActionSituation newSituation{
            .maxFitness = auxMaxFitness,
            .meanDeltaFitness = (double)oldSituation.meanDeltaFitness + (double)(((double)deltaFitness - oldSituation.meanDeltaFitness)/(double)(oldSituation.timesExecuted+1)),
            .timesExecuted = oldSituation.timesExecuted+1
        };
        
        sas.actionArray[this->lastAction] = newSituation;
        
        
        StateActionContainer::Instance().putStateActionSituation(lastDiscreteState.to_short_string(), sas);
        
    }else{
        
        StateActionSituation sas = StateActionSituation::getEmptyValue();
        
        ActionSituation as{
            .maxFitness = deltaFitness,
            .meanDeltaFitness = deltaFitness,
            .timesExecuted = 1
        };
        
        sas.actionArray[this->lastAction] = as;
        
        StateActionContainer::Instance().putStateActionSituation(lastDiscreteState.to_short_string(), sas);
    }
    
    
    /*
     
     Now we pick one action to do with:
     
     https://en.wikipedia.org/wiki/Softmax_function#Reinforcement_learning
     
     */
    
    if(StateActionContainer::Instance().hasState(this->currentDiscreteState.to_short_string())){
        
        StateActionSituation sas = StateActionContainer::Instance().getStateActionSituationFor(this->currentDiscreteState.to_short_string());
        
        if(((double) rand() / (RAND_MAX)) > EPSILON){
            
            this->lastAction = (Action) 0;
            
            for(int i = 0 ; i < NumberOfActions ; i++){
                
                //prints("FOR STATE: " << this->currentDiscreteState.to_short_string() << ", ACTION [" << i << "]: MAX_FITNESS [" << sas.actionArray[i].maxFitness << "] AVERAGE_FITNESS [" << sas.actionArray[i].meanDeltaFitness << "]");
                
                if(this->getActionSituationWeigth(sas.actionArray[this->lastAction]) < this->getActionSituationWeigth(sas.actionArray[i])){
                    this->lastAction = (Action) i;
                }
            }
            
        }else{
            
            this->lastAction = (Action) getRandomBetween(0, 6);
            
        }
    }else{
        
        this->lastAction = (Action) getRandomBetween(0, 6);
        
    }
    
    this->actions->execute(lastAction);
    
}


#define MAX_FITNESS_WEIGTH (0.3f)
#define AVG_FITNESS_WEIGTH (0.7f)

double ReinforcementLearningBehaviour_1::getActionSituationWeigth(ActionSituation as){
    return ((double)as.maxFitness * MAX_FITNESS_WEIGTH + (double)as.meanDeltaFitness * AVG_FITNESS_WEIGTH);
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



