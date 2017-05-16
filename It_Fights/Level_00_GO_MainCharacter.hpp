//
//  Level_00_GO_MainCharacter.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 22/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Level_00_GO_MainCharacter_hpp
#define Level_00_GO_MainCharacter_hpp

#include "Level_00_GO_BasicCharacter.hpp"
#include "MainCharacterController.hpp"


/*
 Class that represents the main character in the duel, this extends from our BasicCharacter class
 which contains the general character functionality.
 */
class Level_00_GO_MainCharacter : public Level_00_GO_BasicCharacter{
public:
    Level_00_GO_MainCharacter(Scene* scene, sf::Vector2f position);
    
    /*
     We override the update function to be able to read the player input
     and apply it to the character controlled.
     */
    void update();
private:
    BoxCollider hurtbox;
    void startAttack();
    
    
    MainCharacterController myController;

};

#endif /* Level_00_GO_MainCharacter_hpp */
