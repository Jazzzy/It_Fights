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

enum Direction {
    MOVE_UP,
    MOVE_DOWN
};


class MenuOptions : public GameObject {
public:
    MenuOptions(Scene * scene);
    ~MenuOptions();
    void update();
    void draw(sf::RenderTarget *renderTarget);
    void onStart(){}
    void onEnd(){}
    void moveSelection(Direction direction);
    void executeSelection();
private:
    sf::Font mainFont;
    Options selectedOption;
    void changeSelection(short delta);
    
};

#endif /* MenuOptions_hpp */
