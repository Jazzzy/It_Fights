//
//  Level_00_GO_Ground.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 21/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Level_00_GO_Ground_hpp
#define Level_00_GO_Ground_hpp

#include <stdio.h>

#include "GameObject.hpp"
#include "BloomShader.hpp"
#include "GroundNoiseShader.hpp"
#include "BoxCollider.hpp"

class Level_00_GO_Ground : public GameObject {
public:
    Level_00_GO_Ground(Scene* scene);
    ~Level_00_GO_Ground();
    void update();
    void draw(sf::RenderTarget *renderTarget);
    void onStart();
    void onEnd();
private:
    GroundNoiseShader noiseShader;
    sf::RenderTexture noiseTexture;
    sf::Sprite noiseSprite;
    sf::RenderTexture groundTexture;
    BoxCollider outsideCollider;
    void drawNoise(sf::RenderTarget *renderTarget);
};

#endif /* Level_00_GO_Ground_hpp */
