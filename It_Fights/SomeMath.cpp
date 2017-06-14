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

unsigned int getRandomBetween(unsigned int min, unsigned int max){
    int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;
    
    /* Create equal size buckets all in a row, then fire randomly towards
     * the buckets until you land in one of them. All buckets are equally
     * likely. If you land off the end of the line of buckets, try again. */
    do
    {
        r = rand();
    } while (r >= limit);
    
    return min + (r / buckets);
}


