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
#include "GeneralCharacterController.hpp"


//Sizes for the location collider of the character
#define hurtboxSize_x (10)
#define hurtboxSize_y (12)


//Offsets for the locaiton collider of the character relative to its position
#define hurtboxOffset_x (5)
#define hurtboxOffset_y (10)

//Offsets for the hitbox collider relative to its position
#define HITBOX_OFFSET_X (0)
#define HITBOX_OFFSET_Y (-15)

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
    Level_00_GO_BasicCharacter(Scene* scene, sf::Vector2f position);
    ~Level_00_GO_BasicCharacter();
    
    void update();
    void draw(sf::RenderTarget * renderTarget);
    void onStart();
    void onEnd();
    
    sf::Vector2f getPosition();
    float getHealthNormalized();
    
protected:
    Level_00_GO_BasicCharacter_AnimatedSprite animatedSprite;
    GeneralCharacterController *controller;
    
    
    float walkingSpeed;
    float health;
    float maxHealth;
    void receiveDamage(float damage);
    void die();
    
    std::function<void()> attackFunction;
    
    sf::Vector2f position;
    sf::Vector2f oldPosition;
    sf::Vector2f velocity;
    
    Heading calculateHeading(sf::Vector2f velocity);
    Heading lastHeading;
    void tryToUpdateAnimation();
    bool shouldUpdate;
    
    BoxCollider locationCollider;
    void manageCollisionWithVector(sf::Vector2f velocity);
    
    void startDash(sf::Vector2f direction, float magnitude, float seconds, bool force);
    bool dash();
    sf::Vector2f finalDashPosition;
    sf::Vector2f startingDashPosition;
    float timeRemainingForDash;
    float totalDashTime;
    bool dashing;
    float dashMagnitude, dashMillis;
    
    
    float basicAttackDamage;
    float attackRadious;
    void startAttack();
    bool attacking;
    
    
    void startParry();
    bool parrying;
    bool successfulParry;
    
    
    void startCooldown();
    bool inCooldown;
    
};

#endif /* Level_00_GO_BasicCharacter_hpp */

