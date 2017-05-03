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
    std::function<sf::Vector2f()> getOriginFunc;
    std::function<void(ColliderType, sf::Vector2f)> onCollisionCallback;
} ColliderFuncs;


typedef struct {
    bool active;
    unsigned int id;
    ColliderFuncs funcs;
    ColliderType colType;
    sf::Vector2f size;
    sf::Vector2f lastOrigin;
    bool updated;
    
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
    
    //Register and unregister colliders
    unsigned int registerRectangleCollider(RectangleCollider * rectangleCollider);
    void unregisterRectangleCollider(unsigned int id);
    
    //Activate and deactivate colliders
    void activateCollider (unsigned int id);
    void deactivateCollider (unsigned int id);
    
    
    void update();
    void draw(sf::RenderTarget * renderTarget);
    
private:
    bool shouldDraw;
    
    
    RectangleCollider* currentInvertedBox;
    
    void onNotify (Message message);
    
    
    unsigned int colliderCounter;
    std::map<unsigned int, RectangleCollider*> rectColMap;

    
    void check__Rect_Rect__Collisions();
    void check__Box_Rect__Collisions();
    
    
    bool check2Rects(RectangleCollider * col1, RectangleCollider * col2, sf::Vector2f* vector1, sf::Vector2f* vector2);
    bool checkBoxRect(RectangleCollider * box, RectangleCollider * col, sf::Vector2f* vector);
    
    void drawRectangleColliders(sf::RenderTarget *renderTarget);
    
};

#endif /* Collisions_hpp */





































/*eof*/
