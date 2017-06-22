//
//  GroundNoiseShader.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 29/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef GroundNoiseShader_hpp
#define GroundNoiseShader_hpp

#include "Shader.hpp"

class GroundNoiseShader : public Shader {
 public:
  GroundNoiseShader(sf::Vector2f resolution);
  ~GroundNoiseShader();
  sf::RenderStates getRenderStates();
  void drawWithShader(sf::RenderTarget* renderTarget, sf::Drawable* drawable);
  void drawWithShader(sf::RenderTarget* renderTarget, sf::Drawable* drawable,
                      sf::Texture source);

 private:
  sf::Shader sf_shader;
  sf::Vector2f resolution;
  float time;
};

#endif /* GroundNoiseShader_hpp */
