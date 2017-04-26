//
//  BoxCollider.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 26/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "BoxCollider.hpp"


BoxCollider::BoxCollider(float width,
                         float heigth,
                         std::function<std::pair<float,float>()>getOriginFunc ,
                         std::function<void(ColliderType)>onCollisionCallback,
                         ColliderType colliderType){

    ColliderFuncs funcs{
        .getOriginFunc=getOriginFunc,
        .onCollisionCallback=onCollisionCallback
    };
    
    this->collider = RectangleCollider{
        .width = width,
        .heigth = heigth,
        .funcs = funcs,
        .colType = colliderType
    };
    
    return;
}

BoxCollider::~BoxCollider(){

}

void BoxCollider::registerCollider(){


}

void BoxCollider::unregisterCollider(){

    
}
