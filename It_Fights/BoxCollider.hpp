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
                std::function<void(ColliderType)>onCollisionCallback,
                ColliderType colliderType);
    ~BoxCollider();
    void registerCollider();
    void unregisterCollider();
private:
    RectangleCollider collider;
    
    
};


#endif /* BoxCollider_hpp */
