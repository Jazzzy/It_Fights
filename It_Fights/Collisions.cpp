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

}


Collisions::~Collisions(){


}


void Collisions::update(){

}

void Collisions::draw(sf::RenderTarget *renderTarget){

}


void Collisions::onNotify(Message message){


}

void Collisions::registerRectangleCollider(float width,
                                           float heigth,
                                           std::function<std::pair<float,float>()>getOriginFunc ,
                                           std::function<void(ColliderType)>onCollisionCallback,
                                           ColliderType colliderType){
    
    
    ColliderFuncs funcs{
        .getOriginFunc=getOriginFunc,
        .onCollisionCallback=onCollisionCallback
    };
    
    RectangleCollider newRectangleCollider{
        .width = width,
        .heigth = heigth,
        .funcs = funcs
    };

    this->rectColVector.push_back(newRectangleCollider);

}


void Collisions::check__Rect_Rect__Collisions(){
    
    
    
}



