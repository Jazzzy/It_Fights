//
//  MenuScene.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "MenuScene.hpp"


MenuScene::MenuScene(MessageBus * messageBus) : Scene(messageBus){

    this->titleText =  new TitleText();
    //Add here all GameObjects necessary to with
    this->addGameObject(titleText);
    
}

MenuScene::~MenuScene(){
    delete this->titleText;
}
