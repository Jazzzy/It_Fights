//
//  Clock.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 28/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Clock.hpp"
#include <cmath>
#include <iostream>

Clock::Clock(){
    this->updateFunction = [&](){this->first20Update();};
}

Clock::~Clock(){}

#define MAX_QUEUE_SIZE 50

void Clock::setFrameSeparator(){
    this->deltaTime = this->deltaClock.restart().asSeconds();
    this->updateFunction();
}

float Clock::getDeltaTime(){
    return this->deltaTime;
}

float Clock::getMeanDeltaTime(){
    return this->meanDeltaTime;
}

unsigned int Clock::getMeanFPS(){
    return std::round(1.0f/this->meanDeltaTime);
}

void Clock::first20Update(){

        if(this->timesQueue.size()>=MAX_QUEUE_SIZE){
            this->updateFunction = [&](){this->runningUpdate();};
            return;
        }

        this->timesQueue.push_front(this->deltaTime); //Meter aqui o delta time en formato sf::Time
    
        this->meanDeltaTime = 0.0f;
    
        for(auto iter = this->timesQueue.begin() ; iter!=timesQueue.end() ; ++iter){
            this->meanDeltaTime+=(*iter);
        }
        this->meanDeltaTime=this->meanDeltaTime/this->timesQueue.size();
    
}

void Clock::runningUpdate(){
    
    int size = (int) this->timesQueue.size();
    this->timesQueue.push_front(this->deltaTime);
    this->meanDeltaTime = this->meanDeltaTime - (this->timesQueue.back()/size) + (this->deltaTime/size);
    this->timesQueue.pop_back();
    
}

