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


Level_00_GO_EnemyCharacter::Level_00_GO_EnemyCharacter(Scene* scene, sf::Vector2f position, AIObserver* observer) : Level_00_GO_BasicCharacter(scene, position),
hurtbox( sf::Vector2f (hurtboxSize_x, hurtboxSize_y) ,
        
        //Function that returs the position in which the location collider should be positioned
        [this]() -> sf::Vector2f{
            return sf::Vector2f(this->position.x-hurtboxOffset_x,this->position.y-hurtboxOffset_y);
        },
        
        //Function that deals with a collisions accordingly
        [this](ColliderType colType, sf::Vector2f vector, float value){
            
            if(colType == ColliderType::HITBOX){
                if(this->receiveDamage(value)){
                    this->startDash(vector, 50, 0.150, true);
                }
            }
            
        },
        
        //Type of the location collider
        ColliderType::HURTBOX, CollisionLayer::ENEMY_COLLIDER){
    
    this->controller = &myController;
    this->attackFunction = [this](){
        this->startAttack();
    };
    
    this->observer = observer;
    this->behaviour = new RuleBasedBehaviour(&(this->myController), (this->observer));


}

AIObserver* Level_00_GO_EnemyCharacter::getAIObserver(){
    return this->observer;
}


void Level_00_GO_EnemyCharacter::onStart(){
    
    Level_00_GO_BasicCharacter::onStart();
    
    if(!this->hurtbox.isRegistered()){
        this->hurtbox.registerCollider();
    }
    if(!this->hurtbox.isActive()){
        this->hurtbox.setActive(true);
    }
}

void Level_00_GO_EnemyCharacter::onEnd(){
    
    
    if(this->hurtbox.isActive()){
        this->hurtbox.setActive(false);
    }
    if(this->hurtbox.isRegistered()){
        this->hurtbox.unregisterCollider();
    }
    
    Level_00_GO_BasicCharacter::onEnd();
    
}

void Level_00_GO_EnemyCharacter::startAttack(){

    Level_00_GO_BasicCharacter::startAttack();
    
    InstantCircleCollider hitbox{
        .x = this->position.x + HITBOX_OFFSET_X,
        .y = this->position.y + HITBOX_OFFSET_Y,
        .r = this->attackRadious
    };
    
    game.getCollisionSystem()->checkCircleHitbox(&hitbox, CollisionLayer::FRIENDLY_COLLIDER, this->basicAttackDamage);

}

void Level_00_GO_EnemyCharacter::update(){
    
    Level_00_GO_BasicCharacter::update();
    
    this->behaviour->update();
    
}
