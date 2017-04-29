//
//  GroundNoiseShader.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 29/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "GroundNoiseShader.hpp"
#include "Game.hpp"

extern Game game;


#include "ResourcePath.hpp"

GroundNoiseShader::GroundNoiseShader(sf::Vector2f resolution){
    
    this->resolution = resolution;
    
    this->time = 0.f;
    
    if(!this->sf_shader.loadFromFile(resourcePath()+"Fullpass.vert",resourcePath()+"lavaNoise.frag")){
        exit(1);
    }
    
}

GroundNoiseShader::~GroundNoiseShader(){
    
}

sf::RenderStates GroundNoiseShader::getRenderStates(){
    
    //TODO
    return sf::RenderStates();
}

void GroundNoiseShader::drawWithShader(sf::RenderTarget* renderTarget, sf::Drawable * drawable){
    
    this->sf_shader.setUniform("u_resolution", this->resolution);
    this->sf_shader.setUniform("u_time", (this->time += game.getDeltaClock()->getDeltaTime()) );
    
    renderTarget->draw(*drawable,&(this->sf_shader));
    
    
}

