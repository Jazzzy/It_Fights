//
//  Level_00_GO_Characters.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 29/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Level_00_GO_Characters.hpp"
#include <array>
#include "RuleBasedBehaviour.hpp"

/*
 Constructor for this container Game Object
 
 It locates both characters on the map
 
 */
Level_00_GO_Characters::Level_00_GO_Characters(Scene* scene):
GameObject(scene){

    this->observer = new AIObserver(this);
    this->mainCharacter = new Level_00_GO_MainCharacter(scene,sf::Vector2f(120,150));
    this->enemyCharacter = new Level_00_GO_EnemyCharacter(scene,sf::Vector2f(280,150), observer);
    
    
}

Level_00_GO_Characters::~Level_00_GO_Characters(){
    delete this->observer;
}


void Level_00_GO_Characters::onStart(){
    this->getMainCharacter()->onStart();
    this->getEnemyCharacter()->onStart();
    
    //We force an update here to force the early failure in case of error
    this->observer->getFightState(true);
}


void Level_00_GO_Characters::onEnd(){
    this->getMainCharacter()->onEnd();
    this->getEnemyCharacter()->onEnd();
}


/*
 This is the scruct used to compare the position of the two characters
 and sort the array
 */
struct {
    bool operator()(Level_00_GO_BasicCharacter* a, Level_00_GO_BasicCharacter* b)
    {
        return a->getPosition().y < b->getPosition().y;
    }
} comp;

/*
 We sort and draw both characters depending on the y value of their position
 */
void Level_00_GO_Characters::draw(sf::RenderTarget * renderTarget){
    
    std::array <Level_00_GO_BasicCharacter*,2> characterVector = {this->mainCharacter, this->enemyCharacter};
    
    //We sort the characters by position
    std::sort(characterVector.begin(), characterVector.end(), comp);
    
    
    //And we draw them
    for(auto it = characterVector.begin() ; it != characterVector.end() ; ++it ){
        (*it)->draw(renderTarget);
    }
    
}

//We simply call the update method of both characters
void Level_00_GO_Characters::update(){
    this->mainCharacter->update();
    this->enemyCharacter->update();
}

Level_00_GO_MainCharacter * Level_00_GO_Characters::getMainCharacter(){
    return (this->mainCharacter);
}

Level_00_GO_EnemyCharacter * Level_00_GO_Characters::getEnemyCharacter(){
    return (this->enemyCharacter);
}
