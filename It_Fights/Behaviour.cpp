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

void Behaviour::threadFunction(){
    
    while(!shouldStopThread){
        
        this->observer->update();
        FightState_Discrete discreteState = this->observer->getDiscreteState();
        
        this->update(discreteState);
        
        /*
         
         If we want to update the behaviour once per a group of frames we can just check if the difference is
         bigger than the length of that frame group in the second part of the while condition.
         
         */
        while(!shouldStopThread && this->currentFrameCount==Clock::Instance().getCurrentFrameCount()){
        }
        this->currentFrameCount=Clock::Instance().getCurrentFrameCount();
        
    }
    
}
