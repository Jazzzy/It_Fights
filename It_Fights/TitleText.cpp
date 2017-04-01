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

extern ResourceManager resourceManager;

#include "ResourcePath.hpp"


TitleText::TitleText(){
    
    this->mainFont = resourceManager.getFont("playfair");
    
}


TitleText::~TitleText(){
    std::cout << "DESTROYING GAME OBJECT" <<std::endl;
}


void TitleText::update(){
//Nothing here yet but we might need to update some shader parameters or other stuff
}

void TitleText::draw(sf::RenderTarget *renderTarget){
    
    sf::Text text_it;
    sf::Text text_fights;

    text_it.setString("IT");
    text_fights.setString("FIGHTS");
    
    text_it.setFillColor(sf::Color::White);
    text_fights.setFillColor(sf::Color::White);
    
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

    
    //@@TODO: Maybe some shader stuff here: https://github.com/SFML/SFML-Game-Development-Book/blob/master/09_Audio/Source/BloomEffect.cpp
    
    
    renderTarget->draw(text_it);
    renderTarget->draw(text_fights);
    

}
