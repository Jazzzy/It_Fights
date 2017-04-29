//
//  Console.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 31/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Console_hpp
#define Console_hpp


#include <SFML/Graphics.hpp>
#include <vector>


#include "BusNode.hpp"
#include "Drawable.hpp"
#include "ConsoleLine.hpp"
#include "InputLine.hpp"
#include "ResourceManager.hpp"

class Console : BusNode, Drawable {
public:
    Console(MessageBus * messageBus);
    ~Console();
    void toggleOpen();
    bool isOpen();
    void draw(sf::RenderTarget *renderTarget);
    void update();
    
    
private:
    
    void onNotify (Message message);
    
    //Opening variables/functions
    float current_openness;
    float target_openness;
    float max_openness;
    float open_speed;
    void updateOpenness();
    
    
    //Drawing variables/functions
    sf::Font font;
    sf::Color inputTextColor;
    sf::Color msgTextColor;
    sf::Color inputBackgroundColor;
    sf::Color messageBackgroundColor;
    unsigned int pixelCharacterSize;
    
    void consoleRectangle(sf::RenderTarget *renderTarget, float origin_X, float origin_Y , float size_X , float size_Y, sf::Color backgroundColor ,sf:: Color outlineColor);
    void drawMessages(sf::RenderTarget *renderTarget, float origin_X, float origin_Y , float size_X , float size_Y, sf::Color textColor, sf::Color softTextColor);
    void drawFps(sf::RenderTarget *renderTarget, float origin_X, float origin_Y , sf::Color textColor);
    
    bool showFps;
    
    
    //ConsoleLines
    std::vector<ConsoleLine> messageLines;
    InputLine inputLine;
    void evaluateInputLine();
    
    
    
};


#endif /* Console_hpp */
