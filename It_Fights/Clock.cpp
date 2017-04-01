//
//  Clock.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 28/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Clock.hpp"

Clock::Clock(){}

Clock::~Clock(){}

void Clock::setFrameSeparator(){
    this->deltaTime = this->deltaClock.restart();
}

float Clock::getDeltaTime(){
    return this->deltaTime.asSeconds();
}
