//
//  TitleText.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef TitleText_hpp
#define TitleText_hpp

#include "GameObject.hpp"

class TitleText : public GameObject {
 public:
  TitleText(Scene *scene);
  ~TitleText();
  void update();
  void draw(sf::RenderTarget *renderTarget);
  void onStart() {}
  void onEnd() {}

 private:
  sf::Font mainFont;
};

#endif /* TitleText_hpp */
