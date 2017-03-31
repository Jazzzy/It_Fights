//
//  Event.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 28/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Event_hpp
#define Event_hpp

//Original event class defined here: https://github.com/SFML/SFML/blob/master/include/SFML/Window/Event.hpp

#include <SFML/Window.hpp>

class Event {
    
public:
    Event(sf::Event event);
    ~Event();
    
    sf::Event getEvent();
    
private:
    sf::Event internalEvent;
    
};

#endif /* Event_hpp */
