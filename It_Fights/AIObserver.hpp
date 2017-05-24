//
//  AIObserver.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 24/5/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef AIObserver_hpp
#define AIObserver_hpp

#include "Level_00_GO_Characters.hpp"

class Level_00_GO_Characters;

enum Character {
    PLAYER,
    ENEMY
};

enum CharacterAction {
    MOVING,
    STANDING,
    ATTACKING,
    PARRYING,
    COOLING_DOWN
};

struct CharacterState {
    float health;
    sf::Vector2f position;
    sf::Vector2f velocity;
    CharacterAction action;
};

struct FightState {
    CharacterState playerState;
    CharacterState  enemyState;
    
    float timeSinceLastCheck;
    float totalFightingTime;
};

class AIObserver {
public:
    AIObserver(Level_00_GO_Characters* characters);
    ~AIObserver();
    
    FightState getFightState(bool doCheck);
    
private:
    FightState currentFightState;
    
    void updateFightState();
    CharacterState getCharacterState(Character character);
    sf::Clock observerClock;
    sf::Clock deltaClock;
    Level_00_GO_Characters* characters;
};

#endif /* AIObserver_hpp */
