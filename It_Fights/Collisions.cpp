//
//  Collisions.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 23/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Collisions.hpp"
#include "Systems.hpp"


Collisions::Collisions(MessageBus * messageBus) : BusNode(Systems::S_Collisions,messageBus){
    
    this->colliderCounter = 0;
    
}


Collisions::~Collisions(){
    
    
}


void Collisions::update(){
    
}

void Collisions::draw(sf::RenderTarget *renderTarget){
    
}


void Collisions::onNotify(Message message){
    
    
}

unsigned int Collisions::registerRectangleCollider(RectangleCollider * rectangleCollider){
    
    rectangleCollider->id = this->colliderCounter++;
    
    this->rectColMap[rectangleCollider->id]=(rectangleCollider);
    
    return rectangleCollider->id;
    
}


void Collisions::check__Rect_Rect__Collisions(){
    
    
    
}



