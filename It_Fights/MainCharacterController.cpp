//
//  MainCharacterController.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 16/5/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "MainCharacterController.hpp"

MainCharacterController::MainCharacterController(){

}


MainCharacterController::~MainCharacterController(){

}


bool MainCharacterController::isConnected(){
    return sf::Joystick::isConnected(0);
}


bool MainCharacterController::isAttackButtonPressed(){
    return (sf::Joystick::isButtonPressed(0, 0));
}


sf::Vector2f MainCharacterController::getJoystickAxisPosition(){
    return sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::X)/100.f,sf::Joystick::getAxisPosition(0, sf::Joystick::Y)/100.f);
}
