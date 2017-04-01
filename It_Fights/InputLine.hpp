//
//  InputLine.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 31/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef InputLine_hpp
#define InputLine_hpp

#include "ConsoleLine.hpp"


class InputLine : public ConsoleLine {
public:
    sf::String getString();
    sf::String getRealString();
    void removeLastCharacter();
    void erase();
};

#endif /* InputLine_hpp */
