//
//  Shader.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <SFML/Graphics.hpp>

class Shader {
public:
    virtual ~Shader(){}
    virtual sf::RenderStates getRenderStates() = 0;
    virtual sf::Shader & getShader() = 0;
};

#endif /* Shader_hpp */
