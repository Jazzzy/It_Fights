//
//  ResourceManager.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "ResourceManager.hpp"
#include <iostream>
#include "ResourcePath.hpp"

ResourceManager* ResourceManager::MInstance = 0;

ResourceManager& ResourceManager::Instance() {
  if (MInstance == 0) MInstance = new ResourceManager();

  return *MInstance;
}

ResourceManager::ResourceManager() {
  this->loadFonts();

  atexit(&CleanUp);
}

void ResourceManager::CleanUp() {
  delete MInstance;
  MInstance = 0;
}

void ResourceManager::loadFonts() {
  sf::Font sansation;
  if (!sansation.loadFromFile(resourcePath() + "sansation.ttf")) {
    std::cerr << "ERROR: Could not load console font" << std::endl;
  }
  this->fontsMap.insert(
      std::pair<std::string, sf::Font>("sansation", sansation));

  sf::Font carnevalee;
  if (!carnevalee.loadFromFile(resourcePath() + "carnevalee.ttf")) {
    std::cerr << "ERROR: Could not load console font" << std::endl;
  }
  this->fontsMap.insert(
      std::pair<std::string, sf::Font>("carnevalee", carnevalee));

  sf::Font playfair;
  if (!playfair.loadFromFile(resourcePath() + "playfair.ttf")) {
    std::cerr << "ERROR: Could not load console font" << std::endl;
  }
  this->fontsMap.insert(std::pair<std::string, sf::Font>("playfair", playfair));

  sf::Font benguiat;
  if (!benguiat.loadFromFile(resourcePath() + "benguiat.ttf")) {
    std::cerr << "ERROR: Could not load console font" << std::endl;
  }
  this->fontsMap.insert(std::pair<std::string, sf::Font>("benguiat", benguiat));

  sf::Font rodin_l;
  if (!rodin_l.loadFromFile(resourcePath() + "rodin_l.otf")) {
    std::cerr << "ERROR: Could not load console font" << std::endl;
  }
  this->fontsMap.insert(std::pair<std::string, sf::Font>("rodin_l", rodin_l));

  sf::Font rodin_m;
  if (!rodin_m.loadFromFile(resourcePath() + "rodin_m.otf")) {
    std::cerr << "ERROR: Could not load console font" << std::endl;
  }
  this->fontsMap.insert(std::pair<std::string, sf::Font>("rodin_m", rodin_m));

  sf::Font rodin_b;
  if (!rodin_b.loadFromFile(resourcePath() + "rodin_b.otf")) {
    std::cerr << "ERROR: Could not load console font" << std::endl;
  }
  this->fontsMap.insert(std::pair<std::string, sf::Font>("rodin_b", rodin_b));

  sf::Font pressStart;
  if (!pressStart.loadFromFile(resourcePath() + "PressStart2P.ttf")) {
    std::cerr << "ERROR: Could not load console font" << std::endl;
  }
  this->fontsMap.insert(
      std::pair<std::string, sf::Font>("pressStart", pressStart));
}

sf::Font ResourceManager::getFont(std::string name) {
  return (this->fontsMap.at(name));
}
