//
//  BloomShader.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "BloomShader.hpp"
#include "ResourcePath.hpp"

BloomShader::BloomShader(){

        if(!this->sf_shader.loadFromFile(resourcePath()+"Fullpass.vert",resourcePath()+"Bloom.frag")){
            exit(1);
        }
    
}

BloomShader::~BloomShader(){
    
}

sf::RenderStates BloomShader::getRenderStates(){

    //TODO
    return sf::RenderStates();
}

void BloomShader::drawWithShader(sf::RenderTarget* renderTarget, sf::Drawable * drawable){
    
    this->sf_shader.setUniform("texture", sf::Shader::CurrentTexture);
    
    this->sf_shader.setUniform("pixelWidth", (float) 0.00001);
    this->sf_shader.setUniform("pixelHeight", (float) 0.00001);

    
    renderTarget->draw(*drawable,&(this->sf_shader));

    
}

