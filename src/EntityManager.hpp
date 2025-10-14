#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include "Components.hpp"

constexpr entity_t MAX_ENTITIES = 5;

class EntityManager
{

private:
  entity_t m_entities;
  entity_t m_player;
  registry m_registry;
  std::vector<sf::Texture> m_textures;

  entity_t createEntity();
  void initSprite(entity_t, std::string);
  void initPosition(entity_t, float, float);
  void initVelocity(entity_t);

public:
  EntityManager();
  ~EntityManager();

  void init(int, int);
  registry& getRegistry();
  entity_t getEntities();
  entity_t getPlayer();
  sf::Sprite& getSprite(entity_t entity);

  void static displayEntity(entity_t entity, registry registry);
};
