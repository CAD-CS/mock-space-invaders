#include <string>
#include "core/Game.hpp"

const int WINDOW_WIDTH = 1900;
const int WINDOW_HEIGHT = 1000;

int main()
{
    Game game(static_cast<unsigned int>(WINDOW_WIDTH), static_cast<unsigned int>(WINDOW_HEIGHT), "Mock Invaders");
    game.run();
    return 0;
}
