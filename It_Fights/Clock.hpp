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
#include <deque>

class Clock {
public:
    Clock();
    ~Clock();
    
    void setFrameSeparator();
    float getDeltaTime();
    float getMeanDeltaTime();
    unsigned int getMeanFPS();
    
private :
    sf::Clock deltaClock;
    sf::Time deltaTime;
    std::deque<sf::Time> timesQueue;
    float meanDeltaTime;
    
    void updateQueue(sf::Time time);
    
};



#endif /* Clock_hpp */
