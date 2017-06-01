//
//  MenuOptions.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/6/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "MenuOptions.hpp"
#include "ResourceManager.hpp"


MenuOptions::MenuOptions(Scene * scene) : GameObject(scene){

    this->mainFont = ResourceManager::Instance().getFont("playfair");

}

MenuOptions::~MenuOptions(){

}

void MenuOptions::update(){


}


void MenuOptions::draw(sf::RenderTarget *renderTarget){


}
