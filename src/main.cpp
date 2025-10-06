#include <iostream>
#include <string>

#include "EntityManager.hpp"
#include "Game.hpp"

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 900;

int main()
{
  Game game(WINDOW_WIDTH, WINDOW_HEIGHT, "Mock Invaders");
  game.run();
  return 0;
}
