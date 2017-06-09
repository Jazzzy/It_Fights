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
    this->controller = controller;
    this->observer = observer;
    this->shouldStopThread = false;
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
    
}

void Behaviour::threadFunction(){
    
    while(!shouldStopThread){
        
        this->update();
        
        if(Clock::Instance().getTimeScale() <= 1.f)
            std::this_thread::sleep_for(std::chrono::milliseconds((TICK_MILLIS)));
        
    }
    
}
