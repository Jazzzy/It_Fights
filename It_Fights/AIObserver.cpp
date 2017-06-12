//
//  AIObserver.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 24/5/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "AIObserver.hpp"
#include "DebugUtilities.hpp"
#include "SomeMath.hpp"

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
    }else if(fabs(state.velocity.x) > 0.0f || fabs(state.velocity.y) > 0.0f){
        state.action = CharacterAction::MOVING;
    }else{
        state.action = CharacterAction::STANDING;
    }
    
    return state;
}


short AIObserver::discretizeHealth(float health , short divisions){
    health = health * 100;
    float fdiscreteHealth = health / (float)divisions;
    return static_cast <short> (ceil(fdiscreteHealth));
}


#define HEALTH_DIVISION (20)
#define ON_RANGE_DIST (20)
#define CLOSE_TO_RANGE_DIST (30)

#define WALL_X_INF (110)
#define WALL_X_SUP (290)
#define WALL_Y_INF (75)
#define WALL_Y_SUP (223)

MyCharacterState_Discrete AIObserver::discretizeMyCharacter(FightState continuousState){

    MyCharacterState_Discrete discreteState;
    
    discreteState.health = discretizeHealth(continuousState.myState.health, HEALTH_DIVISION);
    discreteState.action = continuousState.myState.action;
    

    Position_Discrete discretePosition;
    {
        sf::Vector2f vectorDistance = continuousState.otherState.position - continuousState.myState.position;
        
        float distance = getVectorLength(vectorDistance);
        if(distance <= ON_RANGE_DIST){
            discretePosition.distance = Distance_Discrete::IN_RANGE;
        }else if(distance <= CLOSE_TO_RANGE_DIST){
            discretePosition.distance = Distance_Discrete::CLOSE_TO_RANGE;
        }else{
            discretePosition.distance = Distance_Discrete::OUT_OF_RANGE;
        }
        
        discretePosition.angle = getDirection_8FromVector(getNormalizedVector(vectorDistance));
    
//        discretePosition.wallPositions;
        
        if(continuousState.myState.position.x <= WALL_X_INF){   //Touching left wall
            
            if(continuousState.myState.position.y <= WALL_Y_INF){       //And also the top wall
            
                discretePosition.wallPositions = Direction_8::LEFT_UP_8;
                
            }else if(continuousState.myState.position.y >= WALL_Y_SUP){ //And also the bottom wall
            
                discretePosition.wallPositions = Direction_8::DOWN_LEFT_8;
                
            }else{                                                      //And only the left wall
                
                discretePosition.wallPositions = Direction_8::LEFT_8;
            
            }
        
        }else if(continuousState.myState.position.x >= WALL_X_SUP){ //Touching right wall
            
            if(continuousState.myState.position.y <= WALL_Y_INF){       //And also the top wall
                
                discretePosition.wallPositions = Direction_8::UP_RIGHT_8;
                
            }else if(continuousState.myState.position.y >= WALL_Y_SUP){ //And also the bottom wall
                
                discretePosition.wallPositions = Direction_8::RIGHT_DOWN_8;
                
            }else{                                                      //And only the right wall
        
                discretePosition.wallPositions = Direction_8::RIGHT_8;
                
            }
            
        
        }else{  //Touching neither the left or right walls
        
            if(continuousState.myState.position.y <= WALL_Y_INF){       //Just top wall
                
                discretePosition.wallPositions = Direction_8::UP_8;
                
            }else if(continuousState.myState.position.y >= WALL_Y_SUP){ //Just the bottom wall
                
                discretePosition.wallPositions = Direction_8::DOWN_8;
                
            }else{                                                      //Touching no walls
                
                discretePosition.wallPositions = Direction_8::NONE_8;
                
            }
        }
    }
    
    discreteState.position = discretePosition;
    
    return discreteState;
}


OtherCharacterState_Discrete AIObserver::discretizeOtherCharacter(CharacterState characterState){

    OtherCharacterState_Discrete discreteState;
    
    discreteState.health = discretizeHealth(characterState.health, HEALTH_DIVISION);
    discreteState.action = characterState.action;
    
    return discreteState;
}


FightState_Discrete AIObserver::discretizeState(FightState continuousState){

    FightState_Discrete discreteState{
        .myState = (discretizeMyCharacter(continuousState)),
        .otherState = (discretizeOtherCharacter(continuousState.otherState)),
    };
    
    return discreteState;
    
}


std::ostream& operator<<(std::ostream& os, const FightState_Discrete& state){
    
    return os << "My Health: " << state.myState.health << std::endl <<
                    "Distance: " << (short)state.myState.position.distance << std::endl <<
                    "Angle: " << (short)state.myState.position.angle << std::endl <<
                    "Walls: " << (short)state.myState.position.wallPositions << std::endl <<
                    "My Action: " << state.myState.action << std::endl <<
                    "His health: " << state.otherState.health << std::endl <<
                    "His Action: " << state.otherState.action << std::endl;
    
}

















