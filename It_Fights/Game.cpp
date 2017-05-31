//
//  Game.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Game.hpp"

Game::Game() :
messageBus(){
    
    this->messageBus = new MessageBus();
    this->collisionSystem = new Collisions(this->messageBus);
    this->gameState = new GameState(this->messageBus);
    this->consoleSystem = new Console(this->messageBus);
    this->windowSystem = new Window(this->messageBus,this->consoleSystem,this->collisionSystem,"It_fights",2000,1500);
    this->inputSystem = new Input(this->messageBus,this->windowSystem);
    
    
    this->gameState->getScene()->onStart();
    
}

Game::~Game(){

    this->gameState->getScene()->onEnd();
    
    delete this->inputSystem;
    delete this->windowSystem;
    delete this->consoleSystem;
    delete this->gameState;
    delete this->collisionSystem;
    delete this->messageBus;

}

GameState * Game::getGameState(){
    return this->gameState;
}

void Game::loop(){
    while(windowSystem->isOpen()){
        inputSystem->update();
        gameState->update();
        collisionSystem->update();
        consoleSystem->update();
        windowSystem->update();
        messageBus->notify();
    }
}

bool Game::isConsoleOpen(){
    return this->consoleSystem->isOpen();
}

Collisions * Game::getCollisionSystem(){
    return this->collisionSystem;
}


