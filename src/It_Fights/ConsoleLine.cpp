//
//  ConsoleLine.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 31/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "ConsoleLine.hpp"
#include <algorithm>

#include <iostream>

ConsoleLine::ConsoleLine(sf::String content) {
  this->stringContent = content;
  std::string ansiString = content.toAnsiString();

  this->numberOfLines =
      1 + (unsigned int)std::count(ansiString.begin(), ansiString.end(), '\n');
}

ConsoleLine::ConsoleLine() {}

ConsoleLine::~ConsoleLine() {}

sf::String ConsoleLine::getString() { return this->stringContent; }

void ConsoleLine::appendCharacter(char character) {
  this->stringContent += character;
}

void ConsoleLine::appendString(sf::String string) {
  this->stringContent += string;
}

unsigned int ConsoleLine::getLines() { return this->numberOfLines; }
