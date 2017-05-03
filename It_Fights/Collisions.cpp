//
//  Collisions.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 23/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Collisions.hpp"
#include "Systems.hpp"
#include "DebugUtilities.hpp"


Collisions::Collisions(MessageBus * messageBus) : BusNode(Systems::S_Collisions,messageBus){
    
    this->colliderCounter = 1;
    
    this->shouldDraw = false;
    
}


Collisions::~Collisions(){
    
    
}


void Collisions::update(){
    
    this->check__Box_Rect__Collisions();
    this->check__Rect_Rect__Collisions();
    
}

void Collisions::draw(sf::RenderTarget *renderTarget){
    
    if(shouldDraw){
        this->drawRectangleColliders(renderTarget);
    }
}

void Collisions::drawRectangleColliders(sf::RenderTarget *renderTarget){
    
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(this->currentInvertedBox->size.x, this->currentInvertedBox->size.y));
    rectangle.setOutlineThickness(0);
    rectangle.setPosition(this->currentInvertedBox->lastOrigin.x, this->currentInvertedBox->lastOrigin.y);
    rectangle.setFillColor(sf::Color(230.f,0.f,0.f,40.f));
    renderTarget->draw(rectangle);
    
    
    for(auto it1 = this->rectColMap.begin() ; it1 != this->rectColMap.end() ; ++it1){
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(it1->second->size.x, it1->second->size.y));
        rectangle.setOutlineThickness(0);
        rectangle.setPosition(it1->second->lastOrigin.x, it1->second->lastOrigin.y);
        
        switch (it1->second->colType){
                
            default:
                rectangle.setFillColor(sf::Color(0.f,230.f,0.f,100.f));
                break;
        }
        
        renderTarget->draw(rectangle);
    }
    
}


void Collisions::onNotify(Message message){
    
    if(message.getEvent().compare("MSG_TOGGLE_SHOW_COLLISIONS")==0){
        this->shouldDraw = !(this->shouldDraw);
    }
    
    
}

unsigned int Collisions::registerRectangleCollider(RectangleCollider * rectangleCollider){
    
    
    rectangleCollider->id = this->colliderCounter++;
    
    
    if(rectangleCollider->colType == INVERTED_BOX){
        this->currentInvertedBox = rectangleCollider;
    }else{
        this->rectColMap.insert(std::make_pair(rectangleCollider->id,rectangleCollider));
    }
    
    return rectangleCollider->id;
    
}


void Collisions::unregisterRectangleCollider(unsigned int id){
    this->rectColMap.erase(id);
}


void Collisions::activateCollider(unsigned int id){
    (this->rectColMap[id])->active = true;
}


void Collisions::deactivateCollider(unsigned int id){
    (this->rectColMap[id])->active = false;
}



/*Also sets the updated to false*/
void Collisions::check__Rect_Rect__Collisions(){
    
    RectangleCollider *col1, *col2;
    
    for(auto it1 = this->rectColMap.begin() ; it1 != this->rectColMap.end() ; ++it1){
        
        col1 = it1->second;
        
        if(!col1->active){
            continue;
        }
        
        if(!col1->updated){
            col1->lastOrigin = col1->funcs.getOriginFunc();
            col1->updated = true;
        }
        
        for(auto it2 = (std::next(it1, 1)) ; it2 != this->rectColMap.end(); ++it2){
            col2 = it2->second;
            
            if(!col2->active){
                continue;
            }
            
            if(!col2->updated){
                col2->lastOrigin = col2->funcs.getOriginFunc();
                col2->updated = true;
            }
            
            sf::Vector2f vector1 = sf::Vector2f(0.0f, 0.0f);
            sf::Vector2f vector2 = sf::Vector2f(0.0f, 0.0f);
            
            
            bool col = this->check2Rects(col1, col2, &vector1, &vector2);
            
            if(col){
                col1->funcs.onCollisionCallback(col2->colType,vector1);
                col2->funcs.onCollisionCallback(col1->colType,vector2);
            }
            
        }
        col1->updated = false;
    }
    
    
}

void Collisions::check__Box_Rect__Collisions(){
    
    RectangleCollider *collider;
    
    if(!this->currentInvertedBox->updated){
        this->currentInvertedBox->lastOrigin = this->currentInvertedBox->funcs.getOriginFunc();
        this->currentInvertedBox->updated = true;
    }
    
    for(auto it1 = this->rectColMap.begin() ; it1 != this->rectColMap.end() ; ++it1){
        
        collider = it1->second;
        
        if(!collider->active){
            continue;
        }
        
        if(!collider->updated){
            collider->lastOrigin = collider->funcs.getOriginFunc();
            collider->updated = true;
        }
        
        sf::Vector2f vector = sf::Vector2f(0.0f,0.0f);
        bool inside = this->checkBoxRect(this->currentInvertedBox,collider ,&vector);
        
        if(!inside){
            collider->funcs.onCollisionCallback(INVERTED_BOX,vector);
        }
        
    }
    
    this->currentInvertedBox->updated = false;
    
    
    
}


