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
#include "DebugUtilities.hpp"



Level_00_NeoPurple_DEMO::Level_00_NeoPurple_DEMO(MessageBus * messageBus) :
Scene(messageBus),
level_00_GO_Ground(this),
view(sf::FloatRect(0,0,LVL_00_RESOLUTION_X,LVL_00_RESOLUTION_Y)),
level_00_GO_Characters(this),
level_00_GO_HealthBars(this,&level_00_GO_Characters)
{
    
    
    changedRes = false;
    
    //We add all GameObjects necessary to with "this->addGameObject(GameObject * gameObject)"
    
    this->addGameObject(&level_00_GO_Ground);
    this->addGameObject(&level_00_GO_Characters);
    this->addGameObject(&level_00_GO_HealthBars);
    
    this->localUpdateFunction = [&](){ this->localUpdateImplemented(); };
    this->fullScreenShadersFunc = [this](sf::RenderTarget * renderTarget,const sf::Texture * screenTexture){
        this->screenShaders(renderTarget,screenTexture);
    };
}

Level_00_NeoPurple_DEMO::~Level_00_NeoPurple_DEMO(){
        
}


void Level_00_NeoPurple_DEMO::screenShaders(sf::RenderTarget * renderTarget, const sf::Texture * screenTexture){
    

    
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
        
    }
}


