//
//  BoxCollider.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 26/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "BoxCollider.hpp"
#include "Game.hpp"
extern Game game;

BoxCollider::BoxCollider(float width,
                         float heigth,
                         std::function<std::pair<float,float>()>getOriginFunc ,
                         std::function<void(ColliderType,std::pair<float, float>)>onCollisionCallback,
                         ColliderType colliderType){
    
    ColliderFuncs funcs{
        .getOriginFunc=getOriginFunc,
        .onCollisionCallback=onCollisionCallback
    };
    
    this->collider = RectangleCollider{
        .active = false,
        .id = 0,
        .width = width,
        .heigth = heigth,
        .funcs = funcs,
        .colType = colliderType,
        .updated = false
    };
    
    this->registered = false;
    
    return;
}

BoxCollider::~BoxCollider(){
    
    if(this->isActive()){
        this->setUnactive();
    }
    
    if(this->isRegistered()){
        this->unregisterCollider();
    }
    
}

void BoxCollider::setActive(){
    this->collider.active = true;
}


void BoxCollider::setUnactive(){
    this->collider.active = false;
}

bool BoxCollider::isRegistered(){
    return this->registered;
}

bool BoxCollider::isActive(){
    return this->collider.active;
}

void BoxCollider::registerCollider(){
    game.getCollisionSystem()->registerRectangleCollider(&this->collider);
    this->registered = true;
}

void BoxCollider::unregisterCollider(){
    game.getCollisionSystem()->unregisterRectangleCollider(this->collider.id);
    this->registered = false;
}
