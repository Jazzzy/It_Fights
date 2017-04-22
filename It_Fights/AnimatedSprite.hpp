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

class AnimatedSprite : public Drawable{
public:
    AnimatedSprite(std::string filename);
    ~AnimatedSprite();
    sf::Sprite getCurrentSprite();
    void update();
    void draw(sf::RenderTarget *renderTarget);
private:
    sf::Texture spriteSheet;
    
};

#endif /* AnimatedSprite_hpp */
