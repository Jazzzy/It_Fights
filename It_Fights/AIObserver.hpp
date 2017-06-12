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
    MYSELF,
    OTHER
};

enum CharacterAction {
    MOVING,
    STANDING,
    ATTACKING,
    PARRYING,
    COOLING_DOWN
};


/********************/
/* CONTINUOUS STATE */
/********************/


struct CharacterState {
    float health;
    sf::Vector2f position;
    sf::Vector2f velocity;
    CharacterAction action;
};

struct FightState {
    CharacterState myState;
    CharacterState  otherState;
    
    float timeSinceLastCheck;
    float totalFightingTime;
};

/********************/




/********************/
/* DISCRETE STATE */
/********************/

enum Distance_Discrete {
    IN_RANGE,
    CLOSE_TO_RANGE,
    OUT_OF_RANGE
};

struct Position_Discrete {          //216
    Distance_Discrete distance;     //3
    Direction_8 angle;              //8
    Direction_8 wallPositions;      //9
};

struct MyCharacterState_Discrete {      //6480
    short health;                       //6
    Position_Discrete position;         //216
    CharacterAction action;             //5
};

struct OtherCharacterState_Discrete {   //30
    short health;                       //6
    CharacterAction action;             //5
};

struct FightState_Discrete {                    //194400
    MyCharacterState_Discrete myState;          //6480
    OtherCharacterState_Discrete otherState;    //30
    //How to take time into account?
};

/********************/


std::ostream& operator<<(std::ostream& os, const FightState_Discrete& state);


class AIObserver {
public:
    AIObserver(Level_00_GO_Characters* characters, Position position);
    ~AIObserver();
    
    FightState getFightState(bool doCheck);
    Position getPlayer1_2();

    MyCharacterState_Discrete discretizeMyCharacter(FightState continuousState);
    OtherCharacterState_Discrete discretizeOtherCharacter(CharacterState characterState);
    FightState_Discrete discretizeState(FightState continuousState);

    
private:
    FightState currentFightState;
    short playerPosition;
    
    void updateFightState();
    CharacterState getCharacterState(Character character);
    sf::Clock observerClock;
    sf::Clock deltaClock;
    Level_00_GO_Characters* characters;
    
    
    short discretizeHealth(float health , short divisions);
};

#endif /* AIObserver_hpp */
