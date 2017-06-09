//
//  PhysicsTypes.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 9/6/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "PhysicsTypes.hpp"
#include <cmath>
#include "DebugUtilities.hpp"
#include "SomeMath.hpp"

double getAngleInDegrees180(sf::Vector2f vector){
    vector = getNormalizedVector(vector);
    return (std::atan2(vector.y, vector.x) * 180.0) / M_PI;
}

double getAngleInDegrees360(sf::Vector2f vector){
    
    double angle180 = getAngleInDegrees180(vector);
    
    if(angle180 < 0.0f){
        return angle180 + 360.f;
    }
    return angle180;
    
}

Direction_4 getDirection_4FromVector(sf::Vector2f vector){

    vector.y = -vector.y;
    
    double angleInDegrees = getAngleInDegrees180(vector);
    
    if(angleInDegrees > 0 ){
    
        if(angleInDegrees < 45.f){
            return Direction_4::RIGHT;
        }else if(angleInDegrees >= 45.f && angleInDegrees < 135.f){
            return Direction_4::UP;
        }else if(angleInDegrees >= 135.f && angleInDegrees <= 180.f){
            return Direction_4::LEFT;
        }
    
    }else if(angleInDegrees < 0){
    
        if(angleInDegrees > -45.f){
            return Direction_4::RIGHT;
        }else if(angleInDegrees <= -45.f && angleInDegrees > -135.f){
            return Direction_4::DOWN;
        }else if(angleInDegrees <= 135.f && angleInDegrees >= -180.f){
            return Direction_4::LEFT;
        }
        
    }

    return Direction_4::RIGHT;
    
}

Direction_8 getDirection_8FromVector(sf::Vector2f vector){

    vector.y = -vector.y;
    
    double angle = getAngleInDegrees360(vector);
    
    if(angle <= 22.5f ){
        return RIGHT_8;
    }else if(angle <= 67.5){
        return UP_RIGHT_8;
    }else if(angle <= 112.5){
        return UP_8;
    }else if(angle <= 157.5){
        return LEFT_UP_8;
    }else if(angle <= 202.5){
        return LEFT_8;
    }else if(angle <= 247.5){
        return DOWN_LEFT_8;
    }else if(angle <= 292.5){
        return DOWN_8;
    }else if(angle <= 337.5){
        return RIGHT_DOWN_8;
    }else{
        return RIGHT_8;
    }

}


sf::Vector2f getVectorFromDirection_4(Direction_4 direction_4){
    
    switch (direction_4){
        case UP:
            return sf::Vector2f(0.f,-1.f);
            break;
        case DOWN:
            return sf::Vector2f(0.f,1.f);
            break;
        case LEFT:
            return sf::Vector2f(-1.f,0.f);
            break;
        case RIGHT:
            return sf::Vector2f(1.f,0.f);
            break;
    }
}

bool isVectorHeaded_halfCircle(Direction_4 direction_4 , sf::Vector2f vector){
    sf::Vector2f directionVector = getVectorFromDirection_4(direction_4);
    
    double vectorAngle = getAngleInDegrees360(getNormalizedVector(vector));
    double headingAngle = getAngleInDegrees360(directionVector);
    
    double angleDifference = fabs(vectorAngle-headingAngle);
        
    return (angleDifference <= 90.0f);

}

