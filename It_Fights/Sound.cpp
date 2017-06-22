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
  sf::SoundBuffer* bufferWistle = new sf::SoundBuffer();
  if (!bufferWistle->loadFromFile(resourcePath() + "whistle.wav")) {
    std::cerr << "ERROR: Could not load console font" << std::endl;
  }
  this->bufferMap.insert(std::make_pair("whistle", bufferWistle));

  sf::Sound* whistleSound = new sf::Sound(*bufferWistle);
  this->soundMap.insert(std::make_pair("whistle", whistleSound));
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
    this->soundMap["whistle"]->play();
  }
}
