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
    rectangle.setSize(sf::Vector2f(this->currentInvertedBox->width, this->currentInvertedBox->heigth));
    rectangle.setOutlineThickness(0);
    rectangle.setPosition(this->currentInvertedBox->lastOrigin.first, this->currentInvertedBox->lastOrigin.second);
    rectangle.setFillColor(sf::Color(230.f,0.f,0.f,40.f));
    renderTarget->draw(rectangle);
    
    
    for(auto it1 = this->rectColMap.begin() ; it1 != this->rectColMap.end() ; ++it1){
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(it1->second->width, it1->second->heigth));
        rectangle.setOutlineThickness(0);
        rectangle.setPosition(it1->second->lastOrigin.first, it1->second->lastOrigin.second);
        
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
        
        if(!col1->updated){
            col1->lastOrigin = col1->funcs.getOriginFunc();
            col1->updated = true;
        }
        
        for(auto it2 = (std::next(it1, 1)) ; it2 != this->rectColMap.end(); ++it2){
            col2 = it2->second;
            
            if(!col2->updated){
                col2->lastOrigin = col2->funcs.getOriginFunc();
                col2->updated = true;
            }
            
            bool col = this->check2Rects(col1, col2);
            
            std::pair<float, float> vector;
            
            if(col){
                col1->funcs.onCollisionCallback(col2->colType,vector);
                col2->funcs.onCollisionCallback(col1->colType,vector);
            }
            
        }
        col1->updated = false;
    }
    
    
}

bool Collisions::check2Rects(RectangleCollider * col1, RectangleCollider * col2){
    
    if(col1->lastOrigin.first < (col2->lastOrigin.first + col2->width)      &&
       (col1->lastOrigin.first + col1->width) > col2->lastOrigin.first      &&
       col1->lastOrigin.second < (col2->lastOrigin.second + col2->heigth)   &&
       (col1->lastOrigin.second + col1->heigth) > col2->lastOrigin.second   ){
        //Boys!! We have a collision
        return true;
        
        
    }
    
    return false;
}

void Collisions::check__Box_Rect__Collisions(){
    
    RectangleCollider *collider;
    
    if(!this->currentInvertedBox->updated){
        this->currentInvertedBox->lastOrigin = this->currentInvertedBox->funcs.getOriginFunc();
        this->currentInvertedBox->updated = true;
    }
    
    for(auto it1 = this->rectColMap.begin() ; it1 != this->rectColMap.end() ; ++it1){
        
        collider = it1->second;
        
        if(!collider->updated){
            collider->lastOrigin = collider->funcs.getOriginFunc();
            collider->updated = true;
        }
        
        std::pair<float, float> vector = std::make_pair(0.0f,0.0f);
        bool inside = this->checkBoxRect(this->currentInvertedBox,collider ,&vector);
        
        if(!inside){
            collider->funcs.onCollisionCallback(INVERTED_BOX,vector);
        }
        
    }
    
    this->currentInvertedBox->updated = false;
    
    
    
}


#define box0x (box->lastOrigin.first)
#define box0y (box->lastOrigin.second)
#define box1x ((box->lastOrigin.first) + (box->width))
#define box1y ((box->lastOrigin.second) + (box->heigth))

#define col0x (col->lastOrigin.first)
#define col0y (col->lastOrigin.second)
#define col1x ((col->lastOrigin.first) + (col->width))
#define col1y ((col->lastOrigin.second) + (col->heigth))

bool Collisions::checkBoxRect(RectangleCollider * box, RectangleCollider * col , std::pair<float,float>* vector){
    
    bool inside = true;
    
    float distance1x = box1x - col1x;
    float distance1y = box1y - col1y;
    float distance0x = box0x - col0x;
    float distance0y = box0y - col0y;
    
    if(distance1x < 0){
        vector->first += distance1x;
        inside = false;
    }
    
    if(distance1y < 0){
        vector->second += distance1y;
        inside = false;
    }
    
    if(distance0x > 0){
        vector->first += distance0x;
        inside = false;
    }
    
    if(distance0y > 0){
        vector->second += distance0y;
        inside = false;
    }
    
    return inside;
}





