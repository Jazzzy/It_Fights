//
//  level_00_NeoPurple_DEMO.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 21/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Level_00_NeoPurple_DEMO_hpp
#define Level_00_NeoPurple_DEMO_hpp

#include <stdio.h>
#include <Scene.hpp>
#include "Level_00_GO_Ground.hpp"
#include "Level_00_GO_Characters.hpp"
#include "Level_00_GO_HealthBars.hpp"


#define LVL_00_RESOLUTION_X 400
#define LVL_00_RESOLUTION_Y 300

class Level_00_NeoPurple_DEMO : public Scene {
public:
    Level_00_NeoPurple_DEMO(MessageBus * messageBus);
    ~Level_00_NeoPurple_DEMO();
private:
    void localUpdateImplemented();
    void screenShaders(sf::RenderTarget * renderTarget,const sf::Texture * screenTexture);
    
    Level_00_GO_Ground level_00_GO_Ground;
    Level_00_GO_Characters level_00_GO_Characters;
    Level_00_GO_HealthBars level_00_GO_HealthBars;
    
    sf::View view;
    bool changedRes;
    
};

#endif /* Level_00_NeoPurple_DEMO_hpp */
