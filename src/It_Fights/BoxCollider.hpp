//
//  BoxCollider.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 26/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef BoxCollider_hpp
#define BoxCollider_hpp

#include <functional>
#include "Collisions.hpp"

class BoxCollider {
 public:
  BoxCollider(sf::Vector2f size, std::function<sf::Vector2f()> getOriginFunc,
              std::function<void(ColliderType, sf::Vector2f, float)>
                  onCollisionCallback,
              ColliderType colliderType, CollisionLayer layer);
  ~BoxCollider();

  bool isRegistered();
  void registerCollider();
  void unregisterCollider();

  bool isActive();
  void setActive(bool active);

 private:
  RectangleCollider collider;
  bool registered;
  bool active;
};

#endif /* BoxCollider_hpp */
