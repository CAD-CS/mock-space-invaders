#include <string>
#include "Game.hpp"

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 900;

int main()
{
  Game game(static_cast<unsigned int>(WINDOW_WIDTH), static_cast<unsigned int>(WINDOW_HEIGHT), "Mock Invaders");
  game.run();
  return 0;
}
