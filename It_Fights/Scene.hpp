//
//  Scene.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <Drawable.hpp>
#include <BusNode.hpp>
#include <GameObject.hpp>
#include <vector>

class Scene : public Drawable, public BusNode {
public:
    Scene(MessageBus * messageBus);
    ~Scene();
    void draw(sf::RenderTarget *renderTarget);
    void update();
    void addGameObject(GameObject *gameObject);
    
private:
    std::vector<GameObject*> listOfGameObjects;

};


#endif /* Scene_hpp */
