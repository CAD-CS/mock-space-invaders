#include "Components.hpp"
#include <SFML/Window.hpp>

class MovementSystem
{
  static constexpr float MOVEMENT_SPEED = 100.f;
  bool static isWithinWindow(const sf::Sprite& sprite, const sf::Vector2u& windowSize, sf::Keyboard::Key direction);
public:
  void static apply(registry&, const sf::Event::KeyPressed* key, sf::Vector2u windowSize);  
};
