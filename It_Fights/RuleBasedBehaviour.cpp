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

#define ATTACK_RANGE (20) //28+-

void RuleBasedBehaviour::update(){

    
    FightState state = this->observer->getFightState(true);
    
    sf::Vector2f posDiff =  state.otherState.position - state.myState.position;
    float diffMagnitude = getVectorLength(posDiff);
    
    
    this->controller->setParryButton(false);
    
    if(diffMagnitude < ATTACK_RANGE){           //If the other guy seems in range we attack
        this->controller->setAttackButton(true);
    }else{
        this->controller->setAttackButton(false);
        this->controller->setJoystickPosition(posDiff);
    }
    
    
}
