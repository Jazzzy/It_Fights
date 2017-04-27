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
#include "BoxCollider.hpp"

class Level_00_GO_Ground : public GameObject {
public:
    Level_00_GO_Ground();
    ~Level_00_GO_Ground();
    void update();
    void draw(sf::RenderTarget *renderTarget);
private:
    sf::RenderTexture groundTexture;
    BoxCollider outsideCollider;
};

#endif /* Level_00_GO_Ground_hpp */
