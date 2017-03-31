//
//  Input.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 28/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Input.hpp"
#include "Systems.hpp"

Input::Input(MessageBus * messageBus, Window *m_window) : BusNode(Systems::S_Input ,messageBus) {
    this->m_window=m_window;
}


Input::~Input(){
    
}

void Input::readInput(){
    
    sf::Event event;
    Message msg_cleanup("MSG_CLEANUP");
    Message msg_close("MSG_CLOSE_WINDOW",Systems::S_Window);
    
    
    while (this->m_window->getInternalWindowRef()->pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed:
            {
                Message msg_cleanup("MSG_CLEANUP");
                msg_cleanup.setRelevantForConsole(true);
                Message msg_close("MSG_CLOSE_WINDOW",Systems::S_Window);
                msg_close.setRelevantForConsole(true);
                send(msg_cleanup);
                send(msg_close);
            }
                break;
                
            case sf::Event::Resized:
            {
                Message msg_resized("MSG_RESIZED_WINDOW",Systems::S_Window, new std::pair<int, int>(event.size.width,event.size.height));
                msg_resized.setRelevantForConsole(true);
                send(msg_resized);
            }
                break;
                
            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::BackSlash) {
                    Message msg_toggleConsole("MSG_TOGGLE_CONSOLE",Systems::S_Console);
                    msg_toggleConsole.setRelevantForConsole(true);
                    send(msg_toggleConsole);
                }
            }
                break;
                
            default:
                break;
                
                
                
        }
        
    }
    
}

void Input::update(){
    this->readInput();
    //std::cout << "Window System updating: " << std::endl;
}

void Input::onNotify (Message message){
//    std::cout << "Input System received: " << message.getEvent() << std::endl;
}
