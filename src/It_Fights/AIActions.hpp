//
//  AIActions.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 13/6/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef AIActions_hpp
#define AIActions_hpp

#include "EnemyCharacterController.hpp"

enum Action {
  DO_NOTHING,
  MOVE_UP,
  MOVE_DOWN,
  MOVE_LEFT,
  MOVE_RIGHT,
  ATTACK,
  PARRY
};

class AIActions {
 public:
  AIActions(EnemyCharacterController* controller);
  ~AIActions();
  void execute(Action action);
  EnemyCharacterController* getController();

 private:
  EnemyCharacterController* controller;
};

#endif /* AIActions_hpp */
