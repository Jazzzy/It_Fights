//
//  MessageBus.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 27/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef MessageBus_hpp
#define MessageBus_hpp

#include <functional>
#include <unordered_map>
#include <queue>



#include "Message.hpp"


class MessageBus{
    
public:
    MessageBus();
    ~MessageBus(){}
    
    void notify();
    void addReceiver(int systemID, std::function<void (Message)> newReceiver);
    void removeReceiver(int systemID);
    
    void sendMessage(Message message);
    
private:
    std::unordered_map<int, std::function<void (Message)>> receiverMap;
    std::vector< std::pair<int, std::function<void (Message)>>> receiverVector;
    std::queue<Message> messageQueue;
    std::function<void (Message)> consoleReceiver;
    
};



#endif /* MessageBus_hpp */
