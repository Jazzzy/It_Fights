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
#include "PhysicsTypes.hpp"


enum Position {
    PLAYER_1,
    PLAYER_2
};


//Sizes for the location collider of the character
#define hurtboxSize_x (10)
#define hurtboxSize_y (12)


//Offsets for the locaiton collider of the character relative to its position
#define hurtboxOffset_x (5)
#define hurtboxOffset_y (10)

//Offsets for the hitbox collider relative to its position
#define HITBOX_OFFSET_X (0)
#define HITBOX_OFFSET_Y (-15)

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
    virtual void draw(sf::RenderTarget * renderTarget);
    virtual void onStart();
    virtual void onEnd();
    virtual void startAttackCollision(bool area) = 0;
    
    sf::Vector2f getPosition();
    sf::Vector2f getVelocity();
    float getHealthNormalized();
    
    Direction_4 getDirection_4();
    bool isAttacking();
    bool isParrying();
    bool isOnCooldown();
    
protected:
    Level_00_GO_BasicCharacter_AnimatedSprite animatedSprite;
    GeneralCharacterController *controller;
    
    std::string characterPublicName;
    std::string getCharacterPublicName();
    
    float walkingSpeed;
    float health;
    float maxHealth;
    bool receiveDamage(float damage, sf::Vector2f direction);
    virtual void die();
    
    std::function<void(bool)> attackFunction;
    
    sf::Vector2f position;
    sf::Vector2f oldPosition;
    sf::Vector2f velocity;
    
    Direction_4 calculateDirection_4(sf::Vector2f velocity);
    Direction_4 lastDirection_4;
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
    void startAttack(Direction_4 direction);
    bool attacking;
    
    
    void startParry();
    bool parrying;
    bool successfulParry;
    virtual void parryCounter(sf::Vector2f direction) = 0;
    
    
    void startCooldown();
    bool inCooldown;
    
    sf::CircleShape characterMarker;
    
};

#endif /* Level_00_GO_BasicCharacter_hpp */

