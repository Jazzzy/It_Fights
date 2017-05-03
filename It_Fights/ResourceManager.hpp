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
    static ResourceManager& Instance();
    
    sf::Font getFont(std::string name);
    
private:
    static void CleanUp();
    static ResourceManager* MInstance;
    
    ResourceManager();
    ~ResourceManager(){}
    
    ResourceManager(ResourceManager const&);
    ResourceManager& operator=(ResourceManager const&);
    
    std::unordered_map<std::string, sf::Font> fontsMap;
    void loadFonts();
    
};



#endif /* ResourceManager_hpp */
