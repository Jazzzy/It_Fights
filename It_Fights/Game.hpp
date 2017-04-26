//
//  Game.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//


#ifndef Game_hpp
#define Game_hpp


#include "MessageBus.hpp"
#include "Console.hpp"
#include "Window.hpp"
#include "Input.hpp"
#include "Clock.hpp"
#include "Collisions.hpp"

#include "GameState.hpp"
#include "ResourceManager.hpp"

class Game{
public:
    Game();
    ~Game();
    void loop();
    Clock * getDeltaClock();
    bool isConsoleOpen();
    GameState * getGameState();
    Collisions * getCollisionSystem();
    
private:
    GameState gameState;
    
    MessageBus messageBus;
    Console consoleSystem;
    Window windowSystem;
    Input inputSystem;
    Clock m_clock;
    Collisions collisionSystem;
    
    
};

#endif /* Game_hpp */
