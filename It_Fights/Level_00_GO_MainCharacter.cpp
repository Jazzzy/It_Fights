//
//  Level_00_GO_MainCharacter.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 22/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Level_00_GO_MainCharacter.hpp"
#include <fstream>
#include "ResourcePath.hpp"
#include "Message.hpp"
#include "SomeMath.hpp"

#include <SFML/Window/Joystick.hpp>


#include "Game.hpp"
extern Game game;

Level_00_GO_MainCharacter_AnimatedSprite::Level_00_GO_MainCharacter_AnimatedSprite() :
AnimatedSprite("prota_0.2_anim_data.json", "prota_0.2_anim_spritesheet.png", "prota_0.2_animations.json"){

    this->startAnimation("RUN_UP", true, [](){});
    
}






/****************************/
/*      TRUE GAMEOBJECT     */
/****************************/


//@@TODO Implementar a colisión ca "caixa" exterior pra que non se salga o chaval

//@@TODO Implementar os ataques :D

Level_00_GO_MainCharacter::Level_00_GO_MainCharacter(Scene * scene){
    
    this->scene=scene;

    this->position = sf::Vector2f(100,150);
    this->walkingSpeed = 130.0f;
    this->lastHeading = Heading::DOWN;
    
    
}
Level_00_GO_MainCharacter::~Level_00_GO_MainCharacter(){}



Heading Level_00_GO_MainCharacter::calculateHeading(sf::Vector2f velocity){

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

#define VECTOR_LENGTH_LIMIT 0.4f

void Level_00_GO_MainCharacter::update(){
    
    //@@TODO Listen Here for inputs from the user :D
    
    bool connected = sf::Joystick::isConnected(0);

    if(!connected){
        Message msgNoController("MSG_NO_CONTROLLER"); //@@TODO deal with this.
        msgNoController.setRelevantForConsole(true);
        this->scene->send(msgNoController);
        return;
    }
    
    
    float axis_x = sf::Joystick::getAxisPosition(0, sf::Joystick::X)/100.f;
    float axis_y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y)/100.f;
    
    sf::Vector2f movementVector(axis_x,axis_y);
    
    if(getVectorLength(movementVector)>1.0f){
        movementVector = getNormalizedVector(movementVector);
    }else if(getVectorLength(movementVector)>VECTOR_LENGTH_LIMIT){
    }else{
        movementVector = sf::Vector2f(0,0);
    }
    
    //this->walkingSpeed*game.getDeltaClock()->getDeltaTime()
    
    velocity = (movementVector*this->walkingSpeed*game.getDeltaClock()->getDeltaTime());
    
    this->lastHeading = this->calculateHeading(velocity);
    
    this->position += velocity;
    
    
}

void Level_00_GO_MainCharacter::tryToUpdateAnimation(){

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

void Level_00_GO_MainCharacter::draw(sf::RenderTarget * renderTarget){

    
    this->tryToUpdateAnimation();
    
    this->animatedSprite.update();

    
    sf::Sprite mainCharSprite = this->animatedSprite.getCurrentSprite();
    
    
    mainCharSprite.move(this->position);
    
    renderTarget->draw(mainCharSprite);

}
