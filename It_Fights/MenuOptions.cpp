//
//  MenuOptions.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 1/6/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "MenuOptions.hpp"
#include "AuxiliarRenderFunctions.hpp"
#include "Clock.hpp"
#include "DebugUtilities.hpp"
#include "ResourceManager.hpp"
#include "SomeMath.hpp"

MenuOptions::MenuOptions(Scene *scene) : GameObject(scene) {
  this->mainFont = ResourceManager::Instance().getFont("rodin_b");
  this->selectedOption = PLAY_HUMAN_VS_HUMAN;

  for (int i = 0; i < Options::LAST; i++) {
    sf::Text text;

    text.setFillColor(sf::Color::Black);

    text.setOutlineColor(sf::Color::Black);

    text.setString(this->getStringFromOption((Options)i));

    text.setCharacterSize(70.0f);

    text.setFont(mainFont);

    this->optionsVector.push_back(std::make_pair((Options)i, text));
  }
}

MenuOptions::~MenuOptions() {}

std::string MenuOptions::getStringFromOption(Options option) {
  switch (option) {
    case PLAY_AGENT_VS_AGENT:
      return "Agent VS Agent";
      break;

    case PLAY_HUMAN_VS_AGENT:
      return "Human VS Agent";
      break;

    case PLAY_HUMAN_VS_HUMAN:
      return "Human VS Human";
      break;

    case PLAY_AGENT_VS_AGENT_NO_RENDERING:
      return "Agent VS Agent (No rendering)";
      break;

    case CLOSE:
      return "Close";
      break;

    case LAST:
      return "";
      break;
  }

  return "";
}

void MenuOptions::moveSelection(Direction direction) {
  switch (direction) {
    case Direction::MOVE_MENU_UP:
      this->changeSelection(-1);
      break;
    case Direction::MOVE_MENU_DOWN:
      this->changeSelection(+1);
      break;
  }

  Message messageWhistle("MSG_SOUND_WHISTLE");
  this->scene->send(messageWhistle);
}

void MenuOptions::changeSelection(short delta) {
  short maxOptionNumber = Options::LAST;

  short newSelectedOption = (this->selectedOption + delta) % maxOptionNumber;

  if (newSelectedOption < 0) newSelectedOption = maxOptionNumber - 1;

  this->selectedOption = (Options)newSelectedOption;
}

void MenuOptions::executeSelection() {
  switch (this->selectedOption) {
    case PLAY_AGENT_VS_AGENT: {
      Message msgMainGame("MSG_GO_TO_MAINGAME_AGENT_VS_AGENT");
      this->scene->send(msgMainGame);
    } break;

    case PLAY_HUMAN_VS_AGENT: {
      Message msgMainGame("MSG_GO_TO_MAINGAME_HUMAN_VS_AGENT");
      this->scene->send(msgMainGame);
    } break;

    case PLAY_HUMAN_VS_HUMAN: {
      Message msgMainGame("MSG_GO_TO_MAINGAME_HUMAN_VS_HUMAN");
      this->scene->send(msgMainGame);
    } break;

    case PLAY_AGENT_VS_AGENT_NO_RENDERING: {
      Message msgMainGame("MSG_GO_TO_MAINGAME_AGENT_VS_AGENT_NO_RENDERING");
      this->scene->send(msgMainGame);
    } break;

    case CLOSE: {
      Message msgExitGame("MSG_CLOSE_WINDOW");
      this->scene->send(msgExitGame);
    } break;

    case LAST:
      break;
  }
}

#define LERP_SPEED 0.85

void MenuOptions::update() {
  shownOptionPosition.x = selectedOptionPosition.x;
  shownOptionPosition.y =
      lerp(shownOptionPosition.y, selectedOptionPosition.y, (float)LERP_SPEED);

  shownOptionSize.y = selectedOptionSize.y;
  shownOptionSize.x =
      lerp(shownOptionSize.x, selectedOptionSize.x, (float)LERP_SPEED);
}

#define SELECTION_BAR_WIDTH (15)
#define SELECTION_HEIGTH_PADDING (100)

void MenuOptions::draw(sf::RenderTarget *renderTarget) {
  sf::Vector2f startRectPosition(0.22, 0.50);

  sf::Vector2f percentagePosition(0.25, 0.50);

  for (auto option : this->optionsVector) {
    PairI position =
        getRealPixels(renderTarget, percentagePosition.x, percentagePosition.y);
    option.second.setPosition(position.x, position.y);
    percentagePosition.y += 0.1;

    if (option.first == this->selectedOption) {
      option.second.setOutlineThickness(1.0f);
      selectedOptionPosition = sf::Vector2f(
          option.second.getPosition().x,
          option.second.getPosition().y + SELECTION_HEIGTH_PADDING);
      selectedOptionSize = sf::Vector2f(option.second.getLocalBounds().width,
                                        SELECTION_BAR_WIDTH);
    } else {
      option.second.setOutlineThickness(0.0f);
    }

    renderTarget->draw(option.second);
  }

  sf::Vector2f sizePerc(0.01, percentagePosition.y - 0.53);

  sf::RectangleShape sideRectangle;
  sideRectangle.setFillColor(sf::Color::Black);
  PairI startPosition =
      getRealPixels(renderTarget, startRectPosition.x, startRectPosition.y);
  sideRectangle.setPosition(startPosition.x, startPosition.y);
  PairI realSize = getRealPixels(renderTarget, sizePerc.x, sizePerc.y);
  sf::Vector2f sizeVector(realSize.x, realSize.y);
  sideRectangle.setSize(sizeVector);

  renderTarget->draw(sideRectangle);

  sf::RectangleShape selectionRectangle;
  selectionRectangle.setFillColor(sf::Color::Black);
  selectionRectangle.setPosition(shownOptionPosition);
  selectionRectangle.setSize(shownOptionSize);

  renderTarget->draw(selectionRectangle);
}
