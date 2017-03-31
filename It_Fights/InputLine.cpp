//
//  InputLine.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 31/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "InputLine.hpp"


sf::String InputLine::getString(){
    return (">  " + this->stringContent);
}
