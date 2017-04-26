//
//  level_00_NeoPurple_DEMO.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 21/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Level_00_NeoPurple_DEMO.hpp"
#include "Window.hpp"
#include "Systems.hpp"



Level_00_NeoPurple_DEMO::Level_00_NeoPurple_DEMO(MessageBus * messageBus) :
Scene(messageBus),
level_00_GO_Ground(),
view(sf::FloatRect(0,0,LVL_00_RESOLUTION_X,LVL_00_RESOLUTION_Y)),
mainCharacter(this)
{
    
    
    changedRes = false;
    
    //Add here all GameObjects necessary to with "this->addGameObject(GameObject * gameObject)"
    
    this->addGameObject(&level_00_GO_Ground);
    this->addGameObject(&mainCharacter);
    
    this->localUpdateFunction = [&](){ this->localUpdateImplemented(); };
    this->fullScreenShadersFunc = [this](sf::RenderTarget * renderTarget,const sf::Texture * screenTexture){
        this->screenShaders(renderTarget,screenTexture);
    };
    
    //this->viewptr = &view;
    
}

Level_00_NeoPurple_DEMO::~Level_00_NeoPurple_DEMO(){
    
}


void Level_00_NeoPurple_DEMO::screenShaders(sf::RenderTarget * renderTarget, const sf::Texture * screenTexture){
    
    //@@TODO Apply here shaders for this scene
    
}



void Level_00_NeoPurple_DEMO::localUpdateImplemented(){
    if(!changedRes){
        //We tell the window to render in an specific resolution
        PairI intPair{.x =  static_cast<int>(LVL_00_RESOLUTION_X), .y =  static_cast<int>(LVL_00_RESOLUTION_Y)};
        MessageData pairData{MessageData::PAIR_OF_INTS, .intPair = intPair };
        Message msg_internalRes("MSG_RESIZE_INTERNAL_RESOLUTION",Systems::S_Window, pairData);
        send(msg_internalRes);
        
        changedRes = true;
        
        
        Message msg_smoothFalse("MSG_SMOOTH_FALSE",Systems::S_Window);
        send(msg_smoothFalse);
        
        //@@TODO send another message for setting the smooth to false;
    }
}


