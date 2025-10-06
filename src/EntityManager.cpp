#include "EntityManager.hpp"
#include <cassert>
#include <iostream>

EntityManager::EntityManager() : m_entities(0) {}

EntityManager::~EntityManager() {
    m_textures.clear();
}

entity_t EntityManager::createEntity()
{
    assert(m_entities < MAX_ENTITIES && "Too many entities in existence.");
    return ++m_entities;
}

registry& EntityManager::getRegistry() { return m_registry;}

entity_t EntityManager::getEntities() { return m_entities; }

void EntityManager::init(int windowWidth, int windowHeight)
{
  entity_t player = createEntity();
  entity_t enemy = createEntity();
  entity_t block = createEntity();

  initSprite(player, "./assets/player.jpg");
  initSprite(enemy, "./assets/enemy.jpg");
  initSprite(block, "./assets/block.jpg");

  initPosition(player, 150.0f, 300.0f);
  initPosition(enemy, 150.0f, 50.0f);
  initPosition(block, 100.0f, 200.0f);

  initVelocity(player);
  initVelocity(enemy);
  initVelocity(block);

}

void EntityManager::initSprite(entity_t entity, std::string texturePath)
{
  sf::Texture texture;

  if (!texture.loadFromFile(texturePath))
  {
    std::cerr << "Failed to load texture from " << texturePath << std::endl;
    return;
  }

  sf::Sprite sprite;
  sprite.setTexture(texture);

  m_textures.push_back(texture);

  m_registry.sprites[entity] = {sprite};
}

void EntityManager::initPosition(entity_t entity, float x, float y)
{
  m_registry.positions[entity] = {x, y};
}

void EntityManager::initVelocity(entity_t entity)
{
  m_registry.velocities[entity] = {0.0f, 0.0f};
}