//
//  BusNode.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 27/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "BusNode.hpp"
#include "Systems.hpp"
#include "DebugUtilities.hpp"

BusNode::BusNode(int systemIdentifier, MessageBus *messageBus)
{
    
    this->systemIdentifier = systemIdentifier;
    this->messageBus = messageBus;
    this->messageBus->addReceiver(systemIdentifier, this->getNotifyFunc());
    
}

BusNode::~BusNode(){
    this->messageBus->removeReceiver(systemIdentifier);
}


std::function<void (Message)> BusNode::getNotifyFunc()
{
    std::function<void (Message)> messageListener = [=](Message message) -> void {
        this->onNotify(message);
    };
    return messageListener;
}

void BusNode::send(Message message)
{
    messageBus->sendMessage(message);
}

