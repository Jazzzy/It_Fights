//
//  InputLine.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 31/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "InputLine.hpp"
#include <iostream>

sf::String InputLine::getString(){
    return (">  " + this->stringContent);
}

sf::String InputLine::getRealString(){
    return (this->stringContent);
}

void InputLine::removeLastCharacter(){
    if(this->stringContent.getSize()>0){
        this->stringContent.erase(this->stringContent.getSize()-1);
    }
}

void InputLine::erase(){
    this->stringContent.clear();
}

void InputLine::appendCharacter(char character){
    ConsoleLine::appendCharacter(character);
}

void InputLine::appendString(sf::String string){
    ConsoleLine::appendString(string);
}
