//
//  TitleText.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "TitleText.hpp"
#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include "AuxiliarRenderFunctions.hpp"



TitleText::TitleText(Scene * scene):
GameObject(scene)
{
    
    this->mainFont = ResourceManager::Instance().getFont("playfair");
    
}


TitleText::~TitleText(){
}


void TitleText::update(){
//Nothing here yet but we might need to update some shader parameters or other stuff
}

void TitleText::draw(sf::RenderTarget *renderTarget){
    
    
    
    sf::Text text_it;
    sf::Text text_fights;

    text_it.setString("IT");
    text_fights.setString("FIGHTS");
    
    text_it.setFillColor(sf::Color::Black);
    text_fights.setFillColor(sf::Color::Black);
    
    text_it.setOutlineColor(sf::Color::Black);
    text_fights.setOutlineColor(sf::Color::Black);
    
    text_it.setOutlineThickness(3.0f);
    text_fights.setOutlineThickness(3.0f);
    
    text_it.setCharacterSize(400.0f);
    text_fights.setCharacterSize(300.0f);
    
    text_it.setFont(mainFont);
    text_fights.setFont(mainFont);
    
    PairI itPosition = getRealPixels(renderTarget, 0.15, -0.05);
    text_it.setPosition(itPosition.x, itPosition.y);
    PairI fightsPosition = getRealPixels(renderTarget, 0.03, 0.21);
    text_fights.setPosition(fightsPosition.x, fightsPosition.y);
    

    renderTarget->draw(text_it);
    renderTarget->draw(text_fights);
    
    
}
