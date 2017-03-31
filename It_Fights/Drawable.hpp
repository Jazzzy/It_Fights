//
//  Drawable.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 31/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Drawable_hpp
#define Drawable_hpp


#include <SFML/Graphics.hpp>

class Drawable{
    virtual void draw(sf::RenderTarget *renderTarget) = 0;
};



#endif /* Drawable_hpp */
