#include <SFML/Window.hpp>
#include <iostream>
#include "MovementSystem.hpp"
#include "EntityManager.hpp"

void MovementSystem::apply(registry& reg) 
{
  const float MOVEMENT_SPEED = 0.1f;
  sf::Sprite& playerSprite = reg.sprites[1].sprite;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
  {
    std::cout << "Left key pressed\n";
    EntityManager::displayEntity(1, reg); // Assuming entity 1 is the player
    playerSprite.move({-MOVEMENT_SPEED, 0.f});
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
  {
    playerSprite.move({MOVEMENT_SPEED, 0.f});
  }
}
