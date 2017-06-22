//
//  EnemyCharacterController.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 16/5/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef EnemyCharacterController_hpp
#define EnemyCharacterController_hpp

#include "GeneralCharacterController.hpp"

class EnemyCharacterController : public GeneralCharacterController {
 public:
  EnemyCharacterController();
  ~EnemyCharacterController();

  virtual bool isConnected();
  virtual bool isAttackButtonPressed();
  virtual bool isParryButtonPressed();
  virtual sf::Vector2f getJoystickAxisPosition();

  void setAttackButton(bool pressed);
  void setParryButton(bool pressed);
  void setJoystickPosition(sf::Vector2f vector);
  void setAll(bool attackButton, bool parryButton, sf::Vector2f vector);

 private:
  bool attackButtonPressed;
  bool parryButtonPressed;
  sf::Vector2f joystickAxis;
};

#endif /* EnemyCharacterController_hpp */
