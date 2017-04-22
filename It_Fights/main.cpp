
#include "Game.hpp"
#include "ResourceManager.hpp"

ResourceManager resourceManager;
Game game;

int main(int, char const**){
    game.loop();
    return 0;
}
