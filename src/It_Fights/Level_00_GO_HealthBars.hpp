//
//  Level_00_GO_HealthBars.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 16/5/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Level_00_GO_HealthBars_hpp
#define Level_00_GO_HealthBars_hpp

#include "GameObject.hpp"
#include "Level_00_GO_Characters.hpp"

class Level_00_GO_HealthBars : public GameObject {
 public:
  Level_00_GO_HealthBars(Scene* scene, Level_00_GO_Characters* characters,
                         sf::Clock* fightClock);
  ~Level_00_GO_HealthBars();
  void stopCounting();
  void update();
  void draw(sf::RenderTarget* renderTarget);
  void onStart() {}
  void onEnd() {}

 private:
  Level_00_GO_Characters* characters;

  sf::Clock* fightClock;
  sf::Font mainFont;

  float mainCharShowingHP;
  float enemyCharShowingHP;

  float mainCharTargetHP;
  float enemyCharTargetHP;

  float lerpSpeed;

  bool counting;
  int secondsShowing;
};

#endif /* Level_00_GO_HealthBars_hpp */
