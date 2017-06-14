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
    
    this->currentDiscreteState = discreteState;
    
    if(discreteState.otherState.health < 3){
    
        if(getRandomBetween(0, 5) > 1){
            this->agressiveAttack();
            return;
        }else{
            this->baitAttack();
            return;
        }
        
    }
    
    
    if(discreteState.myState.health > 2){
        
        if(getRandomBetween(0, 5) > 1){
            this->agressiveAttack();
            return;
        }else{
            this->baitAttack();
            return;
        }
        
    }else{
        
        if(getRandomBetween(0, 1) == 1){
            this->deffensiveAttack();
            return;
        }else{
            this->deffensiveEscape();
            return;
        }
    }
    
}

void RuleBasedBehaviour::agressiveAttack(){
    
    if(this->currentDiscreteState.myState.position.distance == IN_RANGE && this->currentDiscreteState.myState.position.lookingAtOpponent == true ){
        
        this->actions->execute(Action::ATTACK);
        
    }else{
        
        this->moveTowardsOpponent();
        
    }
    
}

void RuleBasedBehaviour::baitAttack(){
    
    if(this->currentDiscreteState.myState.position.distance == IN_RANGE && this->currentDiscreteState.myState.position.lookingAtOpponent == true ){
        
        this->actions->execute(Action::PARRY);
        
    }else if(this->currentDiscreteState.myState.position.distance == CLOSE_TO_RANGE){
        
        this->actions->execute(Action::DO_NOTHING);
        
    }else{
        
        this->moveTowardsOpponent();
        
    }
    
}


void RuleBasedBehaviour::deffensiveAttack(){
    
    if(this->currentDiscreteState.myState.position.distance != OUT_OF_RANGE && this->currentDiscreteState.myState.position.lookingAtOpponent == false ){
        
        this->moveTowardsOpponent();
        
    }else if(this->currentDiscreteState.myState.position.distance != OUT_OF_RANGE && this->currentDiscreteState.myState.position.lookingAtOpponent == true ){
        
        this->actions->execute(Action::ATTACK);
        
    }else{
        
        this->moveAwayFromOpponent();
        
    }
    
    
}


void RuleBasedBehaviour::deffensiveEscape(){
    
        
    if(this->currentDiscreteState.myState.position.distance != OUT_OF_RANGE && this->currentDiscreteState.myState.position.lookingAtOpponent == false ){
        
        this->moveTowardsOpponent();
        
    }else if(this->currentDiscreteState.myState.position.distance != OUT_OF_RANGE && this->currentDiscreteState.myState.position.lookingAtOpponent == true ){
        
        this->actions->execute(Action::PARRY);
        
    }else{
        
        this->moveAwayFromOpponent();
        
    }
    
}




void RuleBasedBehaviour::moveTowardsOpponent(){
    switch(this->currentDiscreteState.myState.position.angle){
        case UP:
            this->actions->execute(Action::MOVE_UP);
            break;
        case DOWN:
            this->actions->execute(Action::MOVE_DOWN);
            break;
        case LEFT:
            this->actions->execute(Action::MOVE_LEFT);
            break;
        case RIGHT:
            this->actions->execute(Action::MOVE_RIGHT);
            break;
        default:
            prints("This value should not be possible");
            break;
    }
}

void RuleBasedBehaviour::moveAwayFromOpponent(){
    
    if(this->currentDiscreteState.myState.position.wallPositions == Direction_8::NONE_8){
        switch(this->currentDiscreteState.myState.position.angle){
            case UP:
                this->actions->execute(Action::MOVE_DOWN);
                break;
            case DOWN:
                this->actions->execute(Action::MOVE_UP);
                break;
            case LEFT:
                this->actions->execute(Action::MOVE_RIGHT);
                break;
            case RIGHT:
                this->actions->execute(Action::MOVE_LEFT);
                break;
            default:
                prints("This value should not be possible");
                break;
        }
    }else{  //We are near a wall
        
        switch(this->currentDiscreteState.myState.position.wallPositions){
            case UP_8:
            case UP_RIGHT_8:
                this->actions->execute(Action::MOVE_LEFT);
                break;

                
            case RIGHT_8:
            case RIGHT_DOWN_8:
                this->actions->execute(Action::MOVE_UP);
                break;

                
            case DOWN_8:
            case DOWN_LEFT_8:
                this->actions->execute(Action::MOVE_RIGHT);
                break;

                
            case LEFT_8:
            case LEFT_UP_8:
                this->actions->execute(Action::MOVE_DOWN);
                break;
      
            default:
                prints("This value should not be possible");
                break;
        }
    
    
    }
    
    

}
























