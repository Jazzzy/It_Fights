//
//  Clock.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 28/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Clock_hpp
#define Clock_hpp

#include <SFML/Audio.hpp>

class Clock {
public:
    Clock();
    ~Clock();
    
    void setFrameSeparator();
    float getDeltaTime();
    
    private :
    sf::Clock deltaClock;
};



#endif /* Clock_hpp */
