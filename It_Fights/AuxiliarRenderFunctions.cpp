//
//  AuxiliarRenderFunctions.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 31/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "AuxiliarRenderFunctions.hpp"

PairI getRealPixels(sf::RenderTarget *renderTarget, double x, double y) {
  PairI returnPair;
  sf::Vector2u renderSize = renderTarget->getSize();

  returnPair.x = (x * renderSize.x);
  returnPair.y = (y * renderSize.y);

  return returnPair;
}
