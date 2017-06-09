//
//  Level_00_GO_EnemyCharacter.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 29/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Level_00_GO_EnemyCharacter.hpp"
#include "DebugUtilities.hpp"
#include "Game.hpp"
#include "RuleBasedBehaviour.hpp"
extern Game game;


Level_00_GO_EnemyCharacter::Level_00_GO_EnemyCharacter(Scene* scene, sf::Vector2f position, AIObserver* observer, Position playerPosition) : Level_00_GO_BasicCharacter(scene, position){
    
    if(playerPosition == PLAYER_1){
        
        this->hurtbox = new BoxCollider(sf::Vector2f (hurtboxSize_x, hurtboxSize_y) ,
                                        
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
        characterPublicName = "AGENT 1";

        
    }else{
        this->hurtbox = new BoxCollider(sf::Vector2f (hurtboxSize_x, hurtboxSize_y) ,
                                        
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
        characterPublicName = "AGENT 2";

    }
    
    this->controller = &myController;
    this->attackFunction = [this](bool area){
        this->startAttack(area);
    };
    
    this->observer = observer;
    
    
    
    
    
    
    /********************************************************************************************/
    /*************    HERE WE SELECT WHAT BEHAVIOUR WE USE FOR THE ENEMY ACTIONS    *************/
    /********************************************************************************************/
    
    this->behaviour = new RuleBasedBehaviour(&(this->myController), (this->observer));
    
    /********************************************************************************************/
    /********************************************************************************************/
    
    
    
}

Level_00_GO_EnemyCharacter::~Level_00_GO_EnemyCharacter(){
    delete this->behaviour;
    delete this->hurtbox;
}

AIObserver* Level_00_GO_EnemyCharacter::getAIObserver(){
    return this->observer;
}


void Level_00_GO_EnemyCharacter::onStart(){
    
    Level_00_GO_BasicCharacter::onStart();
    
    this->behaviour->startThread();
    
    if(!this->hurtbox->isRegistered()){
        this->hurtbox->registerCollider();
    }
    if(!this->hurtbox->isActive()){
        this->hurtbox->setActive(true);
    }
}

void Level_00_GO_EnemyCharacter::onEnd(){
    
    this->behaviour->stopThread();
    
    if(this->hurtbox->isActive()){
        this->hurtbox->setActive(false);
    }
    if(this->hurtbox->isRegistered()){
        this->hurtbox->unregisterCollider();
    }
    
    Level_00_GO_BasicCharacter::onEnd();
    
}

void Level_00_GO_EnemyCharacter::startAttackCollision(bool area){

    InstantCircleCollider hitbox{
        .x = this->position.x + HITBOX_OFFSET_X,
        .y = this->position.y + HITBOX_OFFSET_Y,
        .r = this->attackRadious,
        .direction_4 = this->getDirection_4(),
        .area = area
    };
    
    game.getCollisionSystem()->checkCircleHitbox(&hitbox, CollisionLayer::FRIENDLY_COLLIDER, this->basicAttackDamage);
    
}

void Level_00_GO_EnemyCharacter::startAttack(bool area){
    
    Level_00_GO_BasicCharacter::startAttack(this->lastDirection_4);
    
    this->startAttackCollision(area);
    
}

void Level_00_GO_EnemyCharacter::parryCounter(sf::Vector2f direction){
    
    Level_00_GO_BasicCharacter::startAttack(this->lastDirection_4);
    
    this->startAttackCollision(true);
    
}

void Level_00_GO_EnemyCharacter::update(){
    
    Level_00_GO_BasicCharacter::update();
    
    //this->behaviour->update();
    
}

void Level_00_GO_EnemyCharacter::die(){
    Level_00_GO_BasicCharacter::die();
}
