#include "MovementSystem.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <iostream>

void MovementSystem::apply(sf::Event event, registry& reg)
{
  switch (event.key.code)
  {
    case sf::Keyboard::Left:
      std::cout << "LEFT" << std::endl;
      break;
    case sf::Keyboard::Right:
      std::cout << "Right" << std::endl;
    default:
      std::cout << "Invalid" << std::endl;
  }
}
