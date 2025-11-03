#include "EntityManager.hpp"
#include <cassert>
#include <iostream>

EntityManager::EntityManager(int windowWidth, int windowHeight) : m_entities(0) {
    m_textures.reserve(MAX_ENTITIES);
    init(windowWidth, windowHeight);
}

EntityManager::~EntityManager() {
    m_textures.clear();
}

entity_t EntityManager::createEntity(std::string texturePath)
{
    assert(m_entities < MAX_ENTITIES && "Too many entities in existence.");

    entity_t newEntity = ++m_entities;

    createSprite(newEntity, texturePath);
    
    return newEntity;
}

registry& EntityManager::getRegistry() { return m_registry;}

entity_t EntityManager::getEntities() { return m_entities; }

entity_t EntityManager::getPlayer() { return m_player; }

void EntityManager::createSprite(entity_t entity, std::string texturePath)
{
    sf::Texture texture;

    if (!texture.loadFromFile(texturePath))
    {
        std::cout << "Failed to load texture from " << texturePath << std::endl;
        return;
    }

    m_textures.push_back(std::move(texture));

    sf::Sprite sprite(m_textures.back());

    m_registry.sprites.insert({entity, sprite});
}


void EntityManager::init(int windowWidth, int windowHeight)
{
    entity_t player = createEntity("./assets/player.jpg");
    m_player = player;

    entity_t enemy = createEntity("./assets/enemy.jpg");
    entity_t block = createEntity("./assets/block.jpg");
    entity_t shot = createEntity("assets/shot.jpg");
    
    {
        sf::Sprite& sprite = m_registry.sprites.at(player);
        float x = (windowWidth - sprite.getLocalBounds().size.x) / 2.f;
        float y = windowHeight - sprite.getLocalBounds().size.y;
        initPosition(player, x, y);
    }

    {
        sf::Sprite& sprite = m_registry.sprites.at(enemy);
        float x = (windowWidth - sprite.getLocalBounds().size.x) / 2.f;
        float y = 0.f;
        initPosition(enemy, x, y);
    }

    {
        sf::Sprite& sprite = m_registry.sprites.at(block);
        float x = (windowWidth - sprite.getLocalBounds().size.x) / 2.f;
        float y = (windowHeight - sprite.getLocalBounds().size.y) / 2.f;
        initPosition(block, x, y);
    }

    {
        sf::Sprite& sprite = m_registry.sprites.at(shot);
        float x = 20.f;
        float y = 50.f;
        initPosition(shot, x, y);
    }

    initVelocity(player);
    initVelocity(enemy);
    initVelocity(block);
    initVelocity(shot);

}

void EntityManager::initPosition(entity_t entity, float x, float y)
{
    if(m_registry.sprites.contains(entity))
    {
        sf::Sprite& sprite = m_registry.sprites.at(entity);
        sprite.setPosition({x,y});
    }
}

void EntityManager::initVelocity(entity_t entity)
{
    m_registry.velocities.insert({entity, {.0f, 0.0f}});
}
