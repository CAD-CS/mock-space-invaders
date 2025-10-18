#include "Components.hpp"
#include <SFML/Window.hpp>

class MovementSystem
{
public:
  void static apply(registry&, sf::Event event);  
};
