//
//  GameState.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef GameState_hpp
#define GameState_hpp

#include <Scene.hpp>

#define NUMBER_OF_SIMULATIONS (10)

class GameState : BusNode {
 public:
  GameState(MessageBus *messageBus);
  ~GameState();
  void update();
  Scene *getScene();
  bool isConsoleOpen();
  bool isGamePaused();
  bool areWeInMainMenu();

 private:
  void onNotify(Message message);
  Scene *scene;
  bool paused;
  bool mainMenu;

  int simulationsLeft;
};

#endif /* GameState_hpp */
