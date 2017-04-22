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
#include "json.hpp"
#include <unordered_map>


using json = nlohmann::json;

typedef struct {
    
    unsigned int index;
    unsigned int x;
    unsigned int y;
    unsigned int width;
    unsigned int heigth;
    
    float pivot_x;
    float pivot_y;
    
} FrameData;

typedef struct {

    std::string name;
    std::vector<unsigned int>frames;
    std::vector<unsigned int>::iterator currentFrame;
    
} AnimationData;



using json = nlohmann::json;

class AnimatedSprite : public Drawable{
public:
    AnimatedSprite(std::string dataFilename, std::string spriteSheetFilename, std::string animationsFilename);
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
