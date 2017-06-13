//
//  AIActions.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 13/6/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "AIActions.hpp"
#include "PhysicsTypes.hpp"

AIActions::AIActions(EnemyCharacterController * controller){
    
    this->controller = controller;

}



AIActions::~AIActions(){

    this->controller->setAttackButton(false);
    this->controller->setParryButton(false);
    this->controller->setJoystickPosition(sf::Vector2f(0.f,0.f));
    
}

void AIActions::execute(Action action){
    
    switch(action){
        case DO_NOTHING:
        {
            this->controller->setAll(false, false, sf::Vector2f(0.f,0.f));
        }
            break;
        case MOVE_UP:
        {
            this->controller->setAll(false, false, getVectorFromDirection_4(Direction_4::UP));
        }
            break;
        case MOVE_DOWN:
        {
            this->controller->setAll(false, false, getVectorFromDirection_4(Direction_4::DOWN));
        }
            break;
        case MOVE_LEFT:
        {
            this->controller->setAll(false, false, getVectorFromDirection_4(Direction_4::LEFT));
        }
            break;
        case MOVE_RIGHT:
        {
            this->controller->setAll(false, false, getVectorFromDirection_4(Direction_4::RIGHT));
        }
            break;
        case ATTACK:
            this->controller->setAll(true, false, sf::Vector2f(0.f,0.f));
            break;
        case PARRY:
            this->controller->setAll(false, true, sf::Vector2f(0.f,0.f));
            break;
    }


}



