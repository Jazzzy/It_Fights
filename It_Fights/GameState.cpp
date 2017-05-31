//
//  GameState.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "GameState.hpp"
#include "Systems.hpp"
#include "Game.hpp"
#include "MenuScene.hpp"
#include "Level_00_NeoPurple_DEMO.hpp"
#include "DebugUtilities.hpp"

extern Game game;

GameState::GameState(MessageBus * messageBus) : BusNode(Systems::S_GameState, messageBus){
    
    //this->scene = new MenuScene(messageBus);
    this->scene = new Level_00_NeoPurple_DEMO(messageBus);
    this->mainMenu = true;
    this->paused = false;
    
}

GameState::~GameState(){
    delete this->scene;
}

void GameState::update(){
    this->scene->update();
}

void GameState::onNotify(Message message){
    
    if(message.getEvent().compare("MSG_GO_TO_MENU")==0){
        if (this->scene  != nullptr){
            this->scene->onEnd();
            delete this->scene;
        }
        this->scene = new MenuScene(messageBus);
        this->scene->onStart();

    }else if(message.getEvent().compare("MSG_GO_TO_MAINGAME")==0){
        if (this->scene  != nullptr){
            this->scene->onEnd();
            delete this->scene;
        }
        this->scene = new Level_00_NeoPurple_DEMO(messageBus);
        this->scene->onStart();
    }
}

Scene * GameState::getScene(){
    return this->scene;
}

bool GameState::isConsoleOpen(){
    return game.isConsoleOpen();
}

bool GameState::isGamePaused(){
    return this->paused;
}

bool GameState::areWeInMainMenu(){
    return this->mainMenu;
}

