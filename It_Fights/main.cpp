#include "BusNode.hpp"
#include "MessageBus.hpp"
#include "Window.hpp"
#include "Clock.hpp"
#include "Input.hpp"
#include "Console.hpp"

Clock m_clock;

//TODO: Make a GameState class that knows if the console is open and then send the keypresses to the console it if is open from the input system

int main(int, char const**){
    
    MessageBus messageBus;
    
    Console consoleSystem(&messageBus);
    Window windowSystem (&messageBus,&consoleSystem,"It_fights",2000,1500);
    Input inputSystem (&messageBus,&windowSystem);
    
    while(windowSystem.isOpen()){
        inputSystem.update();
        consoleSystem.update();
        windowSystem.update();
        messageBus.notify();
    }
    
    return 0;
}
