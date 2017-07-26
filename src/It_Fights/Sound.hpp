//
//  sound.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 22/6/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef sound_hpp
#define sound_hpp

#include <SFML/Audio.hpp>
#include <unordered_map>
#include "BusNode.hpp"

/**
 Main class of the sound subsystem
 */
class Sound : BusNode {
 public:
  Sound(MessageBus *messageBus);
  ~Sound();

 private:
  void onNotify(Message message);

/**
 Contains the map for all the buffers necessary for the sound.
 */
  std::unordered_map<std::string, sf::SoundBuffer *> bufferMap;
    
/**
 Contains the map for all the sounds playing.
 */
  std::unordered_map<std::string, sf::Sound *> soundMap;

/**
 Plays a specific sound
 */
  void playSound(std::string);
};

#endif /* sound_hpp */
