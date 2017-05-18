//
//  Game.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Game.hpp"

Game::Game() :
messageBus(),
gameState(&messageBus),
consoleSystem(&messageBus),
windowSystem (&messageBus,&consoleSystem,&collisionSystem,"It_fights",2000,1500),
inputSystem (&messageBus,&windowSystem),
collisionSystem(&messageBus){
    
    
    this->gameState.getScene()->onStart();
    
}

Game::~Game(){

    this->gameState.getScene()->onEnd();

}

GameState * Game::getGameState(){
    return &this->gameState;
}

void Game::loop(){
    while(windowSystem.isOpen()){
        inputSystem.update();
        gameState.update();
        collisionSystem.update();
        consoleSystem.update();
        windowSystem.update();
        messageBus.notify();
    }
}

bool Game::isConsoleOpen(){
    return this->consoleSystem.isOpen();
}

Collisions * Game::getCollisionSystem(){
    return &this->collisionSystem;
}


