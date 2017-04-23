//
//  Collisions.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 23/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Collisions_hpp
#define Collisions_hpp

#include "BusNode.hpp"
#include <functional>
#include "Drawable.hpp"



/*
 
 It could be a good idea to send a message from the callback
 function indicating something just has been hit, for example
 if the collider is a hitbox then we could
 
 
 Maybe in the function for the collision callback for a moving object we should send
 a vector that applyed to the position would solve the collision :D
 This could be usefull when colliding circles for them to slide.
 
 */

enum ColliderType{
    WALL,
    INVERTED_BOX,
    MOVING_OBJECT
};

enum CollisionBehaviour{
    Not_Move
};

typedef struct {
    std::function<std::pair<float,float>()> getOriginFunc;
    std::function<void(ColliderType)> onCollisionCallback;
} ColliderFuncs;



typedef struct {
    float width;
    float heigth;
    ColliderFuncs funcs;
    ColliderType colType;
} RectangleCollider;



typedef struct {
    float width;
    float heigth;
    ColliderFuncs funcs;
    ColliderType colType;
} CircleCollider;



class Collisions : BusNode, Drawable {
public:
    Collisions(MessageBus * messageBus);
    ~Collisions();
    
    void registerRectangleCollider(float width,
                                   float heigth,
                                   std::function<std::pair<float,float>()>getOriginFunc ,
                                   std::function<void(ColliderType)>onCollisionCallback,
                                   ColliderType colliderType);
    void update();
    void draw(sf::RenderTarget * renderTarget);
    
private:
    void onNotify (Message message);
    
    
    void check__Rect_Rect__Collisions();
    
    std::vector<RectangleCollider> rectColVector;
    
};

#endif /* Collisions_hpp */
