#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>

using entity_t = std::size_t;

struct position_component
{
  float x;
  float y;
};

struct velocity_component
{
  float xVel;
  float yVel;
};

struct sprite_component
{
  sf::Sprite sprite;
};

struct texture_component
{
  sf::Texture texture;
};

struct registry
{
  std::unordered_map<entity_t, position_component> positions;
  std::unordered_map<entity_t, velocity_component> velocities;
  std::unordered_map<entity_t, sprite_component> sprites;
};