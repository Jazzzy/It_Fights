//
//  Level_00_GO_BasicCharacter.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 22/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Level_00_GO_BasicCharacter_hpp
#define Level_00_GO_BasicCharacter_hpp

#include "AnimatedSprite.hpp"
#include "GameObject.hpp"
#include "BoxCollider.hpp"



enum Heading { UP,DOWN,RIGHT,LEFT };

/*
 Class that extends from the Animated Sprite class and loads the neccesary
 files with the data for the animations.
 */
class Level_00_GO_BasicCharacter_AnimatedSprite : public AnimatedSprite {
public:
    Level_00_GO_BasicCharacter_AnimatedSprite();
};

class Level_00_GO_BasicCharacter : public GameObject{
public:
    Level_00_GO_BasicCharacter(sf::Vector2f position);
    ~Level_00_GO_BasicCharacter();
    void update();
    void draw(sf::RenderTarget * renderTarget);
    sf::Vector2f getPosition();
protected:
    Level_00_GO_BasicCharacter_AnimatedSprite animatedSprite;
    
    sf::Vector2f position;
    sf::Vector2f oldPosition;
    sf::Vector2f velocity;
    
    float walkingSpeed;
    Heading calculateHeading(sf::Vector2f velocity);
    Heading lastHeading;
    void tryToUpdateAnimation();
    
    BoxCollider locationCollider;
    void manageCollisionWithWall(sf::Vector2f velocity);
    void manageCollisionWithMovingObject(sf::Vector2f velocity);
    
};

#endif /* Level_00_GO_BasicCharacter_hpp */

