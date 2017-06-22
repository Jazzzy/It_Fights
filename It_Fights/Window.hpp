//
//  Window.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 28/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <SFML/Graphics.hpp>
#include <string>


#include "BusNode.hpp"

// Needs a refference to this in order to be able to draw them
#include "Console.hpp"
#include "Collisions.hpp"

class Window : BusNode {
public:
    Window(MessageBus * messageBus, Console *console, Collisions* collisionSystem ,std::string windowName , int resolution_x , int resolution_y );
    ~Window();
    void update();
    sf::Window * getInternalWindowRef();
    sf::RenderTarget * getMainRenderTarget();
    bool isOpen();
    void toggleShouldRender();
    std::pair<unsigned int, unsigned int> getCurrentInternalResolution();
    void setCurrentInternalResolution(std::pair<unsigned int, unsigned int> newResolution);
    
private:
    Console *console;
    Collisions * collisionSystem;
    void onNotify (Message message);
    sf::RenderWindow sf_window;
    sf::RenderTexture sf_renderTexture;
    sf::RenderTexture sf_renderTexture_HighRes;
    
    void tryToResize(unsigned int x, unsigned int y);
    sf::Vector2u currRealResolution;
    bool shouldRender;
    
    std::pair<unsigned int,unsigned int> internalResolution;
    std::pair<double,double> renderTextureScale;
    void recalculateScale();
    
    void newToastMessage(std::string message, float seconds);
    void drawToast(sf::RenderTarget * renderTarget);
    float timeRemainingForToast;
    std::string toastMessage;
    sf::Font toastFont;
    
    
};


#endif /* Window_hpp */
