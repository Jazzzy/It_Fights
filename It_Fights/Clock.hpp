//
//  Clock.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 28/3/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef Clock_hpp
#define Clock_hpp

#include <SFML/Audio.hpp>
#include <deque>
#include <functional>

class Clock {
public:
    static Clock& Instance();
    
    void setFrameSeparator();
    float getDeltaTime();
    float getMeanDeltaTime();
    unsigned int getMeanFPS();
    void setTimeScale(float timeScale);
    float getTimeScale();
    unsigned long getCurrentFrameCount();

private :
    static void CleanUp();
    
    Clock();
    ~Clock(){}
    
    Clock (Clock const&);
    Clock& operator=(Clock const&);
    
    static Clock* MInstance;
    
    void first20Update();
    void runningUpdate();
    
    sf::Clock deltaClock;
    float deltaTime;
    std::deque<float> timesQueue;
    float meanDeltaTime;
    std::function<void()> updateFunction;
    unsigned long currentFrameCount;
    
    float timeScale;
    
    void updateQueue(sf::Time time);
    
};



#endif /* Clock_hpp */
