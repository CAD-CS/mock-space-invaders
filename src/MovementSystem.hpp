#include "Components.hpp"
#include <SFML/Window.hpp>

class MovementSystem
{
  static constexpr float MOVEMENT_SPEED = 100.f;
public:
  void static apply(registry&, const sf::Event::KeyPressed* key, sf::Vector2u windowSize);  
};
