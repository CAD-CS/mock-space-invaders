#include "EntityManager.hpp"
#include <cassert>
#include <iostream>

EntityManager::EntityManager() : m_entities(0) {
  m_textures.reserve(MAX_ENTITIES);
}

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


  {
    sf::Sprite& sprite = m_registry.sprites[player].sprite;
    float x = (windowWidth - sprite.getLocalBounds().width) / 2.f;
    float y = windowHeight - sprite.getLocalBounds().height;
    initPosition(player, x, y);
  }

  {
    sf::Sprite& sprite = m_registry.sprites[enemy].sprite;
    float x = (windowWidth - sprite.getLocalBounds().width) / 2.f;
    float y = 0.f;
    initPosition(enemy, x, y);
  }

  {
    sf::Sprite& sprite = m_registry.sprites[block].sprite;
    float x = (windowWidth - sprite.getLocalBounds().width) / 2.f;
    float y = (windowHeight - sprite.getLocalBounds().height) / 2.f;
    initPosition(block, x, y);

  }

  initVelocity(player);
  initVelocity(enemy);
  initVelocity(block);

}

void EntityManager::initSprite(entity_t entity, std::string texturePath)
{
  sf::Texture texture;

  if (!texture.loadFromFile(texturePath))
  {
    std::cout << "Failed to load texture from " << texturePath << std::endl;
    return;
  }

  m_textures.push_back(std::move(texture));

  sf::Sprite sprite;
  sprite.setTexture(m_textures.back());

  m_registry.sprites[entity] = {sprite};
}

void EntityManager::initPosition(entity_t entity, float x, float y)
{
  m_registry.positions[entity] = {x, y};
  auto it = m_registry.sprites.find(entity);
  if(it != m_registry.sprites.end())
  {
    it->second.sprite.setPosition(x, y);
  }
}

void EntityManager::initVelocity(entity_t entity)
{
  m_registry.velocities[entity] = {.0f, 0.0f};
}

sf::Sprite& EntityManager::getSprite(entity_t entity)
{
  return m_registry.sprites[entity].sprite;
}
