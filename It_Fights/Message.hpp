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

#define MSG_TO_EVERYONE -1

class Message{
public:
    Message(const std::string event);
    Message(const std::string event, const int system);
    Message(const std::string event, const int system, void * data);
    Message(const std::string event, void * data);
    bool isRelevant();
    void setRelevantForConsole(bool relevant);
    std::string getEvent();
    int getReceiverSystem();
    void * getData();
    
private:
    bool relevantForConsole;
    std::string stringEvent;
    void * data;
    int system;
};



#endif /* Message_hpp */
