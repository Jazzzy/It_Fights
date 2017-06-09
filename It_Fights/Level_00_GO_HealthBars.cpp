//
//  Level_00_GO_HealthBars.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 16/5/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Level_00_GO_HealthBars.hpp"
#include "SomeMath.hpp"
#include "Clock.hpp"
#include "DebugUtilities.hpp"


Level_00_GO_HealthBars::Level_00_GO_HealthBars(Scene* scene, Level_00_GO_Characters * characters):
GameObject(scene){
    
    this->characters = characters;
    
    this->mainCharShowingHP = 0.f;
    this->enemyCharShowingHP = 0.f;
    
    this->mainCharTargetHP = .5f;
    this->enemyCharTargetHP = .5f;
    
    this->lerpSpeed = .95f;
    

}


Level_00_GO_HealthBars::~Level_00_GO_HealthBars(){


}


void Level_00_GO_HealthBars::update(){
    
    this->mainCharTargetHP = this->characters->getCharacter_1()->getHealthNormalized();
    this->enemyCharTargetHP = this->characters->getCharacter_2()->getHealthNormalized();
        
    this->mainCharShowingHP = lerp(this->mainCharShowingHP, this->mainCharTargetHP, this->lerpSpeed);
    this->enemyCharShowingHP = lerp(this->enemyCharShowingHP, this->enemyCharTargetHP, this->lerpSpeed);
    
}

#define PADDING (10)
#define BAR_WIDTH (15)

void Level_00_GO_HealthBars::draw(sf::RenderTarget * renderTarget){
    
    sf::Vector2u canvasSize = renderTarget->getSize();
    
    sf::RectangleShape mainCharBar;
    
    mainCharBar.setFillColor(sf::Color::Green);
    mainCharBar.setPosition(PADDING, PADDING);
    
    mainCharBar.setSize(sf::Vector2f( (this->mainCharShowingHP)  * ((canvasSize.x/2.) - PADDING*2) ,BAR_WIDTH ));
    
    
    sf::RectangleShape enemyCharBar;
    
    enemyCharBar.setFillColor(sf::Color::Red);
    enemyCharBar.setPosition(canvasSize.x - PADDING, PADDING);
    enemyCharBar.setPosition(canvasSize.x - PADDING, PADDING + (BAR_WIDTH));
    enemyCharBar.setRotation(180.f);
    enemyCharBar.setSize(sf::Vector2f( (this->enemyCharShowingHP)  * ((canvasSize.x/2.) - PADDING*2) ,BAR_WIDTH ));
    
    
    
    renderTarget->draw(mainCharBar);
    renderTarget->draw(enemyCharBar);

    

}
