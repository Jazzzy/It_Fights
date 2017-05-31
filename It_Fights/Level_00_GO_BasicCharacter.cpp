//
//  Level_00_GO_BasicCharacter..cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 29/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Level_00_GO_BasicCharacter.hpp"
#include <fstream>
#include "ResourcePath.hpp"
#include "SomeMath.hpp"
#include "DebugUtilities.hpp"
#include "Clock.hpp"
#include "Systems.hpp"

#include <SFML/Window/Joystick.hpp>


#include "Game.hpp"
extern Game game;

/*
 Here we load the json and png files with the data for the characters and its animations.
 */
Level_00_GO_BasicCharacter_AnimatedSprite::Level_00_GO_BasicCharacter_AnimatedSprite() :
AnimatedSprite("prota_0.2.json", "prota_0.2.png", DataMode::Aseprite_Array_Json_Data_WPivot){
    this->startAnimation("RUN_UP", true, [](){});
}






/****************************/
/*      TRUE GAMEOBJECT     */
/****************************/


//Sizes for the location collider of the character
#define LocationColliderSize_x (8)
#define LocationColliderSize_y (8)


//Offsets for the locaiton collider of the character relative to its position
#define LocationColliderOffset_x (4)
#define LocationColliderOffset_y (3)

Level_00_GO_BasicCharacter::Level_00_GO_BasicCharacter(Scene* scene, sf::Vector2f position):
GameObject(scene),
locationCollider( sf::Vector2f (LocationColliderSize_x, LocationColliderSize_y) ,
                 
                 //Function that returs the position in which the location collider should be positioned
                 [this]() -> sf::Vector2f{
                     return sf::Vector2f(this->position.x-LocationColliderOffset_x,this->position.y-LocationColliderOffset_y);
                 },
                 
                 //Function that deals with a collisions accordingly
                 [this](ColliderType colType, sf::Vector2f vector, float value){
                     
                     if(colType == ColliderType::INVERTED_BOX || colType == WALL){
                         this->manageCollisionWithVector(vector);
                     }else if(colType == ColliderType::MOVING_OBJECT){
                         this->manageCollisionWithVector(vector);
                     }
                     
                 },
                 
                 //Type of the location collider
                 ColliderType::MOVING_OBJECT, CollisionLayer::NEUTRAL)
{
    
    
    
    this->walkingSpeed = 130.f;
    this->health = 100.f;
    this->maxHealth= 100.f;
    
    
    this->position = position;
    this->oldPosition = this->position;
    this->velocity = sf::Vector2f(0.f,0.f);
    
    this->lastHeading = Heading::DOWN;
    this->shouldUpdate = true;
    
    this->finalDashPosition = sf::Vector2f(0.f,0.f);
    this->startingDashPosition = sf::Vector2f(0.f,0.f);
    this->timeRemainingForDash = 0.f;
    this->totalDashTime = 0.f;
    this->dashing = false;
    this->dashMagnitude = 20.f;
    this->dashMillis = .2f;
    
    
    this->basicAttackDamage = 10.f;
    this->attackRadious = 28.f;
    this->attackFunction = [](){};
    this->attacking = false;
    
    
    this->parrying = false;
    this->successfulParry = false;
    
    
    this->inCooldown = false;
    
}

Level_00_GO_BasicCharacter::~Level_00_GO_BasicCharacter(){}

void Level_00_GO_BasicCharacter::onStart(){
        
    if(!this->locationCollider.isRegistered()){
        this->locationCollider.registerCollider();
    }
    if(!this->locationCollider.isActive()){
        this->locationCollider.setActive(true);
    }
    
}

void Level_00_GO_BasicCharacter::onEnd(){
    
    if(this->locationCollider.isActive()){
        this->locationCollider.setActive(false);
    }
    
    if(this->locationCollider.isRegistered()){
        this->locationCollider.unregisterCollider();
    }
    
}


bool Level_00_GO_BasicCharacter::receiveDamage(float damage){
    
    if(this->parrying){
        this->successfulParry = true;
        this->shouldUpdate = true;
        this->parrying= false;
        
        this->parryCounter();
        
        prints("PARRIED!!");
        
        return false;
    }
    
    this->health-= damage;
    if(this->health<=0.){
        this->health = 0.;
        this->die();
    }
    
    return true;
}

void Level_00_GO_BasicCharacter::parryCounter(){
    //@TODO
}

void Level_00_GO_BasicCharacter::die(){
    
    Message message("MSG_GO_TO_MENU");
    
    this->scene->send(message);
    
}

void Level_00_GO_BasicCharacter::manageCollisionWithVector( sf::Vector2f vector ){
    
    this->oldPosition = this->position;
    this->position += vector;
    
}

