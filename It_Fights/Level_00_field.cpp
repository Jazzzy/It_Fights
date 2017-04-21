//
//  level_00_field.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 21/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Level_00_field.hpp"
#include "Window.hpp"

Level_00_field::Level_00_field(MessageBus * messageBus) :
    Scene(messageBus),
    level_00_GO_Field(),
    view(sf::FloatRect(0,0,INTERNAL_RESOLUTION_X,INTERNAL_RESOLUTION_Y))
{
    
    //Add here all GameObjects necessary to with "this->addGameObject(GameObject * gameObject)"
    
    this->addGameObject(&level_00_GO_Field);
    
    this->localUpdateFunction = [&](){ this->localUpdateImplemented(); };
    
    this->viewptr = &view;
    
    
    
}

Level_00_field::~Level_00_field(){
    
}

void Level_00_field::localUpdateImplemented(){
    
}
