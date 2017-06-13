//
//  RuleBasedBehaviour.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 24/5/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "RuleBasedBehaviour.hpp"
#include "SomeMath.hpp"
#include "DebugUtilities.hpp"

RuleBasedBehaviour::RuleBasedBehaviour(EnemyCharacterController* controller, AIObserver* observer) : Behaviour(controller, observer){

}


RuleBasedBehaviour::~RuleBasedBehaviour(){
    
}

void RuleBasedBehaviour::update(FightState_Discrete discreteState){
    
    printv(discreteState);
    
}
