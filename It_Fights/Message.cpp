//
//  Message.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 27/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//


#include "Message.hpp"

Message::Message(const std::string event){
    this->system = MSG_TO_EVERYONE;
    this->stringEvent=event;
    this->data = nullptr;
    this->relevantForConsole = false;
}

Message::Message(const std::string event, const int system){
    this->system = system;
    this->stringEvent=event;
    this->data=nullptr;
    this->relevantForConsole = false;
}

Message::Message(const std::string event, const int system, void * data){
    this->system = system;
    this->stringEvent=event;
    this->data=data;
    this->relevantForConsole = false;
}

Message::Message(const std::string event, void * data){
    this->system = MSG_TO_EVERYONE;
    this->stringEvent=event;
    this->data = data;
    this->relevantForConsole = false;
}

bool Message::isRelevant(){
    return this->relevantForConsole;
}

void Message::setRelevantForConsole(bool relevant){
    this->relevantForConsole = relevant;
}

std::string Message::getEvent(){
    return this->stringEvent;
}

int Message::getReceiverSystem(){
    return this->system;
}

void * Message::getData(){
    return this->data;
}

