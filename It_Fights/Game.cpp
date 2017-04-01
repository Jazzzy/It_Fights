//
//  Game.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Game.hpp"

Game::Game() :
    messageBus (messageBus),
    consoleSystem(&messageBus),
    windowSystem (&messageBus,&consoleSystem,"It_fights",2000,1500),
    inputSystem (&messageBus,&windowSystem){}

Game::~Game(){}

void Game::loop(){

    while(windowSystem.isOpen()){
        inputSystem.update();
        consoleSystem.update();
        windowSystem.update();
        messageBus.notify();
    }
    
}

Clock * Game::getDeltaClock(){
    return &this->m_clock;
}

bool Game::isConsoleOpen(){
    return this->consoleSystem.isOpen();
}
