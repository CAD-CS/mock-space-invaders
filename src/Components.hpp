#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>

using entity_t = std::size_t;

struct velocity_component
{
  float xVel;
  float yVel;
};

struct texture_component
{
  sf::Texture texture;
};

struct registry
{
  std::unordered_map<entity_t, velocity_component> velocities;
  std::unordered_map<entity_t, sf::Sprite> sprites;
};