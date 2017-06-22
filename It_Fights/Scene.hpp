//
//  Scene.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <BusNode.hpp>
#include <Drawable.hpp>
#include <GameObject.hpp>
#include <vector>

class GameObject;

class Scene : public Drawable, public BusNode {
 public:
  Scene(MessageBus *messageBus);
  virtual ~Scene() = 0;
  void draw(sf::RenderTarget *renderTarget);
  void applyFullScreenShaders(sf::RenderTarget *renderTarget,
                              const sf::Texture *screenTexture);
  void update();
  void addGameObject(GameObject *gameObject);
  void onStart();
  void onEnd();

 private:
  std::vector<GameObject *> listOfGameObjects;

 protected:
  sf::View *viewptr;
  std::function<void()> localUpdateFunction;
  std::function<void(sf::RenderTarget *renderTarget,
                     const sf::Texture *texture)>
      fullScreenShadersFunc;
};

#endif /* Scene_hpp */
