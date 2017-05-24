//
//  Behaviour.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 24/5/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Behaviour.hpp"

Behaviour::Behaviour(EnemyCharacterController* controller, AIObserver* observer){
    this->controller = controller;
    this->observer = observer;
}

Behaviour::~Behaviour(){

}
