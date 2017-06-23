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

class Sound : BusNode {
 public:
  Sound(MessageBus *messageBus);
  ~Sound();

 private:
  void onNotify(Message message);

  std::unordered_map<std::string, sf::SoundBuffer *> bufferMap;
  std::unordered_map<std::string, sf::Sound *> soundMap;

  void playSound(std::string);
};

#endif /* sound_hpp */
