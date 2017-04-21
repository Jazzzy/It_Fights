//
//  level_00_field.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 21/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Level_00_field_hpp
#define Level_00_field_hpp

#include <stdio.h>
#include <Scene.hpp>
#include "Level_00_GO_Field.hpp"


class Level_00_field : public Scene {
public:
    Level_00_field(MessageBus * messageBus);
    ~Level_00_field();
private:
    void localUpdateImplemented();
    
    Level_00_GO_Field level_00_GO_Field;
    sf::View view;

};

#endif /* Level_00_field_hpp */
