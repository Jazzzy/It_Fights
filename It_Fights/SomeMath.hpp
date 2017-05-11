//
//  SomeMath.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 22/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef SomeMath_hpp
#define SomeMath_hpp

#include <SFML/Window.hpp>


sf::Vector2f getNormalizedVector(sf::Vector2f inVector);

float getVectorLength(sf::Vector2f inVector);

template <typename T>
inline T lerp(T v1, T v0, T t) {
    return fma(t, v1, fma(-t, v0, v0));
}

#endif /* SomeMath_hpp */