bool Collisions::check2Rects(RectangleCollider * col1, RectangleCollider * col2, sf::Vector2f* vector1, sf::Vector2f* vector2){
    
    
    
    sf::Vector2f halfSize1 = sf::Vector2f((col1->size.x / 2.),(col1->size.y / 2.));
    sf::Vector2f halfSize2 = sf::Vector2f((col2->size.x / 2.),(col2->size.y / 2.));
    
    
    sf::Vector2f center1 =  sf::Vector2f(col1->lastOrigin.x + halfSize1.x, col1->lastOrigin.y + halfSize1.y);
    sf::Vector2f center2 =  sf::Vector2f(col2->lastOrigin.x + halfSize2.x, col2->lastOrigin.y + halfSize2.y);
    
    sf::Vector2f centerDiff = sf::Vector2f((center1.x - center2.x),(center1.y - center2.y));
    
    sf::Vector2f componente;
    componente.x = halfSize1.x + halfSize2.x - fabs(centerDiff.x);
    componente.y = halfSize1.y + halfSize2.y - fabs(centerDiff.y);
    
    if(componente.x < 0. || componente.y < 0.) return false;
    
    
    if(fabs(centerDiff.x) > fabs(centerDiff.y) ){
        
        //Instead of halving each component we could use normalized weights of both colliders
        if(center1.x < center2.x ){
            vector1->x = -componente.x/2.;
            vector2->x = componente.x/2.;
        }else{
            vector1->x = componente.x/2.;
            vector2->x = -componente.x/2.;
        }
        
    }else{
        
        if(center1.y < center2.y ){
            vector1->y = -componente.y/2.;
            vector2->y = componente.y/2.;
        }else{
            vector1->y = componente.y/2.;
            vector2->y = -componente.y/2.;
        }
        
    }
    
    return true;
    
    
    //    bool notColliding = false;
    //
    //    float distance1x = (col1->lastOrigin.first - (col2->lastOrigin.first + col2->width));   // > 0
    //    float distance1y = col1->lastOrigin.second - (col2->lastOrigin.second + col2->heigth);  // > 0
    //    float distance0x = (col1->lastOrigin.first + col1->width) - col2->lastOrigin.first;     // < 0
    //    float distance0y = (col1->lastOrigin.second + col1->heigth) - col2->lastOrigin.second;  // < 0
    //
    //    //@@TODO: Fix this for all axis
    //
    //    if(distance1x > 0){
    //        notColliding = true;
    //    }else{
    //        vector1->first += distance1x/2;
    //        vector2->first -= distance1x/2;
    //    }
    //
    //    if(distance1y > 0){
    //        notColliding = true;
    //    }else{
    //        vector1->second += distance1y/2;
    //        vector1->second -= distance1y/2;
    //    }
    //
    //    if(distance0x < 0){
    //        notColliding = true;
    //    }else{
    //        vector1->first += distance0x/2;
    //        vector1->first -= distance0x/2;
    //    }
    //
    //    if(distance0y < 0){
    //        notColliding = true;
    //    }else{
    //        vector1->second += distance0y/2;
    //        vector1->second -= distance0y/2;
    //    }
    //
    //    return !notColliding;
    
    //      Old collision checking without vector generation
    
    //    if(!(col1->lastOrigin.first > (col2->lastOrigin.first + col2->width)      ||
    //       (col1->lastOrigin.first + col1->width) < col2->lastOrigin.first      ||
    //       col1->lastOrigin.second > (col2->lastOrigin.second + col2->heigth)   ||
    //       (col1->lastOrigin.second + col1->heigth) < col2->lastOrigin.second   ))
    //    {
    //
    //
    //        printv(true);
    //        //Boys!! We have a collision
    //        return true;
}



#define box0x (box->lastOrigin.x)
#define box0y (box->lastOrigin.y)
#define box1x ((box->lastOrigin.x) + (box->size.x))
#define box1y ((box->lastOrigin.y) + (box->size.y))

#define col0x (col->lastOrigin.x)
#define col0y (col->lastOrigin.y)
#define col1x ((col->lastOrigin.x) + (col->size.x))
#define col1y ((col->lastOrigin.y) + (col->size.y))

bool Collisions::checkBoxRect(RectangleCollider * box, RectangleCollider * col , sf::Vector2f* vector){
    
    bool inside = true;
    
    float distance1x = box1x - col1x;
    float distance1y = box1y - col1y;
    float distance0x = box0x - col0x;
    float distance0y = box0y - col0y;
    
    if(distance1x < 0){
        vector->x += distance1x;
        inside = false;
    }
    
    if(distance1y < 0){
        vector->y += distance1y;
        inside = false;
    }
    
    if(distance0x > 0){
        vector->x += distance0x;
        inside = false;
    }
    
    if(distance0y > 0){
        vector->y += distance0y;
        inside = false;
    }
    
    return inside;
}





