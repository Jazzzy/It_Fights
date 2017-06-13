//
//  EnemyCharacterController.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 16/5/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "EnemyCharacterController.hpp"
#include "SomeMath.hpp"

EnemyCharacterController::EnemyCharacterController(){
    this->attackButtonPressed = false;
    this->parryButtonPressed = false;
    this->joystickAxis = sf::Vector2f(0.0f,0.0f);
    
}


EnemyCharacterController::~EnemyCharacterController(){
    
}


bool EnemyCharacterController::isConnected(){
    return true;
}


bool EnemyCharacterController::isAttackButtonPressed(){
    return this->attackButtonPressed;
}

bool EnemyCharacterController::isParryButtonPressed(){
    return this->parryButtonPressed;
}


sf::Vector2f EnemyCharacterController::getJoystickAxisPosition(){
    return this->joystickAxis;
}

void EnemyCharacterController::setAttackButton(bool pressed){
    this->attackButtonPressed = pressed;
}

void EnemyCharacterController::setParryButton(bool pressed){
    this->parryButtonPressed = pressed;
}

void EnemyCharacterController::setJoystickPosition(sf::Vector2f vector){
    this->joystickAxis = getNormalizedVector(vector);
}

void EnemyCharacterController::setAll(bool attackButton, bool parryButton, sf::Vector2f vector){
    this->setAttackButton(attackButton);
    this->setParryButton(parryButton);
    this->setJoystickPosition(vector);
}

