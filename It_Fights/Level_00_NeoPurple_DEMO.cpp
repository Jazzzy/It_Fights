//
//  level_00_NeoPurple_DEMO.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 21/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Level_00_NeoPurple_DEMO.hpp"
#include "Window.hpp"
#include "Systems.hpp"
#include "DebugUtilities.hpp"
#include "Clock.hpp"



Level_00_NeoPurple_DEMO::Level_00_NeoPurple_DEMO(MessageBus * messageBus, CharacterOptions characterOptions, bool shouldRender) :
Scene(messageBus),
level_00_GO_Ground(this),
view(sf::FloatRect(0,0,LVL_00_RESOLUTION_X,LVL_00_RESOLUTION_Y)),
level_00_GO_Characters(this,characterOptions),
level_00_GO_HealthBars(this,&level_00_GO_Characters,&this->fightClock)
{
    this->shouldRender = shouldRender;
    
    changedRes = false;
    
    //We add all GameObjects necessary to with "this->addGameObject(GameObject * gameObject)"
    this->addGameObject(&level_00_GO_Ground);
    this->addGameObject(&level_00_GO_Characters);
    this->addGameObject(&level_00_GO_HealthBars);
    
    this->localUpdateFunction = [&](){ this->localUpdateImplemented(); };
    this->fullScreenShadersFunc = [this](sf::RenderTarget * renderTarget,const sf::Texture * screenTexture){
        this->screenShaders(renderTarget,screenTexture);
    };
    
    
    if(!this->shouldRender){
        Message msgRender("MSG_TOGGLE_RENDER");
        this->send(msgRender);
        Clock::Instance().setTimeScale(TIME_SCALE); //Simulates physics like it was playing at 30fps more or less
    }
    
    this->fightClock.restart();
    
}

Level_00_NeoPurple_DEMO::~Level_00_NeoPurple_DEMO(){
        if(!this->shouldRender){
            Clock::Instance().setTimeScale(1.f);
            Message msgRender("MSG_TOGGLE_RENDER");
            this->send(msgRender);
        }
}


void Level_00_NeoPurple_DEMO::screenShaders(sf::RenderTarget * renderTarget, const sf::Texture * screenTexture){
    

    
}



void Level_00_NeoPurple_DEMO::localUpdateImplemented(){
    if(!changedRes){
        //We tell the window to render in an specific resolution
        PairI intPair{.x =  static_cast<int>(LVL_00_RESOLUTION_X), .y =  static_cast<int>(LVL_00_RESOLUTION_Y)};
        MessageData pairData{MessageData::PAIR_OF_INTS, .intPair = intPair };
        Message msg_internalRes("MSG_RESIZE_INTERNAL_RESOLUTION",Systems::S_Window, pairData);
        send(msg_internalRes);
        
        changedRes = true;
        
        
        Message msg_smoothFalse("MSG_SMOOTH_FALSE",Systems::S_Window);
        send(msg_smoothFalse);
        
    }
    
    if((this->fightClock.getElapsedTime().asSeconds() * Clock::Instance().getTimeScale()) >= TIME_LIMIT_IN_SECONDS){
    
        if(this->level_00_GO_Characters.getCharacter_1()->getHealthNormalized() > this->level_00_GO_Characters.getCharacter_2()->getHealthNormalized()){
        
            this->win(PLAYER_1);
            
        }else if(this->level_00_GO_Characters.getCharacter_1()->getHealthNormalized() < this->level_00_GO_Characters.getCharacter_2()->getHealthNormalized()){
        
            this->win(PLAYER_2);
            
        }else{
            //Draw
        }
        
        Message messageToMenu("MSG_GO_TO_MENU");
        this->send(messageToMenu);

    }
    

}

void Level_00_NeoPurple_DEMO::onNotify(Message message){
    
    if(message.getEvent().compare("MSG_BUTTON_PRESSED")==0){
        if(message.getData().type!=MessageData::INTEGER){
            std::cerr << "ERROR: The data in this message should be an integer" << std::endl;
        }else{
            switch(message.getData().integer){
                case 9:        //Back button
                {
                    Message messageToMenu("MSG_GO_TO_MENU");
                    this->send(messageToMenu);
                    break;
                }
                default:
                    break;
            }
        }
    }else if(message.getEvent().compare("MSG_THE_LOOSER_IS")==0){
        if(message.getData().type!=MessageData::INTEGER){
            std::cerr << "ERROR: The data in this message should be an integer" << std::endl;
        }else{
            switch(message.getData().integer){
                case PLAYER_1:
                    
                    this->win(PLAYER_2);
                    break;
                
                case PLAYER_2:
                    
                    this->win(PLAYER_1);
                    break;
            
                default:
                    break;
            }
        }
    }else{
    
    }

}

void Level_00_NeoPurple_DEMO::win(Position player){

    switch(player){
        case PLAYER_1:
            
            prints("Player 1 is the winner!");
            
            break;
            
        case PLAYER_2:
            
            prints("Player 2 is the winner!");
            
            break;
            
        default:
            break;
    }

}



