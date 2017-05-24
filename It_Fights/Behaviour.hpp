//
//  Behaviour.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 24/5/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Behaviour_hpp
#define Behaviour_hpp
#include "EnemyCharacterController.hpp"
#include "AIObserver.hpp"

class AIObserver;

class Behaviour {
public:
    Behaviour(EnemyCharacterController* controller, AIObserver* observer);
    ~Behaviour();
    virtual void update() = 0;
protected:
    EnemyCharacterController* controller;
    AIObserver* observer;
    
};


#endif /* Behaviour_hpp */
