//
//  ResourceManager.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>

class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager();
    sf::Font getFont(std::string name);
    
private:
    std::unordered_map<std::string, sf::Font> fontsMap;
    void loadFonts();

};



#endif /* ResourceManager_hpp */
