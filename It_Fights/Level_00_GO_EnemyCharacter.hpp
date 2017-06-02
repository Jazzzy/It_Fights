//
//  Level_00_GO_EnemyCharacter.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 29/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Level_00_GO_EnemyCharacter_hpp
#define Level_00_GO_EnemyCharacter_hpp

#include "Level_00_GO_BasicCharacter.hpp"
#include "EnemyCharacterController.hpp"
#include "Behaviour.hpp"
#include "AIObserver.hpp"

class AIObserver;
class Behaviour;

/*
 Class that represents the enemy character in the duel, this extends from our BasicCharacter class
 which contains the general character functionality
 */
class Level_00_GO_EnemyCharacter : public Level_00_GO_BasicCharacter{
public:
    Level_00_GO_EnemyCharacter(Scene* scene, sf::Vector2f position, AIObserver* observer);
    ~Level_00_GO_EnemyCharacter();
    
    /*
     We override the update function to be able to read the input
     from the AI system and apply it to the enemy.
     */
    void update();
    void onStart();
    void onEnd();
    
    AIObserver* getAIObserver();
    
private:
    BoxCollider hurtbox;
    void startAttack();
    
    
    EnemyCharacterController myController;
    
    Behaviour* behaviour;
    AIObserver* observer;

};

#endif /* Level_00_GO_EnemyCharacter_hpp */
