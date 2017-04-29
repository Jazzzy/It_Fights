//
//  AnimatedSprite.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 22/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef AnimatedSprite_hpp
#define AnimatedSprite_hpp


#include "Drawable.hpp"
#include <unordered_map>


enum DataMode {
    Aseprite_Array_Json_Data_WPivot
};

typedef struct {
    
    unsigned int index;
    unsigned int x;
    unsigned int y;
    unsigned int width;
    unsigned int heigth;
    
    float pivot_x;
    float pivot_y;
    
    unsigned int durationMillis;
    
} FrameData;

typedef struct {
    
    std::string name;
    std::vector<unsigned int>frames;
    std::vector<unsigned int>::iterator currentFrame;
    
} AnimationData;




class AnimatedSprite : public Drawable{
public:
    AnimatedSprite(std::string dataFilename, std::string spriteSheetFilename,DataMode dataMode);
    ~AnimatedSprite();
    sf::Sprite getSprite(unsigned int index);
    sf::Sprite getCurrentSprite();
    void update();
    void draw(sf::RenderTarget *renderTarget);
    
    std::string getCurrentAnimation();
    void startAnimation(std::string name, bool loop, std::function<void()> callback);
    
private:
    sf::Texture spriteSheet;
    std::unordered_map<unsigned int, FrameData> frameMap;
    std::unordered_map<std::string,AnimationData> animationMap;
    
    std::string currentAnimationName;
    AnimationData currentAnimationData;
    bool loop;
    void goToNextFrame();
    std::function<void()> callbackAnimationEnd;
    
    float timePerFrame;
    float timeInThisFrame;
    
};

#endif /* AnimatedSprite_hpp */
