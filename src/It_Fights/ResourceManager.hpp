//
//  ResourceManager.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class ResourceManager {
 public:
  static ResourceManager& Instance();

    /**
     Returns the font with the given name
     */
  sf::Font getFont(std::string name);

 private:
  static void CleanUp();
  static ResourceManager* MInstance;

  ResourceManager();
  ~ResourceManager() {}

  ResourceManager(ResourceManager const&);
  ResourceManager& operator=(ResourceManager const&);

    /**
     Stores all the fonts with their name as the key
     */
  std::unordered_map<std::string, sf::Font> fontsMap;
    
    /**
     Loads all the necesary fonts
     */
  void loadFonts();
};

#endif /* ResourceManager_hpp */
