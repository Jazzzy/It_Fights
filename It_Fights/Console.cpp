//
//  Console.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 31/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Console.hpp"
#include "Systems.hpp"
#include "AuxiliarRenderFunctions.hpp"
#include "ResourcePath.hpp"
#include "Clock.hpp"
#include <cmath>
#include "Game.hpp"

extern Game game;

Console::Console(MessageBus * messageBus) : BusNode (Systems::S_Console,messageBus) {
    
    this->current_openness = 0.0f;
    this->target_openness = 0.0f;
    this->max_openness = 0.8f;
    this->open_speed = 2.0f;
    
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        std::cerr << "ERROR: Could not load console font" << std::endl;
    }
    
    this->inputTextColor = sf::Color::Black;
    this->msgTextColor = sf::Color(75,75,75);
    this->messageBackgroundColor = sf::Color(227,194,124,180);    //Light Brown
    this->inputBackgroundColor = sf::Color(189,151,120);      //Darker Brown
    
    this->pixelCharacterSize = 40;
    
}

Console::~Console(){
    
}

void Console::update(){
    updateOpenness();
}

bool Console::isOpen(){
    return (this->current_openness != 0.0f);
}

void Console::evaluateInputLine(){
    //@@TODO: Evaluate here the input line (primarly sens a message with the string to everyone)
    Message consoleMessageToEveryone(this->inputLine.getRealString().toAnsiString());
    send(consoleMessageToEveryone);
    this->inputLine.erase();
}

void Console::onNotify (Message message){
    
    if(message.getEvent().compare("MSG_TOGGLE_CONSOLE")==0){
        if(this->target_openness == 0.0f){
            this->target_openness = this->max_openness;
        }else{
            this->target_openness = 0.0f;
        }
    }else if(message.getEvent().compare("CONSOLE_SHOW_MSG")==0){    //Add a message to the console in a new line
        if(message.getData().type!=MessageData::STRING_PTR){
            std::cerr << "ERROR: The data in this message should be a string pointer" << std::endl;
        }else{
            this->messageLines.push_back(ConsoleLine(sf::String(*(message.getData().string_ptr))));
        }

        delete message.getData().string_ptr; //@@OPTIMIZATION: We could try to instantiate this strings on a custom allocator/memory pool to avoid fragmentation
    }else if(message.getEvent().compare("MSG_CONSOLE_KEYCHAR")==0){
        if(message.getData().type!=MessageData::CHARACTER){
            std::cerr << "ERROR: The data in this message should be a character" << std::endl;
        }else{
            this->inputLine.appendCharacter(message.getData().character);
        }
        
    }else if(message.getEvent().compare("MSG_CONSOLE_KEY")==0){
        if(message.getData().type!=MessageData::KEYBOARD_KEY){
            std::cerr << "ERROR: The data in this message should be keyboard key" << std::endl;
        }else{
            switch(message.getData().key){
                case sf::Keyboard::BackSpace:
                    this->inputLine.removeLastCharacter();
                    break;
                    
                case sf::Keyboard::Return:
                    this->evaluateInputLine();
                    break;
            
                default:
                    break;
            }
        
        }
        
    }
    
}

void Console::draw(sf::RenderTarget *renderTarget){
    
    //Draw the rectangles necessary
    consoleRectangle(renderTarget, 0, 0, 1, this->current_openness, this->messageBackgroundColor, this->inputTextColor);
    
    drawMessages(renderTarget, 0, 0, 1, this->current_openness, this->inputTextColor, this->msgTextColor);
    
}


#define OUTLINE_THICKNESS 8

void Console::consoleRectangle(sf::RenderTarget *renderTarget, float origin_X, float origin_Y , float size_X , float size_Y, sf::Color backgroundColor ,sf:: Color outlineColor){ //dimensions and origin in screen percentages
    
    sf::RectangleShape mainRectangle;
    
    sf::Vector2u renderSize = renderTarget->getSize();
    
    float realOrigin_X = (origin_X * renderSize.x)+OUTLINE_THICKNESS;
    float realOrigin_Y = (origin_Y * renderSize.y)+OUTLINE_THICKNESS;
    
    float realSize_X = (size_X * renderSize.x)-OUTLINE_THICKNESS*2;
    float realSize_Y = (size_Y * renderSize.y)-OUTLINE_THICKNESS*2;
    
    mainRectangle.setSize(sf::Vector2f(realSize_X,realSize_Y));
    mainRectangle.setFillColor(backgroundColor);
    mainRectangle.setOutlineColor(outlineColor);
    mainRectangle.setOutlineThickness(OUTLINE_THICKNESS);
    mainRectangle.setPosition(realOrigin_X, realOrigin_Y);
    
    
    renderTarget->draw(mainRectangle);
    
    
}

#define VERTICAL_PADDING 7
#define HORIZONTAL_PADDING 7

void Console::drawMessages(sf::RenderTarget *renderTarget, float origin_X, float origin_Y , float size_X , float size_Y, sf::Color textColor, sf::Color softTextColor){
    
    sf::Vector2u renderSize = renderTarget->getSize();
    
    float realOrigin_X = (origin_X * renderSize.x) + HORIZONTAL_PADDING +OUTLINE_THICKNESS;
    float realOrigin_Y = (origin_Y * renderSize.y) + VERTICAL_PADDING +OUTLINE_THICKNESS;
    
    float realSize_X = (size_X * renderSize.x) - HORIZONTAL_PADDING - OUTLINE_THICKNESS*2;
    float realSize_Y = (size_Y * renderSize.y) - VERTICAL_PADDING - OUTLINE_THICKNESS*2;
    
    //First we print the input line
    
    sf::Text text(this->inputLine.getString(),this->font, this->pixelCharacterSize);
    text.setFillColor(textColor);
    
    float pixelDelta = this->pixelCharacterSize + VERTICAL_PADDING;
    float maxPosition = realSize_Y;
    
    float currentPosition_Y = maxPosition - pixelDelta;
    text.setPosition(realOrigin_X, currentPosition_Y);
    
    renderTarget->draw(text);
    
    {
        currentPosition_Y -= VERTICAL_PADDING;
        float spaceAvailable_y = currentPosition_Y - realOrigin_Y;
        unsigned int totalLinesAvailable = std::ceil(spaceAvailable_y/pixelDelta);
        auto iter = this->messageLines.rbegin();
        text.setFillColor(softTextColor);
        unsigned int linesPrinted;
        for(linesPrinted = 0 ; (iter != this->messageLines.rend()) && (linesPrinted<=totalLinesAvailable) ; ++iter, linesPrinted ++){   //We iterate from the end of the list;
            currentPosition_Y -= pixelDelta;
            text.setString(iter->getString());
            text.setPosition(realOrigin_X, currentPosition_Y);
            renderTarget->draw(text);
        }
    }
    
    
}


void Console::updateOpenness(){
    
    double deltaOpenness = this->open_speed * game.getDeltaClock()->getDeltaTime();
    
    if(this->current_openness < this->target_openness ){
        this->current_openness += deltaOpenness;
        if(this->current_openness > this->max_openness){
            this->current_openness = this->max_openness;
            //We could play a sound marking the fac that we have open the console
        }
    }else if(this->current_openness > this->target_openness){
        this->current_openness -= deltaOpenness;
        if(this->current_openness < 0){
            this->current_openness = 0;
            //We could play a sound marking the fac that we have closed the console
        }
        
    }
    
}

