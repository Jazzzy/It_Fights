//
//  Window.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 28/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include "BusNode.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include "Console.hpp"

#define INTERNAL_RESOLUTION_X 2000
#define INTERNAL_RESOLUTION_Y 1500

class Window : BusNode {
public:
    Window(MessageBus * messageBus, Console *console, std::string windowName , int resolution_x , int resolution_y );
    ~Window();
    void update();
    sf::Window * getInternalWindowRef();
    sf::RenderTarget * getMainRenderTarget();
    bool isOpen();
    
private:
    Console *console;
    void onNotify (Message message);
    sf::RenderWindow sf_window;
    sf::RenderTexture sf_renderTexture;
    void tryToResize(unsigned int x, unsigned int y);
    sf::Vector2u currRealResolution;
    
};


#endif /* Window_hpp */
