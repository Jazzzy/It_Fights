//
//  MenuOptions.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/6/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef MenuOptions_hpp
#define MenuOptions_hpp

#include "GameObject.hpp"

enum Options {
    PLAY,
    CLOSE,
    LAST
};


class MenuOptions : public GameObject {
public:
    MenuOptions(Scene * scene);
    ~MenuOptions();
    void update();
    void draw(sf::RenderTarget *renderTarget);
    void onStart(){}
    void onEnd(){}
private:
    sf::Font mainFont;
    
};

#endif /* MenuOptions_hpp */
