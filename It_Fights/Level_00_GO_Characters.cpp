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
Level_00_GO_Characters::Level_00_GO_Characters(Scene* scene, CharacterOptions options):
GameObject(scene){

    this->characterOptions = options;
    
    this->observer_1 = nullptr;
    this->observer_2 = nullptr;
    
    switch(this->characterOptions){
    
        case HUMAN_VS_AGENT:
            this->observer_2 = new AIObserver(this,Position::PLAYER_2);
            this->character_1 = new Level_00_GO_MainCharacter(scene,sf::Vector2f(120,150),PLAYER_1);
            this->character_2 = new Level_00_GO_EnemyCharacter(scene,sf::Vector2f(280,150), observer_2, PLAYER_2, RULE_BASED);
            break;
        case AGENT_VS_AGENT:
            this->observer_1 = new AIObserver(this,Position::PLAYER_1);
            this->observer_2 = new AIObserver(this,Position::PLAYER_2);
            this->character_1 = new Level_00_GO_EnemyCharacter(scene,sf::Vector2f(120,150), observer_1, PLAYER_1, RULE_BASED);
            this->character_2 = new Level_00_GO_EnemyCharacter(scene,sf::Vector2f(280,150), observer_2, PLAYER_2, REINFORCEMENT_1_BASED);
            break;
        case HUMAN_VS_HUMAN:
            this->character_1 = new Level_00_GO_MainCharacter(scene,sf::Vector2f(120,150),PLAYER_1);
            this->character_2 = new Level_00_GO_MainCharacter(scene,sf::Vector2f(280,150),PLAYER_2);
            break;
    
    }
    
}

Level_00_GO_Characters::~Level_00_GO_Characters(){
    
    delete this->character_1;
    delete this->character_2;
    
    if(this->observer_1 != nullptr)
        delete this->observer_1;
    
    if(this->observer_2 != nullptr)
        delete this->observer_2;
    
}


void Level_00_GO_Characters::onStart(){
    this->getCharacter_1()->onStart();
    this->getCharacter_2()->onStart();
    
    //We force an update here to force the early failure in case of error
    if(this->observer_1 != nullptr)
        this->observer_1->update();
    
    if(this->observer_2 != nullptr)
        this->observer_2->update();

}


void Level_00_GO_Characters::onEnd(){
    this->getCharacter_1()->onEnd();
    this->getCharacter_2()->onEnd();
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
    
    std::array <Level_00_GO_BasicCharacter*,2> characterVector = {this->character_1, this->character_2};
    
    //We sort the characters by position
    std::sort(characterVector.begin(), characterVector.end(), comp);
    
    
    //And we draw them
    for(auto it = characterVector.begin() ; it != characterVector.end() ; ++it ){
        (*it)->draw(renderTarget);
    }
    
}

//We simply call the update method of both characters
void Level_00_GO_Characters::update(){
    this->character_1->update();
    this->character_2->update();
}

Level_00_GO_BasicCharacter * Level_00_GO_Characters::getCharacter_1(){
    return (this->character_1);
}

Level_00_GO_BasicCharacter * Level_00_GO_Characters::getCharacter_2(){
    return (this->character_2);
}
