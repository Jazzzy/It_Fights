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
    PLAY_HUMAN_VS_HUMAN,
    PLAY_HUMAN_VS_AGENT,
    PLAY_AGENT_VS_AGENT,
    PLAY_AGENT_VS_AGENT_NO_RENDERING,
    CLOSE,
    LAST
};

enum Direction {
    MOVE_MENU_UP,
    MOVE_MENU_DOWN
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
    
    std::vector<std::pair<Options, sf::Text>> optionsVector;
    sf::Font mainFont;
    Options selectedOption;
    void changeSelection(short delta);
    std::string getStringFromOption(Options option);
    
    sf::Vector2f selectedOptionPosition;
    sf::Vector2f selectedOptionSize;
    
    sf::Vector2f shownOptionPosition;
    sf::Vector2f shownOptionSize;
    
};

#endif /* MenuOptions_hpp */
