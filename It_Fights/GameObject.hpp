//
//  GameObject.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include "Scene.hpp"
#include "Drawable.hpp"

class Scene;

class GameObject : public Drawable {
public:
    GameObject(Scene * scene);
    virtual ~GameObject() {}
    virtual void update() = 0;
    virtual void draw(sf::RenderTarget *renderTarget) = 0;
    virtual void onStart() = 0;
    virtual void onEnd() = 0;
protected:
    Scene* scene;
};



#endif /* GameObject_hpp */
