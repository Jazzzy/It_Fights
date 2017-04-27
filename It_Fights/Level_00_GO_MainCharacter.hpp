//
//  Level_00_GO_MainCharacter.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 22/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Level_00_GO_MainCharacter_hpp
#define Level_00_GO_MainCharacter_hpp

#include <stdio.h>
#include "AnimatedSprite.hpp"
#include "GameObject.hpp"
#include "json.hpp"
#include <unordered_map>
#include "Scene.hpp"
#include "BoxCollider.hpp"



class Level_00_GO_MainCharacter_AnimatedSprite : public AnimatedSprite {
public:
    Level_00_GO_MainCharacter_AnimatedSprite();
private:
    
};


enum Heading { UP,DOWN,RIGHT,LEFT};

class Level_00_GO_MainCharacter : public GameObject{
public:
    Level_00_GO_MainCharacter(Scene * scene);
    ~Level_00_GO_MainCharacter();
    void update();
    void draw(sf::RenderTarget * renderTarget);
private:
    Level_00_GO_MainCharacter_AnimatedSprite animatedSprite;
    
    sf::Vector2f position;
    sf::Vector2f oldPosition;
    sf::Vector2f velocity;
    Scene * scene;
    
    float walkingSpeed;
    Heading calculateHeading(sf::Vector2f velocity);
    Heading lastHeading;
    void tryToUpdateAnimation();
    
    BoxCollider locationCollider;
    void manageCollisionWithWall(sf::Vector2f velocity);
    
    
    
};

#endif /* Level_00_GO_MainCharacter_hpp */
