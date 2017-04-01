
#include "Game.hpp"

Game game;

//TODO: Make a Game class that knows if the console is open and then send the keypresses to the console it if is open from the input system

int main(int, char const**){
    
    game.loop();
    
    return 0;
}
