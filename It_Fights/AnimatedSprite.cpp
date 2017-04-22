//
//  AnimatedSprite.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 22/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "AnimatedSprite.hpp"
#include "ResourcePath.hpp"
#include <fstream>

#include "Game.hpp"
extern Game game;


AnimatedSprite::AnimatedSprite(std::string dataFilename, std::string spriteSheetFilename, std::string animationsFilename){

    std::ifstream jsonFile(resourcePath() + dataFilename);
    
    this->timePerFrame = 80.f/1000.f;
    
    json jsonData;
    
    jsonFile >> jsonData;
    
    json frameArray = jsonData["frames"];
    
    int frameIndex = 1;
    for (json::iterator it = frameArray.begin() ; it != frameArray.end(); ++it, frameIndex++) {
        json frameData = *it;
        FrameData currentFrameData;
        currentFrameData.index=frameIndex;
        currentFrameData.x = frameData["frame"]["x"];
        currentFrameData.y = frameData["frame"]["y"];
        currentFrameData.width = frameData["frame"]["w"];
        currentFrameData.heigth = frameData["frame"]["h"];
        
        currentFrameData.pivot_x = frameData["pivot"]["x"];
        currentFrameData.pivot_y = frameData["pivot"]["y"];
        
        
        this->frameMap[currentFrameData.index]=currentFrameData;
    }
    
    
    if(!this->spriteSheet.loadFromFile(resourcePath()+spriteSheetFilename)){
        std::cerr << "ERROR: Could not load Main Character 00 spritesheet" << std::endl;
    }
    
    std::ifstream jsonAnimationFile(resourcePath() + animationsFilename);
    
    json animationJsonData;
    jsonAnimationFile >> animationJsonData;
    
    
    bool first = true;
    
    for (json::iterator it = animationJsonData.begin(); it != animationJsonData.end(); ++it) {
        
        if(first){
            this->currentAnimationName = it.key();
            loop = true;
            first = false;
        }
        
        AnimationData animData;
        animData.name = it.key();
        
        for(json::iterator fit = it.value().begin(); fit!= it.value().end(); ++fit ){
            animData.frames.push_back(*fit);
        }
        this->animationMap[it.key()]=animData;
        
    }
    
    this->currentAnimationData = this->animationMap[this->currentAnimationName];
    
    this->callbackAnimationEnd = [](){};
    
    this->timeInThisFrame = 0.f;
    
}

AnimatedSprite::~AnimatedSprite(){}

sf::Sprite AnimatedSprite::getSprite(unsigned int index){

    FrameData * fPtr = &(this->frameMap[index]);
    
    sf::Sprite sprite(this->spriteSheet,sf::IntRect(fPtr->x,fPtr->y,fPtr->width,fPtr->heigth));
    
    sprite.setOrigin(fPtr->pivot_x * fPtr->width, fPtr->pivot_y * fPtr->heigth);
    
    return sprite;
    
}

std::string AnimatedSprite::getCurrentAnimation(){
    return this->currentAnimationName;
}


void AnimatedSprite::startAnimation(std::string name, bool loop,std::function<void()> callback){

    if(currentAnimationName.compare(name)==0){
        return; //Trying to set the same animation
    }
    
    this->callbackAnimationEnd = callback;
    this->currentAnimationName = name;
    this->currentAnimationData = this->animationMap[this->currentAnimationName];
    this->currentAnimationData.currentFrame = this->currentAnimationData.frames.begin();
    
}

void AnimatedSprite::goToNextFrame(){
    this->currentAnimationData.currentFrame++;
    if(this->currentAnimationData.currentFrame == this->currentAnimationData.frames.end()){
        if(loop){
            this->currentAnimationData.currentFrame = this->currentAnimationData.frames.begin();
        }else{
            this->callbackAnimationEnd();
            this->currentAnimationData.currentFrame--;
        }
    }else{
        
    }
    }

void AnimatedSprite::update(){
    
    this->timeInThisFrame += game.getDeltaClock()->getDeltaTime();
    
    if(timeInThisFrame >= this->timePerFrame){
        this->goToNextFrame();
        this->timeInThisFrame = 0.f;
    }
    
}

void AnimatedSprite::draw(sf::RenderTarget *renderTarget){
    
    renderTarget->draw(getSprite(*(this->currentAnimationData.currentFrame)));

}


sf::Sprite AnimatedSprite::getCurrentSprite(){
    return getSprite(*(this->currentAnimationData.currentFrame));
}





