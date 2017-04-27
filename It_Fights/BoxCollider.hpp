//
//  BoxCollider.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 26/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef BoxCollider_hpp
#define BoxCollider_hpp

#include "Collisions.hpp"
#include <functional>


class BoxCollider {
public:
    BoxCollider(float width,
                float heigth,
                std::function<std::pair<float,float>()>getOriginFunc ,
                std::function<void(ColliderType,std::pair<float, float>)>onCollisionCallback,
                ColliderType colliderType);
    ~BoxCollider();
    

    bool isRegistered();
    void registerCollider();
    void unregisterCollider();
    
    
    bool isActive();
    void setActive();
    void setUnactive();
    
private:
    RectangleCollider collider;
    bool registered;
    bool active;
    
    
};


#endif /* BoxCollider_hpp */
