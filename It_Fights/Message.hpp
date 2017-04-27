//
//  Message.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 27/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Message_hpp
#define Message_hpp



#include <string>
#include <iostream>
#include "MessageData.h"


#define MSG_TO_EVERYONE (-1)




class Message{
public:
    Message(const std::string event);
    Message(const std::string event, const int system);
    Message(const std::string event, const int system, MessageData data);
    Message(const std::string event, MessageData data);
    bool isRelevant();
    void setRelevantForConsole(bool relevant);
    std::string getEvent();
    int getReceiverSystem();
    MessageData getData();
    
private:
    bool relevantForConsole;
    std::string stringEvent;
    MessageData data{MessageData::EMPTY,nullptr};
    int system;
};



#endif /* Message_hpp */
