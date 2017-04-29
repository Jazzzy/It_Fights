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



//@@TODO Implementar os ataques :D


//Sizes for the location collider of the character
#define LocationColliderSize_x 8
#define LocationColliderSize_y 8


//Offsets for the locaiton collider of the character relative to its position
#define LocationColliderOffset_x 4
#define LocationColliderOffset_y 3

Level_00_GO_BasicCharacter::Level_00_GO_BasicCharacter(sf::Vector2f position):
locationCollider( LocationColliderSize_x, LocationColliderSize_y ,
                 
                 //Function that returs the position in which the location collider should be positioned
                 [this]() -> std::pair<float,float>{
                     return std::make_pair(this->position.x-LocationColliderOffset_x,this->position.y-LocationColliderOffset_y);
                 },
                 
                 //Function that deals with a collisions accordingly
                 [this](ColliderType colType, std::pair<float, float> vector){
                     
                     if(colType == ColliderType::INVERTED_BOX || colType == WALL){
                         this->manageCollisionWithWall(sf::Vector2f(vector.first, vector.second));
                     }else if(colType == ColliderType::MOVING_OBJECT){
                         this->manageCollisionWithMovingObject(sf::Vector2f(vector.first, vector.second));
                     }
                     
                 },
                 
                 //Type of the location collider
                 ColliderType::MOVING_OBJECT)
{
    
    
    this->position = position;
    this->oldPosition = this->position;
    this->walkingSpeed = 130.0f;
    this->lastHeading = Heading::DOWN;
    
    
}
Level_00_GO_BasicCharacter::~Level_00_GO_BasicCharacter(){}


void Level_00_GO_BasicCharacter::manageCollisionWithWall( sf::Vector2f vector ){
    
    this->oldPosition = this->position;
    this->position += vector;
    
}

void Level_00_GO_BasicCharacter::manageCollisionWithMovingObject(sf::Vector2f velocity){
    
    if(this->position == oldPosition){
        return;
    }
    this->position = this->oldPosition;
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


void Level_00_GO_BasicCharacter::update(){
    
    if(!this->locationCollider.isRegistered()){
        this->locationCollider.registerCollider();
    }
    if(!this->locationCollider.isActive()){
        this->locationCollider.setActive();
    }
    
}

sf::Vector2f Level_00_GO_BasicCharacter::getPosition(){
    return this->position;
}

void Level_00_GO_BasicCharacter::tryToUpdateAnimation(){
    
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
    
    
    this->tryToUpdateAnimation();
    
    this->animatedSprite.update();
    
    
    sf::Sprite mainCharSprite = this->animatedSprite.getCurrentSprite();
    
    
    mainCharSprite.move(this->position);
    
    renderTarget->draw(mainCharSprite);
    
}
