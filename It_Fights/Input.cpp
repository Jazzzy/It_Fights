//
//  Input.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 28/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Input.hpp"
#include "Systems.hpp"
#include "Game.hpp"
#include "DebugUtilities.hpp"

extern Game game;

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
                PairI intPair{.x =  static_cast<int>(event.size.width), .y =  static_cast<int>(event.size.height)};
                MessageData pairData{MessageData::PAIR_OF_INTS, .intPair = intPair };
                Message msg_resized("MSG_RESIZED_WINDOW",Systems::S_Window, pairData);
                msg_resized.setRelevantForConsole(true);
                send(msg_resized);
            }
                break;
                
            case sf::Event::TextEntered:
            {
                if(game.isConsoleOpen()){ //If the console is open then the key should go to it
                    if (event.text.unicode < 128 && event.text.unicode > 31 && event.text.unicode != '\\' ){
                        Message msg_keyForConsole("MSG_CONSOLE_KEYCHAR",Systems::S_Console, MessageData{MessageData::CHARACTER, .character = static_cast<char>(event.text.unicode)});
                        send(msg_keyForConsole);
                    }
                    break;
                }else{
                    //Other text stuff
                }
            }
                
            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::BackSlash) {
                    Message msg_toggleConsole("MSG_TOGGLE_CONSOLE",Systems::S_Console);
                    send(msg_toggleConsole);
                }else{  //The key is not for opening or closing the console so we should deal with it
                    if(game.isConsoleOpen()){ //If the console is open then the key should go to it
                        Message msg_keyForConsole("MSG_CONSOLE_KEY",Systems::S_Console, MessageData{MessageData::KEYBOARD_KEY, .key = event.key.code});
                        send(msg_keyForConsole);
                    }else{
                        //Deal with other keypresses here
                        //Remember that for smooth movement I should use the sf::keyboard thing
                        Message msg_keypressed("MSG_KEYPRESS", MessageData{MessageData::KEYBOARD_KEY, .key = event.key.code});
                        send(msg_keypressed);
                    }
                }
            }
                break;
                
            case sf::Event::JoystickButtonPressed:
            {
                Message msg_buttonPressed("MSG_BUTTON_PRESSED", MessageData{MessageData::INTEGER, .integer = (int)event.joystickButton.button});
                send(msg_buttonPressed);
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
