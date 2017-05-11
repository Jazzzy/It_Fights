//
//  Level_00_GO_EnemyCharacter.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 29/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Level_00_GO_EnemyCharacter.hpp"
#include "DebugUtilities.hpp"

Level_00_GO_EnemyCharacter::Level_00_GO_EnemyCharacter(Scene* scene, sf::Vector2f position) : Level_00_GO_BasicCharacter(scene, position),
hurtbox( sf::Vector2f (hurtboxSize_x, hurtboxSize_y) ,
        
        //Function that returs the position in which the location collider should be positioned
        [this]() -> sf::Vector2f{
            return sf::Vector2f(this->position.x-hurtboxOffset_x,this->position.y-hurtboxOffset_y);
        },
        
        //Function that deals with a collisions accordingly
        [this](ColliderType colType, sf::Vector2f vector, float value){
            
            if(colType == ColliderType::HITBOX){
                prints("HIT");
                this->startDash(vector, 50, 0.150, true);
            }
            
        },
        
        //Type of the location collider
        ColliderType::HURTBOX, CollisionLayer::ENEMY_COLLIDER){

}


void Level_00_GO_EnemyCharacter::update(){
    
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
    
}
