//
//  Level_00_GO_Field.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 21/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Level_00_GO_Field.hpp"


Level_00_GO_Field::Level_00_GO_Field(){

}

Level_00_GO_Field::~Level_00_GO_Field(){
    
}

void Level_00_GO_Field::update(){

}

void Level_00_GO_Field::draw(sf::RenderTarget *renderTarget){

    
    //@@DEBUG @@TODO
    for(int x=-200;x<3200;x+=200)
    {
        for(int y=-200;y<2200;y+=200)
        {
            
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(200, 200));
            rectangle.setOutlineColor(sf::Color::Black);
            rectangle.setOutlineThickness(5);
            rectangle.setPosition(x, y);
            
            renderTarget->draw(rectangle);
        }
    }
    
    
}
