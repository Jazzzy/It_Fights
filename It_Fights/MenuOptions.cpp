//
//  MenuOptions.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/6/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "MenuOptions.hpp"
#include "ResourceManager.hpp"
#include "DebugUtilities.hpp"
#include "AuxiliarRenderFunctions.hpp"



MenuOptions::MenuOptions(Scene * scene) : GameObject(scene){

    this->mainFont = ResourceManager::Instance().getFont("playfair");
    this->selectedOption = PLAY;

}

MenuOptions::~MenuOptions(){

}

void MenuOptions::moveSelection(Direction direction){
    
    switch (direction){
        case Direction::MOVE_UP:
            this->changeSelection(-1);
            break;
        case Direction::MOVE_DOWN:
            this->changeSelection(+1);
            break;
            
    }
    
}

void MenuOptions::changeSelection(short delta){

    short maxOptionNumber = Options::LAST;
    
    short newSelectedOption = (this->selectedOption + delta) % maxOptionNumber;
    
    if(newSelectedOption < 0) newSelectedOption = maxOptionNumber-1;
    
    this->selectedOption = (Options) newSelectedOption;
    
}

void MenuOptions::executeSelection(){
    
    switch(this->selectedOption){
        case PLAY:
        {
            Message msgMainGame("MSG_GO_TO_MAINGAME");
            this->scene->send(msgMainGame);
        }
            break;
            
        case CLOSE:
        {
            Message msgExitGame("MSG_CLOSE_WINDOW");
            this->scene->send(msgExitGame);
        }
            break;
            
        case LAST:
            break;
            
    }
}

void MenuOptions::update(){


}


void MenuOptions::draw(sf::RenderTarget *renderTarget){
    
    sf::Text text_play;
    sf::Text text_close;
    
    text_play.setString("PLAY");
    text_close.setString("CLOSE");
    
    text_play.setFillColor(sf::Color::White);
    text_close.setFillColor(sf::Color::White);
    
    text_play.setOutlineColor(sf::Color::Black);
    text_close.setOutlineColor(sf::Color::Black);
    
    
    switch(this->selectedOption){
        case PLAY:
            text_play.setOutlineThickness(4.0f);
            text_close.setOutlineThickness(1.0f);
            break;
            
        case CLOSE:
            text_play.setOutlineThickness(1.0f);
            text_close.setOutlineThickness(4.0f);
            break;
            
        default:
            text_play.setOutlineThickness(1.0f);
            text_close.setOutlineThickness(1.0f);
            break;
            
    }
    
    text_play.setCharacterSize(100.0f);
    text_close.setCharacterSize(100.0f);
    
    text_play.setFont(mainFont);
    text_close.setFont(mainFont);
    
    PairI itPosition = getRealPixels(renderTarget, 0.43, 0.65);
    text_play.setPosition(itPosition.x, itPosition.y);
    PairI fightsPosition = getRealPixels(renderTarget, 0.413, 0.75);
    text_close.setPosition(fightsPosition.x, fightsPosition.y);
    
    
    renderTarget->draw(text_play);
    renderTarget->draw(text_close);
    


}
