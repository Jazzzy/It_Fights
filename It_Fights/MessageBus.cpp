//
//  MessageBus.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 27/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//


#include <algorithm>
#include <iostream>


#include "MessageBus.hpp"
#include "Systems.hpp"
#include "DebugUtilities.hpp"


MessageBus::MessageBus(){
    //By default the function for the scene is empty :D
    receiverMap[Systems::S_CurrentScene] = [=](Message message) -> void {};
}

void MessageBus::notify(){
    while(!messageQueue.empty()) {
        Message message = messageQueue.front();
        
        if(message.isRelevant()){
            std::string * strForConsole = new std::string("Message for System [" + std::to_string(message.getReceiverSystem()) + "] that says [" + message.getEvent() + "]");
            MessageData messageData = {MessageData::STRING_PTR,strForConsole};
            
            Message messageForConsole("CONSOLE_SHOW_MSG", Systems::S_Console, messageData);
            this->consoleReceiver(messageForConsole);
        }
        
        if(message.getReceiverSystem()==MSG_TO_EVERYONE){
            for (auto iter = receiverVector.begin(); iter != receiverVector.end(); iter++) {
                (*iter).second(message);
            }
            receiverMap[Systems::S_CurrentScene](message);
        }else{
            (receiverMap[message.getReceiverSystem()])(message);
        }
        
        messageQueue.pop();
    }
}

void MessageBus::addReceiver(int systemID, std::function<void (Message)> newReceiver){
    
    if(systemID == Systems::S_Console){
        this->consoleReceiver = newReceiver;
    }
    
    receiverMap[systemID] = newReceiver;
    this->receiverVector.push_back(std::make_pair(systemID, newReceiver));
}


void MessageBus::removeReceiver(int systemID){
    
    
    for (auto iter = receiverVector.begin(); iter != receiverVector.end(); ) {
        if ((*iter).first == systemID)
            iter = receiverVector.erase(iter);
        else
            ++iter;
    }
    
}

void MessageBus::sendMessage(Message message){
    //    std::cout << "Message received in Bus: " << message.getEvent() << std::endl;
    messageQueue.push(message);
}

