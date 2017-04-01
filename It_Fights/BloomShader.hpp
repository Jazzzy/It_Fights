//
//  BloomShader.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef BloomShader_hpp
#define BloomShader_hpp

#include "Shader.cpp"

class BloomShader : public Shader {
public:
    BloomShader();
    ~BloomShader();
    sf::RenderStates getRenderStates();
private:
    sf::RenderTexture mBrightnessTexture;
    

};

#endif /* BloomShader_hpp */
