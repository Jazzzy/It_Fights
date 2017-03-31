//
//  Event.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 28/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Event.hpp"


Event::Event(sf::Event event) : internalEvent(event){

    
}

Event::~Event(){

}

sf::Event Event::getEvent(){
    return this->internalEvent;
}
