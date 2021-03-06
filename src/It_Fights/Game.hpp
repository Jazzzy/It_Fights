//
//  Game.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

// Internal sunsystems of the game
#include "Collisions.hpp"
#include "Console.hpp"
#include "Input.hpp"
#include "MessageBus.hpp"
#include "Sound.hpp"
#include "Window.hpp"

// Attributes that need to be accessed by a lot of classes in the game
#include "GameState.hpp"

class Game {
 public:
  Game();
  ~Game();
  void loop();
  bool isConsoleOpen();
  GameState* getGameState();
  Collisions* getCollisionSystem();

 private:
  GameState* gameState;

  MessageBus* messageBus;
  Console* consoleSystem;
  Window* windowSystem;
  Input* inputSystem;
  Collisions* collisionSystem;
  Sound* soundSystem;
};

#endif /* Game_hpp */
