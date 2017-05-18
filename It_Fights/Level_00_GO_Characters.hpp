//
//  Level_00_GO_Characters.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 29/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Level_00_GO_Characters_hpp
#define Level_00_GO_Characters_hpp

#include "GameObject.hpp"
#include "Level_00_GO_MainCharacter.hpp"
#include "Level_00_GO_EnemyCharacter.hpp"

/*
 This is a container Game Object used to store the two characters.
 
 This needs to be done because we need custom draw functionality to sort
 both characters depending on their Y position on the screen
 
 */
class Level_00_GO_Characters : public GameObject {
public:
    Level_00_GO_Characters(Scene* scene);
    
    /*
     Function used to sort out characters
     by the "y" position since they need to be drawn on top
     of each other correctly, that is, if a character is right
     below the other one that needs to be drawn second.
     */
    void draw(sf::RenderTarget * renderTarget);
    
    /*
     Custom update function for this game object since it contains other game objects that are not registered on the scene
     */
    void update();
    
    void onStart();
    void onEnd();
    
    Level_00_GO_MainCharacter * getMainCharacter();
    Level_00_GO_EnemyCharacter * getEnemyCharacter();
    
private:
    Level_00_GO_MainCharacter mainCharacter;
    Level_00_GO_EnemyCharacter enemyCharacter;
    
};

#endif /* Level_00_GO_Characters_hpp */
