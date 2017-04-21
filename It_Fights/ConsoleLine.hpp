//
//  ConsoleLine.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 31/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef ConsoleLine_hpp
#define ConsoleLine_hpp

#include "Drawable.hpp"
#include <SFML/Graphics.hpp>


class ConsoleLine  {
public:
    ConsoleLine(sf::String content);
    ConsoleLine();
    ~ConsoleLine();

    void appendCharacter(char character);
    void appendString(sf::String string);
    
    sf::String getString();
    unsigned int getLines();
    
protected:
    sf::String stringContent;
    unsigned int numberOfLines;

};

#endif /* ConsoleLine_hpp */
