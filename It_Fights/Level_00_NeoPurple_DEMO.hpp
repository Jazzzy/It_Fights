//
//  level_00_NeoPurple_DEMO.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 21/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Level_00_NeoPurple_DEMO_hpp
#define Level_00_NeoPurple_DEMO_hpp

#include <Scene.hpp>
#include "Level_00_GO_Characters.hpp"
#include "Level_00_GO_Ground.hpp"
#include "Level_00_GO_HealthBars.hpp"

#define LVL_00_RESOLUTION_X 400
#define LVL_00_RESOLUTION_Y 300
#define TIME_SCALE 400
#define TIME_LIMIT_IN_SECONDS 30
#define TIME_WINNER (3.f)

class Level_00_NeoPurple_DEMO : public Scene {
 public:
  Level_00_NeoPurple_DEMO(MessageBus* messageBus,
                          CharacterOptions characterOptions, bool shouldRender);
  virtual ~Level_00_NeoPurple_DEMO();

 private:
  void localUpdateImplemented();
  void screenShaders(sf::RenderTarget* renderTarget,
                     const sf::Texture* screenTexture);
  void draw(sf::RenderTarget* renderTarget);
  void update();

  Level_00_GO_Ground level_00_GO_Ground;
  Level_00_GO_Characters level_00_GO_Characters;
  Level_00_GO_HealthBars level_00_GO_HealthBars;

  sf::View view;
  bool changedRes;

  bool shouldRender;

  bool shouldUpdate;

  void win(Position player);

  void onNotify(Message message);

  sf::Clock fightClock;

  float timeWinnerRemaining;
  bool showingWinner;
  short lastWinnerNumber;
  sf::Font winnerFont;
  void startShowWinner(short winnerNumber);
  void updateShowWinner();
  void drawWinner(sf::RenderTarget* renderTarget);
};

#endif /* Level_00_NeoPurple_DEMO_hpp */
