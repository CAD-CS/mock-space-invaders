#include <SFML/Window.hpp>
#include <iostream>
#include "MovementSystem.hpp"
#include "EntityManager.hpp"

sf::Event createKeyEvent(sf::Keyboard::Key keycode) 
{
  sf::Event event;
  event.type = sf::Event::KeyPressed;
  event.key.code = keycode;
  event.key.alt = false;
  event.key.control = false;
  event.key.shift = false;
  event.key.system = false;
  return event;
}

void MovementSystem::apply(registry& reg, sf::Event event) 
{
    const float MOVEMENT_SPEED = 5.0f;
    sf::Sprite& playerSprite = reg.sprites[1].sprite;
    
    if (event.key.code == sf::Keyboard::Left) {
        playerSprite.move(-MOVEMENT_SPEED, 0.f);
    }
    else if (event.key.code == sf::Keyboard::Right) {
        playerSprite.move(MOVEMENT_SPEED, 0.f);
    }
    
    // Update the position component to match sprite position
    auto pos = playerSprite.getPosition();
    reg.positions[1] = {pos.x, pos.y};
}
