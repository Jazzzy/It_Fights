//
//  Behaviour.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 24/5/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Behaviour.hpp"
#include "DebugUtilities.hpp"
#include "Clock.hpp"

Behaviour::Behaviour(EnemyCharacterController* controller, AIObserver* observer){
    this->actions = new AIActions(controller);
    this->observer = observer;
    this->shouldStopThread = false;
    this->currentFrameCount = Clock::Instance().getCurrentFrameCount();
}

void Behaviour::startThread(){
    this->shouldStopThread = false;
    this->behaviourThread =  std::thread( [this](){this->threadFunction();} );
}

void Behaviour::stopThread(){
    this->shouldStopThread = true;
    this->behaviourThread.join();
}


Behaviour::~Behaviour(){
    delete this->actions;
}

#define WAITING_FRAMES 60

void Behaviour::threadFunction(){
    
    while(!shouldStopThread){
        
        FightState_Discrete discreteState = this->observer->getDiscreteState();
        
        this->update(discreteState);
        
        while(!shouldStopThread && ((Clock::Instance().getCurrentFrameCount() - this->currentFrameCount) < WAITING_FRAMES)){
            
            bool stateChanged = (discreteState == this->observer->getDiscreteState());
            
            if(stateChanged) break;
            
        }
        
        this->currentFrameCount=Clock::Instance().getCurrentFrameCount();
        
    }
    
}
