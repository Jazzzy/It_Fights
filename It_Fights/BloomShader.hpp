//
//  BloomShader.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef BloomShader_hpp
#define BloomShader_hpp

#include "Shader.hpp"

class BloomShader : public Shader {
public:
    BloomShader();
    ~BloomShader();
    sf::RenderStates getRenderStates();
    void drawWithShader(sf::RenderTarget* renderTarget, sf::Drawable* drawable);

private:
    sf::Shader sf_shader;
    sf::RenderTexture mBrightnessTexture;
    

};

#endif /* BloomShader_hpp */
