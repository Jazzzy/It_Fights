//
//  GroundNoiseShader.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 29/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "GroundNoiseShader.hpp"
#include "Game.hpp"
#include "Clock.hpp"

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
        return sf::RenderStates();
}

void GroundNoiseShader::drawWithShader(sf::RenderTarget* renderTarget, sf::Drawable * drawable){
    
//    this->sf_shader.setUniform("u_resolution", this->resolution);
//    this->sf_shader.setUniform("u_time", (this->time += Clock::Instance().getDeltaTime()) );
//    this->sf_shader.setUniform("u_blend", .1f );
//    this->sf_shader.setUniform("source", drawable);
//    
//    renderTarget->draw(*drawable,&(this->sf_shader));
    
    
}

void GroundNoiseShader::drawWithShader(sf::RenderTarget* renderTarget, sf::Drawable * drawable, sf::Texture source){
    
    this->sf_shader.setUniform("u_resolution", this->resolution);
    this->sf_shader.setUniform("u_time", (this->time += Clock::Instance().getDeltaTime()) );
    this->sf_shader.setUniform("u_blend", .8f );
    this->sf_shader.setUniform("source", source);
    
    renderTarget->draw(*drawable,&(this->sf_shader));
    
    
}

