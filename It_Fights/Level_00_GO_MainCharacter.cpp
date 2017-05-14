//
//  Level_00_GO_MainCharacter.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 22/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Level_00_GO_MainCharacter.hpp"
#include "SomeMath.hpp"
#include "Game.hpp"
#include "Clock.hpp"
#include "DebugUtilities.hpp"
extern Game game;



Level_00_GO_MainCharacter::Level_00_GO_MainCharacter(Scene* scene, sf::Vector2f position) : Level_00_GO_BasicCharacter(scene, position),
hurtbox( sf::Vector2f (hurtboxSize_x, hurtboxSize_y) ,
        
        //Function that returs the position in which the location collider should be positioned
        [this]() -> sf::Vector2f{
            return sf::Vector2f(this->position.x-hurtboxOffset_x,this->position.y-hurtboxOffset_y);
        },
        
        //Function that deals with a collisions accordingly
        [this](ColliderType colType, sf::Vector2f vector, float value){
            
            if(colType == ColliderType::HITBOX){
                this->startDash(vector, 50, 0.150, true);
            }
        },
        
        //Type of the location collider
        ColliderType::HURTBOX, CollisionLayer::FRIENDLY_COLLIDER){
    
}


#define VECTOR_LENGTH_LIMIT 0.2f
#define HITBOX_OFFSET_X (0)
#define HITBOX_OFFSET_Y (-15)

void Level_00_GO_MainCharacter::startAttack(){
    
    Level_00_GO_BasicCharacter::startAttack();
    
    InstantCircleCollider hitbox{
        .x = this->position.x + HITBOX_OFFSET_X,
        .y = this->position.y + HITBOX_OFFSET_Y,
        .r = this->attackRadious
    };
    
    game.getCollisionSystem()->checkCircleHitbox(&hitbox, CollisionLayer::ENEMY_COLLIDER, this->basicAttackDamage);

}


void Level_00_GO_MainCharacter::update(){
    
    if(!this->hurtbox.isRegistered()){
        this->hurtbox.registerCollider();
    }
    if(!this->hurtbox.isActive()){
        this->hurtbox.setActive(true);
    }
    
    
    Level_00_GO_BasicCharacter::update();
    
    
    if(this->dashing){
        this->dash();
        return;
    }
    
    if(!this->shouldUpdate){
        return;
    }
    
    bool connected = sf::Joystick::isConnected(0);
    
    
    if(!connected){
        return;
    }
    
    
    bool attackButtonPressed = (sf::Joystick::isButtonPressed(0, 0));
    
    
    if(attackButtonPressed)
        this->startAttack();
    
    float axis_x = sf::Joystick::getAxisPosition(0, sf::Joystick::X)/100.f;
    float axis_y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y)/100.f;
    
    sf::Vector2f movementVector(axis_x,axis_y);
    
    if(getVectorLength(movementVector)>1.0f){
        movementVector = getNormalizedVector(movementVector);
    }else if(getVectorLength(movementVector)>VECTOR_LENGTH_LIMIT){
    }else{
        movementVector = sf::Vector2f(0,0);
    }
        
    velocity = (movementVector*this->walkingSpeed * Clock::Instance().getDeltaTime());
    
    this->lastHeading = this->calculateHeading(velocity);
    
    this->oldPosition = this->position;
    this->position += velocity;
    
}
