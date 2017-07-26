//
//  Level_00_GO_EnemyCharacter.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 29/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Level_00_GO_EnemyCharacter_hpp
#define Level_00_GO_EnemyCharacter_hpp

#include "AIObserver.hpp"
#include "Behaviour.hpp"
#include "EnemyCharacterController.hpp"
#include "Level_00_GO_BasicCharacter.hpp"

class AIObserver;
class Behaviour;

enum EnemyType { RULE_BASED, REINFORCEMENT_1_BASED };

/*
 Class that represents the enemy character in the duel, this extends from our
 BasicCharacter class which contains the general character functionality
 */
class Level_00_GO_EnemyCharacter : public Level_00_GO_BasicCharacter {
 public:
  Level_00_GO_EnemyCharacter(Scene* scene, sf::Vector2f position,
                             AIObserver* observer, Position playerPosition,
                             EnemyType type);
  ~Level_00_GO_EnemyCharacter();

  /*
   We override the update function to be able to read the input
   from the AI system and apply it to the enemy.
   */
  void update();
  void onStart();
  void onEnd();
  void startAttackCollision(bool area);

  AIObserver* getAIObserver();

 private:
  BoxCollider* hurtbox;
  void startAttack(bool area);
  void parryCounter(sf::Vector2f direction);
  void die();

  EnemyCharacterController myController;

  Behaviour* behaviour;
  AIObserver* observer;
};

#endif /* Level_00_GO_EnemyCharacter_hpp */
