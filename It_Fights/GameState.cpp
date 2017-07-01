//
//  GameState.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "GameState.hpp"
#include "DebugUtilities.hpp"
#include "Game.hpp"
#include "Level_00_NeoPurple_DEMO.hpp"
#include "MenuScene.hpp"
#include "Systems.hpp"

extern Game* game;

GameState::GameState(MessageBus* messageBus)
    : BusNode(Systems::S_GameState, messageBus) {
  this->scene = new MenuScene(messageBus);
  this->mainMenu = true;
  this->paused = false;
  this->simulationsLeft = 0;
}

GameState::~GameState() { delete this->scene; }

void GameState::update() { this->scene->update(); }

extern bool simulating;

void GameState::onNotify(Message message) {
  if (message.getEvent().compare("MSG_GO_TO_MENU") == 0) {
    if (this->scene != nullptr) {
      this->scene->onEnd();
      delete this->scene;
    }

    if (this->simulationsLeft > 1) {
      this->simulationsLeft--;
      prints("Simulations left: " << this->simulationsLeft);
      this->scene = new Level_00_NeoPurple_DEMO(
          messageBus, CharacterOptions::AGENT_VS_AGENT, false);
      this->scene->onStart();
    } else {
      simulating = false;
      Message messagePop("MSG_SOUND_POP");
      this->scene->send(messagePop);
      this->scene = new MenuScene(messageBus);
      this->scene->onStart();
    }

  } else if (message.getEvent().compare("MSG_GO_TO_MAINGAME_AGENT_VS_AGENT") ==
             0) {
    if (this->scene != nullptr) {
      this->scene->onEnd();
      delete this->scene;
    }
    simulating = false;
    this->scene = new Level_00_NeoPurple_DEMO(
        messageBus, CharacterOptions::AGENT_VS_AGENT, true);
    this->scene->onStart();
  } else if (message.getEvent().compare("MSG_GO_TO_MAINGAME_HUMAN_VS_AGENT") ==
             0) {
    if (this->scene != nullptr) {
      this->scene->onEnd();
      delete this->scene;
    }
    simulating = false;
    this->scene = new Level_00_NeoPurple_DEMO(
        messageBus, CharacterOptions::HUMAN_VS_AGENT, true);
    this->scene->onStart();
  } else if (message.getEvent().compare("MSG_GO_TO_MAINGAME_HUMAN_VS_HUMAN") ==
             0) {
    if (this->scene != nullptr) {
      this->scene->onEnd();
      delete this->scene;
    }
    simulating = false;
    this->scene = new Level_00_NeoPurple_DEMO(
        messageBus, CharacterOptions::HUMAN_VS_HUMAN, true);
    this->scene->onStart();
  } else if (message.getEvent().compare(
                 "MSG_GO_TO_MAINGAME_AGENT_VS_AGENT_NO_RENDERING") == 0) {
    if (this->scene != nullptr) {
      this->scene->onEnd();
      delete this->scene;
    }
    simulating = true;
    this->simulationsLeft = NUMBER_OF_SIMULATIONS;
    prints("Simulations left: " << this->simulationsLeft);
    this->scene = new Level_00_NeoPurple_DEMO(
        messageBus, CharacterOptions::AGENT_VS_AGENT, false);
    this->scene->onStart();
  }
}

Scene* GameState::getScene() { return this->scene; }

bool GameState::isConsoleOpen() { return game->isConsoleOpen(); }

bool GameState::isGamePaused() { return this->paused; }

bool GameState::areWeInMainMenu() { return this->mainMenu; }
