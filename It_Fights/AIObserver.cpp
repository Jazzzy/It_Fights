//
//  AIObserver.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 24/5/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "AIObserver.hpp"
#include "DebugUtilities.hpp"

AIObserver::AIObserver(Level_00_GO_Characters* characters){
    this->characters = characters;
    this->deltaClock.restart();
    this->observerClock.restart();
}

AIObserver::~AIObserver(){}

FightState AIObserver::getFightState(bool doCheck){
    
    if(doCheck){
        this->updateFightState();
    }
    
    return this->currentFightState;
}

void AIObserver::updateFightState(){
    
    this->currentFightState.timeSinceLastCheck = this->deltaClock.restart().asSeconds();
    this->currentFightState.totalFightingTime = this->observerClock.getElapsedTime().asSeconds();
    
    this->currentFightState.playerState = this->getCharacterState(Character::PLAYER);
    this->currentFightState.enemyState = this->getCharacterState(Character::ENEMY);
    
}

CharacterState AIObserver::getCharacterState(Character character){

    CharacterState state;
    Level_00_GO_BasicCharacter* cptr;

    if(character == Character::PLAYER){
        cptr = this->characters->getMainCharacter();
    }else{
        cptr = this->characters->getEnemyCharacter();
    }
    
    state.health = cptr->getHealthNormalized();
    state.position = cptr->getPosition();
    state.velocity = cptr->getVelocity();
    
    if(cptr->isAttacking()){
        state.action = CharacterAction::ATTACKING;
    }else if(cptr->isParrying()){
        state.action = CharacterAction::PARRYING;
    }else if(cptr->isOnCooldown()){
        state.action = CharacterAction::COOLING_DOWN;
    }else if(state.velocity.x > 0.0f || state.velocity.y > 0.0f){
        state.action = CharacterAction::MOVING;
    }else{
        state.action = CharacterAction::STANDING;
    }
    
    return state;
}



