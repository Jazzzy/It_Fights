//
//  SomeMath.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 22/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "SomeMath.hpp"
#include <cmath>


float getVectorLength(sf::Vector2f inVector){
    return sqrt((inVector.x *inVector.x)+ (inVector.y *inVector.y));
}



sf::Vector2f getNormalizedVector(sf::Vector2f vector){
    float length = getVectorLength(vector);
    if(length != 0){
        vector.x = vector.x/length;
        vector.y = vector.y/length;
    }
    return vector;
}


