//
//  Clock.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 28/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Clock.hpp"
#include <cmath>

Clock::Clock(){}

Clock::~Clock(){}

#define MAX_QUEUE_SIZE 50

void Clock::setFrameSeparator(){
    this->deltaTime = this->deltaClock.restart();
    this->updateQueue(this->deltaTime);
}

float Clock::getDeltaTime(){
    return this->deltaTime.asSeconds();
}

float Clock::getMeanDeltaTime(){
    return this->meanDeltaTime;
}

unsigned int Clock::getMeanFPS(){
    return std::round(1.0f/this->meanDeltaTime);
}

void Clock::updateQueue(sf::Time time){

    if(this->timesQueue.size()>=MAX_QUEUE_SIZE){
        this->timesQueue.pop_back();
    }
    this->timesQueue.push_front(time);
    
    this->meanDeltaTime = 0.0f;
    
    for(auto iter = this->timesQueue.begin() ; iter!=timesQueue.end() ; ++iter){
        this->meanDeltaTime+=(*iter).asSeconds();
    }
    this->meanDeltaTime=this->meanDeltaTime/this->timesQueue.size();
    
}
