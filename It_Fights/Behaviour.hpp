//
//  Behaviour.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 24/5/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Behaviour_hpp
#define Behaviour_hpp

#include <thread>

#include "EnemyCharacterController.hpp"
#include "AIObserver.hpp"

class AIObserver;


#define TICK_MILLIS 20

class Behaviour {
public:
    Behaviour(EnemyCharacterController* controller, AIObserver* observer);
    virtual ~Behaviour();
    virtual void update() = 0;
protected:
    EnemyCharacterController* controller;
    AIObserver* observer;
    void threadFunction();
    
    std::thread behaviourThread;
    bool stopThread;
    
};


#endif /* Behaviour_hpp */
