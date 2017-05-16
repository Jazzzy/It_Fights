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


class EnemyCharacterController : public GeneralCharacterController{
public:
    EnemyCharacterController();
    ~EnemyCharacterController();
    
    virtual bool isConnected();
    virtual bool isAttackButtonPressed();
    virtual sf::Vector2f getJoystickAxisPosition();
    
    
};

#endif /* EnemyCharacterController_hpp */