float Level_00_GO_BasicCharacter::getHealthNormalized(){
    return this->health/this->maxHealth;
}


Heading Level_00_GO_BasicCharacter::calculateHeading(sf::Vector2f velocity){
    
    if(fabs(velocity.x) > fabs(velocity.y)){
        
        if(velocity.x > 0)
            return Heading::RIGHT;
        else
            return Heading::LEFT;
        
    }else if(fabs(velocity.x) < fabs(velocity.y)){
        
        if(velocity.y > 0)
            return Heading::DOWN;
        else
            return Heading::UP;
        
    }else{
        return lastHeading;
    }
    
}

#define VECTOR_LENGTH_LIMIT 0.2f

void Level_00_GO_BasicCharacter::update(){
    
    if(this->dashing){
        this->dash();
        return;
    }
    
    if(this->inCooldown){
        return;
    }
    
    if(!this->shouldUpdate){
        return;
    }
    
    if(!this->controller->isConnected()){
        return;
    }
    
    bool attackButtonPressed = this->controller->isAttackButtonPressed();
    
    if(attackButtonPressed)
        this->attackFunction();
    
    bool parryButtonPressed = this->controller->isParryButtonPressed();
    
    if(parryButtonPressed)
        this->startParry();
    
    sf::Vector2f movementVector = this->controller->getJoystickAxisPosition();
    
    if(getVectorLength(movementVector)>1.0f){
        movementVector = getNormalizedVector(movementVector);
    }else if(getVectorLength(movementVector)>VECTOR_LENGTH_LIMIT){
        //You'll do nothing :P
    }else{
        movementVector = sf::Vector2f(0,0);
    }
    
    this->velocity = (movementVector*this->walkingSpeed * Clock::Instance().getDeltaTime());
    
    this->lastHeading = this->calculateHeading(this->velocity);
    
    this->oldPosition = this->position;
    
    this->position += this->velocity;
    
}

sf::Vector2f Level_00_GO_BasicCharacter::getPosition(){
    return this->position;
}

void Level_00_GO_BasicCharacter::startDash(sf::Vector2f direction, float magnitude, float millis, bool force){
    
    sf::Vector2f finalPosition;
    
    this->finalDashPosition.x=this->position.x + (direction.x * magnitude);
    this->finalDashPosition.y=this->position.y + (direction.y * magnitude);
    this->startingDashPosition = this->position;
    
    this->timeRemainingForDash = millis;
    this->totalDashTime = millis;
    
    this->dashing = true;

}




bool Level_00_GO_BasicCharacter::dash(){
    
    this->timeRemainingForDash -= Clock::Instance().getDeltaTime();
    
    if(timeRemainingForDash <= 0.){
        this->dashing = false;
        this->timeRemainingForDash = 0.;
        this->totalDashTime = 0.;
        return false;
    }

    float amount = this->timeRemainingForDash / this->totalDashTime;
    
    this->position.x = lerp(this->startingDashPosition.x, this->finalDashPosition.x, amount);
    this->position.y = lerp(this->startingDashPosition.y, this->finalDashPosition.y, amount);

    
    return true;

}

sf::Vector2f Level_00_GO_BasicCharacter::getVelocity(){
    return this->velocity;
}

Heading Level_00_GO_BasicCharacter::getHeading(){
    return this->lastHeading;
}

bool Level_00_GO_BasicCharacter::isAttacking(){
    return this->attacking;
}

bool Level_00_GO_BasicCharacter::isParrying(){
    return this->parrying;
}

bool Level_00_GO_BasicCharacter::isOnCooldown(){
    return this->inCooldown;
}


void Level_00_GO_BasicCharacter::startAttack(){
    
    if(!this->shouldUpdate){
        return;
    }
    
    this->shouldUpdate = false;
    this->attacking = true;
    
    auto finishAnimationFunction = [this](){
        this->shouldUpdate = true;
        this->attacking = false;
    };
    
    sf::Vector2f dashVector;
    dashVector.x=0;
    dashVector.y=0;
    
    switch(lastHeading){
        case (Heading::DOWN):
            this->animatedSprite.startAnimation("ATTACK_DOWN", false, finishAnimationFunction);
            dashVector.y=1;
            break;
        case (Heading::UP):
            this->animatedSprite.startAnimation("ATTACK_UP", false, finishAnimationFunction);
            dashVector.y=-1;
            break;
        case (Heading::LEFT):
            this->animatedSprite.startAnimation("ATTACK_LEFT", false, finishAnimationFunction);
            dashVector.x=-1;
            break;
        case (Heading::RIGHT):
            this->animatedSprite.startAnimation("ATTACK_RIGHT", false, finishAnimationFunction);
            dashVector.x=1;
            break;
        default:
            this->animatedSprite.startAnimation("IDLE_DOWN", false, finishAnimationFunction);
            break;
    }
    
    this->startDash(dashVector, dashMagnitude, dashMillis, false);
    
}

