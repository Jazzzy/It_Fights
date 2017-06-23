//
//  sound.cpp
//  It_Fights
//
//  Created by Rubén Osorio López on 22/6/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#include "Sound.hpp"
#include "DebugUtilities.hpp"
#include "ResourcePath.hpp"
#include "Systems.hpp"

Sound::Sound(MessageBus* messageBus) : BusNode(Systems::S_Sound, messageBus) {
  /*WHISTLE SOUND*/
  sf::SoundBuffer* bufferWistle = new sf::SoundBuffer();
  if (!bufferWistle->loadFromFile(resourcePath() + "whistle.wav")) {
    std::cerr << "ERROR: Could not load console font" << std::endl;
  }
  this->bufferMap.insert(std::make_pair("whistle", bufferWistle));

  sf::Sound* whistleSound = new sf::Sound(*bufferWistle);
  this->soundMap.insert(std::make_pair("whistle", whistleSound));

  /*POP sound*/
  sf::SoundBuffer* popWistle = new sf::SoundBuffer();
  if (!popWistle->loadFromFile(resourcePath() + "pop.wav")) {
    std::cerr << "ERROR: Could not load console font" << std::endl;
  }
  this->bufferMap.insert(std::make_pair("pop", popWistle));

  sf::Sound* popSound = new sf::Sound(*popWistle);
  this->soundMap.insert(std::make_pair("pop", popSound));

  /*SLASH sound*/
  sf::SoundBuffer* slashWistle = new sf::SoundBuffer();
  if (!slashWistle->loadFromFile(resourcePath() + "slash.wav")) {
    std::cerr << "ERROR: Could not load console font" << std::endl;
  }
  this->bufferMap.insert(std::make_pair("slash", slashWistle));

  sf::Sound* slashSound = new sf::Sound(*slashWistle);
  slashSound->setVolume(70.f);
  this->soundMap.insert(std::make_pair("slash", slashSound));

  /*DAMAGE sound*/
  sf::SoundBuffer* damageWistle = new sf::SoundBuffer();
  if (!damageWistle->loadFromFile(resourcePath() + "damage.wav")) {
    std::cerr << "ERROR: Could not load console font" << std::endl;
  }
  this->bufferMap.insert(std::make_pair("damage", damageWistle));

  sf::Sound* damageSound = new sf::Sound(*damageWistle);
  damageSound->setVolume(70.f);
  this->soundMap.insert(std::make_pair("damage", damageSound));
}

Sound::~Sound() {
  for (auto i = this->soundMap.begin(); i != this->soundMap.end(); ++i) {
    i->second->stop();
    delete i->second;
  }

  for (auto i = this->bufferMap.begin(); i != this->bufferMap.end(); ++i) {
    delete i->second;
  }
}

void Sound::onNotify(Message message) {
  if (message.getEvent().compare("MSG_SOUND_WHISTLE") == 0) {
    this->playSound("whistle");
  } else if (message.getEvent().compare("MSG_SOUND_POP") == 0) {
    this->playSound("pop");
  } else if (message.getEvent().compare("MSG_SOUND_SLASH") == 0) {
    this->playSound("slash");
  } else if (message.getEvent().compare("MSG_SOUND_DAMAGE") == 0) {
    this->playSound("damage");
  }
}

extern bool simulating;

void Sound::playSound(std::string name) {
  if (this->soundMap.find(name) != this->soundMap.end() && !simulating) {
    this->soundMap[name]->play();
  }
}
