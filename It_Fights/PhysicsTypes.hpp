//
//  PhysicsTypes.h
//  It_Fights
//
//  Created by Rubén Osorio López on 9/6/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef PhysicsTypes_h
#define PhysicsTypes_h

#include <SFML/Graphics.hpp>

enum Direction_4 { UP,DOWN,RIGHT,LEFT };

enum Direction_8 { UP_8,UP_RIGHT_8,RIGHT_8,RIGHT_DOWN_8,DOWN_8,DOWN_LEFT_8,LEFT_8,LEFT_UP_8, NONE_8};


/*
 
    IMPORTANT:
 
    They Y axis increases in the DOWN direction.
 
 
 */

//@@TODO: Make functions for getting the Direction_8 from a director vector


Direction_4 getDirection_4FromVector(sf::Vector2f vector);

Direction_8 getDirection_8FromVector(sf::Vector2f vector);


sf::Vector2f getVectorFromDirection_4(Direction_4 direction_4);

bool isVectorHeaded_halfCircle(Direction_4 direction_4 , sf::Vector2f vector);

double getAngleInDegrees180(sf::Vector2f vector);

double getAngleInDegrees360(sf::Vector2f vector);




#endif /* PhysicsTypes_h */
