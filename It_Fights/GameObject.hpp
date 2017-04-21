//
//  GameObject.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include "Drawable.hpp"

class GameObject : public Drawable {
public:
    virtual ~GameObject() {}
    virtual void update() = 0;
    virtual void draw(sf::RenderTarget *renderTarget) = 0;
};



#endif /* GameObject_hpp */
