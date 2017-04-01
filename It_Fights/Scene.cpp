//
//  Scene.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Scene.hpp"
#include "Systems.hpp"
#include "Game.hpp"

extern Game game;

Scene::Scene(MessageBus * messageBus) : BusNode(Systems::S_CurrentScene, messageBus) {

}

Scene::~Scene(){}

void Scene::addGameObject(GameObject * gameObject){
    this->listOfGameObjects.push_back(gameObject);
}

void Scene::update(){
    
    
    for(auto iter = this->listOfGameObjects.begin(); iter!=this->listOfGameObjects.end(); ++iter ){
        (*iter)->update();
    }

}

void Scene::draw(sf::RenderTarget *renderTarget){
    
    for(auto iter = this->listOfGameObjects.begin(); iter!=this->listOfGameObjects.end(); ++iter ){
        (*iter)->draw(renderTarget);
    }
    
}
