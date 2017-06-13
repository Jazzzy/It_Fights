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
#include "AIActions.hpp"

class AIObserver;
struct FightState_Discrete;

#define TICK_MILLIS 20

class Behaviour {
public:
    Behaviour(EnemyCharacterController* controller, AIObserver* observer);
    virtual ~Behaviour();
    virtual void update(FightState_Discrete discreteState) = 0;
    void startThread();
    void stopThread();
protected:
    AIActions* actions;
    AIObserver* observer;
    void threadFunction();
    
    std::thread behaviourThread;
    bool shouldStopThread;
    unsigned long currentFrameCount;
    
};


#endif /* Behaviour_hpp */
