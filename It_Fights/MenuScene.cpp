//
//  MenuScene.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "MenuScene.hpp"
#include "Systems.hpp"
#include "DebugUtilities.hpp"
#define RESOLUTION_X 2000
#define RESOLUTION_Y 1500

MenuScene::MenuScene(MessageBus * messageBus) : Scene(messageBus), titleText(this){

    //Add here all GameObjects necessary with
    this->addGameObject(&titleText);
    
    this->localUpdateFunction = [&](){ this->localUpdateImplemented(); };
    this->changedRes=false;
    
}

MenuScene::~MenuScene(){
    
}

void MenuScene::localUpdateImplemented(){
    if(!changedRes){
        //We tell the window to render in an specific resolution
        PairI intPair{.x =  static_cast<int>(RESOLUTION_X), .y =  static_cast<int>(RESOLUTION_Y)};
        MessageData pairData{MessageData::PAIR_OF_INTS, .intPair = intPair };
        Message msg_internalRes("MSG_RESIZE_INTERNAL_RESOLUTION",Systems::S_Window, pairData);
        send(msg_internalRes);
        
        changedRes = true;
        
        
        Message msg_smoothFalse("MSG_SMOOTH_FALSE",Systems::S_Window);
        send(msg_smoothFalse);
        
    }
}

void MenuScene::onNotify (Message message){
    
    
    if(message.getEvent().compare("MSG_KEYPRESS")==0){
        if(message.getData().type!=MessageData::KEYBOARD_KEY){
            std::cerr << "ERROR: The data in this message should be keyboard key" << std::endl;
        }else{
            switch(message.getData().key){
                //@@TODO: Change menu options
                case sf::Keyboard::Up :
                    prints("UP!");
                    break;
                    
                case sf::Keyboard::Down:
                    prints("DOWN!");
                    break;
                    
                default:
                    break;
            }
            
        }
    }
    
}
