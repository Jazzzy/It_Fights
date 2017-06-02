//
//  MenuScene.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef MenuScene_hpp
#define MenuScene_hpp

#include <Scene.hpp>
#include "TitleText.hpp"
#include "MenuOptions.hpp"


class MenuScene : public Scene {
public:
    MenuScene(MessageBus * messageBus);
    ~MenuScene();
private:
    TitleText titleText;
    MenuOptions menuOptions;
    
    void localUpdateImplemented();
    bool changedRes;
    void onNotify (Message message);


};

#endif /* MenuScene_hpp */
