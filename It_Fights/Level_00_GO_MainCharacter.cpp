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
extern Game * game;



Level_00_GO_MainCharacter::Level_00_GO_MainCharacter(Scene* scene, sf::Vector2f position, Position playerPosition) : Level_00_GO_BasicCharacter(scene, position, playerPosition){
    
    if(playerPosition == PLAYER_1){
    
    this->hurtbox = new BoxCollider ( sf::Vector2f (hurtboxSize_x, hurtboxSize_y) ,
                                            
                                            //Function that returs the position in which the location collider should be positioned
                                            [this]() -> sf::Vector2f{
                                                return sf::Vector2f(this->position.x-hurtboxOffset_x,this->position.y-hurtboxOffset_y);
                                            },
                                            
                                            //Function that deals with a collisions accordingly
                                            [this](ColliderType colType, sf::Vector2f vector, float value){
                                                if(colType == ColliderType::HITBOX){
                                                    if(this->receiveDamage(value,vector)){
                                                        this->startDash(vector, 50, 0.150, true);
                                                    }
                                                }
                                            },
                                            
                                            //Type of the location collider
                                     ColliderType::HURTBOX, CollisionLayer::FRIENDLY_COLLIDER);
        
        characterMarker.setOutlineColor(sf::Color(50.0f,255.0f,50.0f,80.0f));
        characterMarker.setFillColor(sf::Color(50.0f,255.0f,50.0f,80.0f));
        myController = new MainCharacterController(0);
        
        characterPublicName = "HUMAN PLAYER 1";

        
    }else{
        
        this->hurtbox = new BoxCollider ( sf::Vector2f (hurtboxSize_x, hurtboxSize_y) ,
                                         
                                         //Function that returs the position in which the location collider should be positioned
                                         [this]() -> sf::Vector2f{
                                             return sf::Vector2f(this->position.x-hurtboxOffset_x,this->position.y-hurtboxOffset_y);
                                         },
                                         
                                         //Function that deals with a collisions accordingly
                                         [this](ColliderType colType, sf::Vector2f vector, float value){
                                             if(colType == ColliderType::HITBOX){
                                                 if(this->receiveDamage(value,vector)){
                                                     this->startDash(vector, 50, 0.150, true);
                                                 }
                                             }
                                         },
                                         
                                         //Type of the location collider
                                         ColliderType::HURTBOX, CollisionLayer::ENEMY_COLLIDER);
        
        characterMarker.setOutlineColor(sf::Color(255.0f,0.0f,0.0f,80.0f));
        characterMarker.setFillColor(sf::Color(255.0f,0.0f,0.0f,80.0f));
        myController = new MainCharacterController(1);

        characterPublicName = "HUMAN PLAYER 2";

    
    }
    
    
    this->controller = myController;
    this->attackFunction = [this](bool area){
        this->startAttack(area);
    };
    
    
    
}

void Level_00_GO_MainCharacter::onStart(){

    Level_00_GO_BasicCharacter::onStart();
    
    if(!this->hurtbox->isRegistered()){
        this->hurtbox->registerCollider();
    }
    if(!this->hurtbox->isActive()){
        this->hurtbox->setActive(true);
    }
}

void Level_00_GO_MainCharacter::onEnd(){
    

    if(this->hurtbox->isActive()){
        this->hurtbox->setActive(false);
    }
    if(this->hurtbox->isRegistered()){
        this->hurtbox->unregisterCollider();
    }
    
    Level_00_GO_BasicCharacter::onEnd();
    
}

void Level_00_GO_MainCharacter::startAttackCollision(bool area){

    InstantCircleCollider hitbox{
        .x = this->position.x + HITBOX_OFFSET_X,
        .y = this->position.y + HITBOX_OFFSET_Y,
        .r = this->attackRadious,
        .direction_4 = this->getDirection_4(),
        .area = area
    };
    
    if(this->playerNumber == PLAYER_1){
        game->getCollisionSystem()->checkCircleHitbox(&hitbox, CollisionLayer::ENEMY_COLLIDER, this->basicAttackDamage);
    }else{
        game->getCollisionSystem()->checkCircleHitbox(&hitbox, CollisionLayer::FRIENDLY_COLLIDER, this->basicAttackDamage);
    }
}

void Level_00_GO_MainCharacter::startAttack(bool area){
    
    Level_00_GO_BasicCharacter::startAttack(this->lastDirection_4);
    
    this->startAttackCollision(area);

}

void Level_00_GO_MainCharacter::parryCounter(sf::Vector2f direction){

    Level_00_GO_BasicCharacter::startAttack(this->lastDirection_4);
    
    this->startAttackCollision(true);
    
}


void Level_00_GO_MainCharacter::update(){
    
    Level_00_GO_BasicCharacter::update();
 
}

void Level_00_GO_MainCharacter::draw(sf::RenderTarget * renderTarget){

    Level_00_GO_BasicCharacter::draw(renderTarget);
    
    
}

void Level_00_GO_MainCharacter::die(){
    
    Level_00_GO_BasicCharacter::die();

}




















