//
//  MainCharacterController.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 16/5/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef MainCharacterController_hpp
#define MainCharacterController_hpp

#include "GeneralCharacterController.hpp"

class MainCharacterController : public GeneralCharacterController {
 public:
  MainCharacterController(short controllerNumber);
  ~MainCharacterController();

  virtual bool isConnected();
  virtual bool isAttackButtonPressed();
  virtual bool isParryButtonPressed();
  virtual sf::Vector2f getJoystickAxisPosition();

 private:
  short controllerNumber;
};

#endif /* MainCharacterController_hpp */
