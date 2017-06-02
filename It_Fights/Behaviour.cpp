//
//  Behaviour.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 24/5/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Behaviour.hpp"
#include "DebugUtilities.hpp"

Behaviour::Behaviour(EnemyCharacterController* controller, AIObserver* observer){
    this->controller = controller;
    this->observer = observer;
    
    this->stopThread = false;
    
    this->behaviourThread =  std::thread( [this](){this->threadFunction();} );
    
}

Behaviour::~Behaviour(){
    
    this->stopThread = true;
    
    this->behaviourThread.join();
    
}

void Behaviour::threadFunction(){
    
    while(!stopThread){
        
        this->update();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(TICK_MILLIS));
    }
    
}
