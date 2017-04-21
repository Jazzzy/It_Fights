//
//  Level_00_GO_Field.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 21/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Level_00_GO_Field_hpp
#define Level_00_GO_Field_hpp

#include <stdio.h>

#include "GameObject.hpp"

class Level_00_GO_Field : public GameObject {
public:
    Level_00_GO_Field();
    ~Level_00_GO_Field();
    void update();
    void draw(sf::RenderTarget *renderTarget);
private:
    
};

#endif /* Level_00_GO_Field_hpp */
