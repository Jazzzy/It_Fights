//
//  Level_00_GO_Characters.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 29/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Level_00_GO_Characters_hpp
#define Level_00_GO_Characters_hpp

#include "AIObserver.hpp"
#include "GameObject.hpp"
#include "Level_00_GO_EnemyCharacter.hpp"
#include "Level_00_GO_MainCharacter.hpp"

class AIObserver;
class Level_00_GO_EnemyCharacter;

enum CharacterOptions { HUMAN_VS_AGENT, HUMAN_VS_HUMAN, AGENT_VS_AGENT };

/*
 This is a container Game Object used to store the two characters.

 This needs to be done because we need custom draw functionality to sort
 both characters depending on their Y position on the screen and its a good way
 of encapsulating both the player and the enemy.

 */
class Level_00_GO_Characters : public GameObject {
 public:
  Level_00_GO_Characters(Scene *scene, CharacterOptions options);
  ~Level_00_GO_Characters();

  /*
   Function used to sort out characters
   by the "y" position since they need to be drawn on top
   of each other correctly, that is, if a character is right
   below the other one that needs to be drawn second.
   */
  void draw(sf::RenderTarget *renderTarget);

  /*
   Custom update function for this game object since it contains other game
   objects that are not registered on the scene
   */
  void update();

  void onStart();
  void onEnd();

  Level_00_GO_BasicCharacter *getCharacter_1();
  Level_00_GO_BasicCharacter *getCharacter_2();

 private:
  CharacterOptions characterOptions;
  Level_00_GO_BasicCharacter *character_1;
  Level_00_GO_BasicCharacter *character_2;
  AIObserver *observer_1;
  AIObserver *observer_2;
};

#endif /* Level_00_GO_Characters_hpp */