void Level_00_GO_BasicCharacter::startParry(){
    
    if(!this->shouldUpdate){
        return;
    }
    
    this->shouldUpdate = false;
    this->parrying = true;
    this->successfulParry = false;
    
    auto finishAnimationFunction = [this](){
        this->shouldUpdate = true;
        this->parrying = false;
        if(!this->successfulParry){
            this->startCooldown();
        }
        this->successfulParry = false;
    };
    
    switch(lastHeading){
        case (Heading::DOWN):
            this->animatedSprite.startAnimation("PARRY_DOWN", false, finishAnimationFunction);
            break;
        case (Heading::UP):
            this->animatedSprite.startAnimation("PARRY_UP", false, finishAnimationFunction);
            break;
        case (Heading::LEFT):
            this->animatedSprite.startAnimation("PARRY_LEFT", false, finishAnimationFunction);
            break;
        case (Heading::RIGHT):
            this->animatedSprite.startAnimation("PARRY_RIGHT", false, finishAnimationFunction);
            break;
        default:
            this->animatedSprite.startAnimation("IDLE_DOWN", false, finishAnimationFunction);
            break;
    }
}

void Level_00_GO_BasicCharacter::startCooldown(){
    
    if(!this->shouldUpdate){
        return;
    }
    
    this->shouldUpdate = false;
    this->inCooldown = true;
    
    auto finishAnimationFunction = [this](){
        this->shouldUpdate = true;
        this->inCooldown = false;
    };
    
    switch(lastHeading){
        case (Heading::DOWN):
            this->animatedSprite.startAnimation("PARRYCOOLDOWN_DOWN", false, finishAnimationFunction);
            break;
        case (Heading::UP):
            this->animatedSprite.startAnimation("PARRYCOOLDOWN_UP", false, finishAnimationFunction);
            break;
        case (Heading::LEFT):
            this->animatedSprite.startAnimation("PARRYCOOLDOWN_LEFT", false, finishAnimationFunction);
            break;
        case (Heading::RIGHT):
            this->animatedSprite.startAnimation("PARRYCOOLDOWN_RIGHT", false, finishAnimationFunction);
            break;
        default:
            this->animatedSprite.startAnimation("IDLE_DOWN", false, finishAnimationFunction);
            break;
    }
}


void Level_00_GO_BasicCharacter::tryToUpdateAnimation(){
    
    if(this->attacking || this->parrying || this->inCooldown){
        return;
    }
    
    if(getVectorLength(velocity) > 0.0f){   //We are moving
        switch(lastHeading){
            case (Heading::DOWN):
                this->animatedSprite.startAnimation("RUN_DOWN", true, [](){});
                break;
            case (Heading::UP):
                this->animatedSprite.startAnimation("RUN_UP", true, [](){});
                break;
            case (Heading::LEFT):
                this->animatedSprite.startAnimation("RUN_LEFT", true, [](){});
                break;
            case (Heading::RIGHT):
                this->animatedSprite.startAnimation("RUN_RIGHT", true, [](){});
                break;
            default:
                this->animatedSprite.startAnimation("IDLE_DOWN", true, [](){});
                break;
        }
        
    }else{                                  //We are standing still
        
        switch(lastHeading){
            case (Heading::DOWN):
                this->animatedSprite.startAnimation("IDLE_DOWN", true, [](){});
                break;
            case (Heading::UP):
                this->animatedSprite.startAnimation("IDLE_UP", true, [](){});
                break;
            case (Heading::LEFT):
                this->animatedSprite.startAnimation("IDLE_LEFT", true, [](){});
                break;
            case (Heading::RIGHT):
                this->animatedSprite.startAnimation("IDLE_RIGHT", true, [](){});
                break;
            default:
                this->animatedSprite.startAnimation("IDLE_DOWN", true, [](){});
                break;
        }
    }
    
    
}

void Level_00_GO_BasicCharacter::draw(sf::RenderTarget * renderTarget){
    
    if(this->shouldUpdate){
        this->tryToUpdateAnimation();
    }
    
    this->animatedSprite.update();
    
    sf::Sprite mainCharSprite = this->animatedSprite.getCurrentSprite();
    
    mainCharSprite.move(this->position);
    
    renderTarget->draw(mainCharSprite);
    
}

