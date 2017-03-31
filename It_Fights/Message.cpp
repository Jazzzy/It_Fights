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
    this->data.type = MessageData::EMPTY;
    this->relevantForConsole = false;
}

Message::Message(const std::string event, const int system){
    this->system = system;
    this->stringEvent=event;
    this->data.type = MessageData::EMPTY;
    this->relevantForConsole = false;
}

Message::Message(const std::string event, const int system, MessageData data){
    this->system = system;
    this->stringEvent=event;
    this->data = data;
    this->relevantForConsole = false;
}

Message::Message(const std::string event, MessageData data){
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

MessageData Message::getData(){
    return this->data;
}

