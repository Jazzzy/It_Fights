//
//  BusNode.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 27/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef BusNode_hpp
#define BusNode_hpp

#include "MessageBus.hpp"
#include <iostream>

class BusNode{
public:
    BusNode(int systemIdentifier, MessageBus *messageBus);
    ~BusNode();
    virtual void update() {};
    
protected:
    MessageBus *messageBus;
    int systemIdentifier;
    
    std::function<void (Message)> getNotifyFunc();
    
    void send(Message message);
        
    virtual void onNotify(Message message)
    {
        std::cout << "NOT IMPLEMENTED: THe onNotify function for this system is not implemented" << std::endl;
    }
    
};

#endif /* BusNode_hpp */
