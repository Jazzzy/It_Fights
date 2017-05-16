//
//  GeneralCharacterController.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 16/5/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef GeneralCharacterController_hpp
#define GeneralCharacterController_hpp

#include <SFML/Graphics.hpp>

class GeneralCharacterController {
public:
    virtual ~GeneralCharacterController() {}
    
    
    virtual bool isConnected() = 0;
    virtual bool isAttackButtonPressed() = 0;
    virtual sf::Vector2f getJoystickAxisPosition() = 0;
    

};

#endif /* GeneralCharacterController_hpp */


