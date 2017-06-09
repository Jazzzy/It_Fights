//
//  AIObserver.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 24/5/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "AIObserver.hpp"
#include "DebugUtilities.hpp"

AIObserver::AIObserver(Level_00_GO_Characters* characters, Position position){
    this->characters = characters;
    this->deltaClock.restart();
    this->observerClock.restart();
    this->playerPosition = position;
}

AIObserver::~AIObserver(){}

FightState AIObserver::getFightState(bool doCheck){
    
    if(doCheck){
        this->updateFightState();
    }
    
    return this->currentFightState;
}

Position AIObserver::getPlayer1_2(){
    return (Position)this->playerPosition;
}

void AIObserver::updateFightState(){
    
    this->currentFightState.timeSinceLastCheck = this->deltaClock.restart().asSeconds();
    this->currentFightState.totalFightingTime = this->observerClock.getElapsedTime().asSeconds();
    
    this->currentFightState.myState = this->getCharacterState(Character::MYSELF);
    this->currentFightState.otherState = this->getCharacterState(Character::OTHER);
    
}

CharacterState AIObserver::getCharacterState(Character character){

    CharacterState state;
    Level_00_GO_BasicCharacter* cptr = nullptr;

    
    if(this->playerPosition == Position::PLAYER_1){
        if(character == Character::MYSELF){
            cptr = this->characters->getCharacter_1();
        }else{
            cptr = this->characters->getCharacter_2();
        }
    }else{
        if(character == Character::MYSELF){
            cptr = this->characters->getCharacter_2();
        }else{
            cptr = this->characters->getCharacter_1();
        }
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



