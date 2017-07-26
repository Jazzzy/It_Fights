//
//  BoxCollider.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 26/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "BoxCollider.hpp"
#include "Game.hpp"
extern Game* game;

BoxCollider::BoxCollider(
    sf::Vector2f size, std::function<sf::Vector2f()> getOriginFunc,
    std::function<void(ColliderType, sf::Vector2f, float)> onCollisionCallback,
    ColliderType colliderType, CollisionLayer layer) {
  ColliderFuncs funcs{.getOriginFunc = getOriginFunc,
                      .onCollisionCallback = onCollisionCallback};

  this->collider = RectangleCollider{.active = false,
                                     .id = 0,
                                     .size = size,
                                     .funcs = funcs,
                                     .colType = colliderType,
                                     .updated = false,
                                     .layer = layer};

  this->registered = false;

  return;
}

BoxCollider::~BoxCollider() {
  if (this->isActive()) {
    this->setActive(false);
  }

  if (this->isRegistered()) {
    this->unregisterCollider();
  }
}

void BoxCollider::setActive(bool active) { this->collider.active = active; }

bool BoxCollider::isRegistered() { return this->registered; }

bool BoxCollider::isActive() { return this->collider.active; }

void BoxCollider::registerCollider() {
  game->getCollisionSystem()->registerRectangleCollider(&this->collider);
  this->registered = true;
}

void BoxCollider::unregisterCollider() {
  game->getCollisionSystem()->unregisterRectangleCollider(this->collider.id);
  this->registered = false;
}
