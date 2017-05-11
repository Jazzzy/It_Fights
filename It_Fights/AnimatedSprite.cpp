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
#include "json.hpp"
#include "DebugUtilities.hpp"
using json = nlohmann::json;

#include "Clock.hpp"
#include "Game.hpp"
extern Game game;


AnimatedSprite::AnimatedSprite(std::string dataFilename, std::string spriteSheetFilename,DataMode dataMode){
    
    if(dataMode == DataMode::Aseprite_Array_Json_Data_WPivot){
        
        std::ifstream jsonFile(resourcePath() + dataFilename);
        
        this->timePerFrame = 80.f/1000.f;
        
        json jsonData;
        
        jsonFile >> jsonData;
        
        json frameArray = jsonData["frames"];
        
        int frameIndex = 0;
        for (json::iterator it = frameArray.begin() ; it != frameArray.end(); ++it, frameIndex++) {
            json frameData = *it;
            FrameData currentFrameData;
            currentFrameData.index=frameIndex;
            currentFrameData.x = frameData["frame"]["x"];
            currentFrameData.y = frameData["frame"]["y"];
            currentFrameData.width = frameData["frame"]["w"];
            currentFrameData.heigth = frameData["frame"]["h"];
            
            
            if(jsonData["meta"].find("pivot") == jsonData["meta"].end()){
                currentFrameData.pivot_x = 0.f;
                currentFrameData.pivot_y = 0.f;
            }else{
                currentFrameData.pivot_x = jsonData["meta"]["pivot"]["x"];
                currentFrameData.pivot_y = jsonData["meta"]["pivot"]["y"];
            }
            
            currentFrameData.durationMillis = frameData["duration"];
            
            this->frameMap[currentFrameData.index]=currentFrameData;
        }
        
        
        if(!this->spriteSheet.loadFromFile(resourcePath()+spriteSheetFilename)){
            std::cerr << "ERROR: Could not load Main Character 00 spritesheet" << std::endl;
        }
        
        
        json animationJsonData = jsonData["meta"]["frameTags"];
        
        
        bool first = true;
        
        for (json::iterator it = animationJsonData.begin(); it != animationJsonData.end(); ++it) {
            
            
            json currAnimData = *it;
            
            if(first){
                this->currentAnimationName = currAnimData["name"];
                loop = true;
                first = false;
            }
            
            AnimationData animData;
            animData.name = currAnimData["name"];
            
            
            for(unsigned int i = currAnimData["from"]; i <= (unsigned int)currAnimData["to"] ;i++){
                animData.frames.push_back(i);
            }
            this->animationMap[animData.name]=animData;
            
        }
        
        this->currentAnimationData = this->animationMap[this->currentAnimationName];
        
        this->callbackAnimationEnd = [](){};
        
        this->timeInThisFrame = 0.f;
    }
    
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
 
    
    if(currentAnimationName.compare(name)==0 && loop ){
        return; //Trying to set the same animation
    }
    
    this->loop = loop;
    this->callbackAnimationEnd = callback;
    this->currentAnimationName = name;
    this->currentAnimationData = this->animationMap[this->currentAnimationName];
    this->currentAnimationData.currentFrame = this->currentAnimationData.frames.begin();
    FrameData * fPtr = &(this->frameMap[*(this->currentAnimationData.currentFrame)]);
    this->timePerFrame = ((float)fPtr->durationMillis)/1000.f;
    
    
    
    
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
    
    FrameData * fPtr = &(this->frameMap[*(this->currentAnimationData.currentFrame)]);
    
    this->timePerFrame = ((float)fPtr->durationMillis)/1000.f;
    
}

void AnimatedSprite::update(){
    
    this->timeInThisFrame += Clock::Instance().getDeltaTime();
    
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





