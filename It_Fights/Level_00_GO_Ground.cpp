//
//  Level_00_GO_Ground.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 21/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Level_00_GO_Ground.hpp"
#include "Level_00_NeoPurple_DEMO.hpp"
#include "DebugUtilities.hpp"

#define tileSide 16
#define tileMapWidth 13
#define tileMapHeight 11
#define outLineTHICC 1


Level_00_GO_Ground::Level_00_GO_Ground(Scene* scene) :
GameObject(scene),
groundTexture(),
noiseTexture(),
noiseShader(sf::Vector2f(LVL_00_RESOLUTION_X,LVL_00_RESOLUTION_Y)),
outsideCollider( sf::Vector2f((tileSide * tileMapWidth), (tileSide * tileMapHeight)) ,[]() -> sf::Vector2f{
    
    sf::Vector2f origin;
    origin.x = (LVL_00_RESOLUTION_X-(tileSide*tileMapWidth))/2.0f;
    origin.y = (LVL_00_RESOLUTION_Y-(tileSide*tileMapHeight))/2.0f;
    return origin;
    
},
                [](ColliderType colType,sf::Vector2f vector, float value){},
                ColliderType::INVERTED_BOX, CollisionLayer::NEUTRAL)
{
    
    
    noiseTexture.create(LVL_00_RESOLUTION_X,LVL_00_RESOLUTION_Y);
    noiseTexture.setSmooth(true);
    
    
    groundTexture.create(LVL_00_RESOLUTION_X,LVL_00_RESOLUTION_Y);
    groundTexture.setSmooth(false);
    
    groundTexture.clear(sf::Color::Transparent);
    
    float sidePadding_x = (LVL_00_RESOLUTION_X-(tileSide*tileMapWidth))/2;
    float sidePadding_y = (LVL_00_RESOLUTION_Y-(tileSide*tileMapHeight))/2;
    
    for(float x=sidePadding_x ; x < (sidePadding_x + ( tileSide * tileMapWidth)) ; x+=tileSide)
    {
        for(float y=sidePadding_y ; y < (sidePadding_y + ( tileSide * tileMapHeight)) ; y+=tileSide)
        {
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(tileSide-outLineTHICC, tileSide-outLineTHICC));
            rectangle.setOutlineColor(sf::Color(150,150,150));
            rectangle.setOutlineThickness(outLineTHICC);
            rectangle.setPosition(x, y);
            groundTexture.draw(rectangle);
        }
    }
    
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f((tileSide*tileMapWidth)-outLineTHICC, (tileSide*tileMapHeight)-outLineTHICC));
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(outLineTHICC*2);
    rectangle.setPosition(sidePadding_x, sidePadding_y);
    rectangle.setFillColor(sf::Color::Transparent);
    groundTexture.draw(rectangle);
    
    groundTexture.display();
    
    
    
    noiseSprite.setTexture(this->noiseTexture.getTexture());
    noiseSprite.setTextureRect(sf::IntRect(0, 0, LVL_00_RESOLUTION_X, LVL_00_RESOLUTION_Y));
}

Level_00_GO_Ground::~Level_00_GO_Ground(){
    
}

void Level_00_GO_Ground::update(){
    
    
    
}

void Level_00_GO_Ground::draw(sf::RenderTarget *renderTarget){
    
    this->drawNoise(renderTarget);
    
    //renderTarget->draw(sf::Sprite(this->groundTexture.getTexture()));
    
}

void Level_00_GO_Ground::onStart(){
    if(!this->outsideCollider.isRegistered()){
        this->outsideCollider.registerCollider();
    }
}
void Level_00_GO_Ground::onEnd(){
    if(this->outsideCollider.isRegistered()){
        this->outsideCollider.unregisterCollider();
    }
}

void Level_00_GO_Ground::drawNoise(sf::RenderTarget *renderTarget){
    
    this->noiseTexture.clear(sf::Color::Black);
    
    
    
    //this->noiseShader.drawWithShader(&this->noiseTexture, &noiseSprite);
    sf::Sprite auxSprite(this->groundTexture.getTexture());
    this->noiseShader.drawWithShader(&this->noiseTexture, &auxSprite, this->groundTexture.getTexture());
    
    
    
    
    this->noiseTexture.display();
    
    
    renderTarget->draw(sf::Sprite(this->noiseTexture.getTexture()));
    
}























