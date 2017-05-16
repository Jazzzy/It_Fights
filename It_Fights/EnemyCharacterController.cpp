//
//  EnemyCharacterController.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 16/5/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "EnemyCharacterController.hpp"

EnemyCharacterController::EnemyCharacterController(){
    
}


EnemyCharacterController::~EnemyCharacterController(){
    
}


bool EnemyCharacterController::isConnected(){
    return true;
}


bool EnemyCharacterController::isAttackButtonPressed(){
    return false;
}


sf::Vector2f EnemyCharacterController::getJoystickAxisPosition(){
    return sf::Vector2f(((float)rand()-(RAND_MAX/2.f))/(float)RAND_MAX,((float)rand()-(RAND_MAX/2.f))/(float)RAND_MAX);
}
