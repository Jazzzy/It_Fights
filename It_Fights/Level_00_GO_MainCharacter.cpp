//
//  Level_00_GO_MainCharacter.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 22/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Level_00_GO_MainCharacter.hpp"
#include "SomeMath.hpp"
#include "Game.hpp"
extern Game game;

Level_00_GO_MainCharacter::Level_00_GO_MainCharacter(sf::Vector2f position) : Level_00_GO_BasicCharacter( position){
    
}


#define VECTOR_LENGTH_LIMIT 0.4f

void Level_00_GO_MainCharacter::update(){
    
    Level_00_GO_BasicCharacter::update();
    
    //We Listen Here for inputs from the user :D
    
    bool connected = sf::Joystick::isConnected(0);
    
    if(!connected){
        return;
    }
    
    
    float axis_x = sf::Joystick::getAxisPosition(0, sf::Joystick::X)/100.f;
    float axis_y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y)/100.f;
    
    sf::Vector2f movementVector(axis_x,axis_y);
    
    if(getVectorLength(movementVector)>1.0f){
        movementVector = getNormalizedVector(movementVector);
    }else if(getVectorLength(movementVector)>VECTOR_LENGTH_LIMIT){
    }else{
        movementVector = sf::Vector2f(0,0);
    }
        
    velocity = (movementVector*this->walkingSpeed*game.getDeltaClock()->getDeltaTime());
    
    this->lastHeading = this->calculateHeading(velocity);
    
    this->oldPosition = this->position;
    this->position += velocity;
    
}
