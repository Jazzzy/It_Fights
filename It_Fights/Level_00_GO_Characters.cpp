//
//  Level_00_GO_Characters.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 29/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Level_00_GO_Characters.hpp"
#include <array>

/*
 Constructor for this container Game Object
 
 It locates both characters on the map
 
 */
Level_00_GO_Characters::Level_00_GO_Characters():
mainCharacter(sf::Vector2f(120,150)),
enemyCharacter(sf::Vector2f(280,150)){}


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
    
    std::array <Level_00_GO_BasicCharacter*,2> characterVector = {&this->mainCharacter, &this->enemyCharacter};
    
    //We sort the characters by position
    std::sort(characterVector.begin(), characterVector.end(), comp);
    
    
    //And we draw them
    for(auto it = characterVector.begin() ; it != characterVector.end() ; ++it ){
        (*it)->draw(renderTarget);
    }

}

//We simply call the update method of both characters
void Level_00_GO_Characters::update(){
    this->mainCharacter.update();
    this->enemyCharacter.update();
}
