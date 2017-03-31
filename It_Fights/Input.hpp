//
//  Input.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 28/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Input_hpp
#define Input_hpp

#include "Window.hpp"

class Input : BusNode {
public:
    Input(MessageBus * messageBus, Window *m_window);
    ~Input();
    
    void readInput();
    void update();
    
private:
    Window *m_window;
    void onNotify (Message message);
    
};

#endif /* Input_hpp */
