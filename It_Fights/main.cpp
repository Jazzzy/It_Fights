
#include "Game.hpp"
#include "ResourceManager.hpp"

Game *game;

int main(int, char const**){
    game = new Game();
    game->loop();
    delete game;
    return 0;
}
