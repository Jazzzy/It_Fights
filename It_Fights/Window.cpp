//
//  Window.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 28/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Window.hpp"
#include "Systems.hpp"
#include <iostream>
#include "Clock.hpp"
#include "Game.hpp"
#include "ResourcePath.hpp"


extern Game game;

Window::Window(MessageBus * messageBus, Console * console, std::string windowName , int resolution_x , int resolution_y ) :  BusNode(Systems::S_Window,messageBus), sf_window(sf::VideoMode(resolution_x,resolution_y),windowName) , sf_renderTexture(){
    
    this->sf_window.setVerticalSyncEnabled(true);
    //this->sf_window.setFramerateLimit(300);
    
    this->console = console;
    sf_renderTexture.create(INTERNAL_RESOLUTION_X, INTERNAL_RESOLUTION_Y);
    sf_renderTexture.setSmooth(true);
    this->currRealResolution = sf::Vector2u(resolution_x,resolution_y);
    
    this->shouldRender = true;
        
}

sf::Window * Window::getInternalWindowRef(){
    return &(this->sf_window);
}

Window::~Window(){
    //    std::cout << "Window System deleting" << std::endl;
}

void Window::toggleShouldRender(){
    this->shouldRender= !this->shouldRender;
}


void Window::update(){
    
    if(!this->shouldRender){
        game.getDeltaClock()->setFrameSeparator();
        return;
    }
    
    this->sf_window.clear(sf::Color::Black);

    this->sf_renderTexture.clear(sf::Color(227,218,201)); //Boneish color
    //Draw here everything to the texture
    
    game.getGameState()->getScene()->draw(&sf_renderTexture);
    
    
    /*
        Could be a good idea to have a scene with a list of drawable objects that can be accesed from here, maybe a scene with layers that have objects with shaders, this way we draw the layers in order and can move them independantly just calling each layer "draw" method.
     */
    
    //Apply here every fullscreen shader
    
    
    if(this->console->isOpen()){
        this->console->draw(&sf_renderTexture);
    }

    this->sf_renderTexture.display();
    
    sf_window.draw(sf::Sprite(this->sf_renderTexture.getTexture()));
    
    this->sf_window.display();
    
    game.getDeltaClock()->setFrameSeparator();
    
}



void Window::tryToResize(unsigned int x, unsigned int y){
    
    bool goingBigger = ( x > this->currRealResolution.x || y > this->currRealResolution.y );
    
    float desiredRatio = (float)INTERNAL_RESOLUTION_X/(float)INTERNAL_RESOLUTION_Y;
    float currentRatio = (float)x/(float)y;
    
    if(goingBigger){
        if(currentRatio > desiredRatio){
            y = x/desiredRatio;
        }else{
            x = y*desiredRatio;
        }
    }else{
        if(currentRatio > desiredRatio){
            x = y*desiredRatio;
        }else{
            y = x/desiredRatio;
        }
    }
    
    this->currRealResolution = sf::Vector2u(x,y);
    this->sf_window.setSize(this->currRealResolution);
    
}

void Window::onNotify (Message message){
    if(message.getEvent().compare("MSG_CLOSE_WINDOW")==0){
        this->sf_window.close();
    }else if(message.getEvent().compare("MSG_RESIZED_WINDOW")==0){
        if(message.getData().type!=MessageData::PAIR_OF_INTS){
            std::cerr << "ERROR: The data in this message should be a pair of ints" << std::endl;
        }else{
            this->tryToResize(message.getData().intPair.x, message.getData().intPair.y);
        }
        
    }
    
}

sf::RenderTarget * Window::getMainRenderTarget(){
    return &(this->sf_renderTexture);
}

bool Window::isOpen(){
    return this->sf_window.isOpen();
}
