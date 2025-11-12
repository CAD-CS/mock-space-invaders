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

void EntityManager::loadTexture(const std::string& texturePath, const std::string& textureName)
{
    sf::Texture texture;
    if (!texture.loadFromFile(texturePath))
    {
        throw std::runtime_error("Failed to load texture from path: " + texturePath);
    }
    m_textures.insert({textureName, texture});
}


entity_t EntityManager::createEntity(std::string textureName)
{
    assert(m_entities < MAX_ENTITIES && "Too many entities in existence.");

    entity_t newEntity = ++m_entities;

    createSprite(newEntity, textureName);
    
    return newEntity;
}

void EntityManager::createSprite(entity_t entity, std::string textureName)
{
    assert(m_textures.contains(textureName) && "Texture not found in texture map.");

    m_sprites.try_emplace(entity, m_textures.at(textureName));
}

void EntityManager::destroyEntity(entity_t entity)
{
    if (m_sprites.contains(entity))
    {
        m_sprites.erase(entity);
    }

    if (m_registry.velocities_map.contains(entity))
    {
        m_registry.velocities_map.erase(entity);
    }

    std::vector<entity_t>::iterator position = std::find(m_registry.hittables_tag.begin(), m_registry.hittables_tag.end(), entity);
    if (position != m_registry.hittables_tag.end())
    {
        m_registry.hittables_tag.erase(position);
    }

    position = std::find(m_registry.projectiles_tag.begin(), m_registry.projectiles_tag.end(), entity);
    if (position != m_registry.projectiles_tag.end())
    {
        m_registry.projectiles_tag.erase(position);
    }

    position = std::find(m_registry.hittables_tag.begin(), m_registry.hittables_tag.end(), entity);
    if (position != m_registry.hittables_tag.end())
    {
        m_registry.hittables_tag.erase(position);
    }
}

registry& EntityManager::getRegistry() { return m_registry;}


entity_t EntityManager::getPlayer() { return m_player; }

sf::Sprite& EntityManager::getSprite(entity_t entity)
{
    assert(m_sprites.contains(entity) && "Entity does not have a sprite component.");
    return m_sprites.at(entity);
}

void EntityManager::init(int windowWidth, int windowHeight)
{
    loadTexture("assets/player.jpg", "Player");
    loadTexture("assets/enemy.jpg", "Enemy");
    loadTexture("assets/block.jpg", "Block");
    loadTexture("assets/projectile.jpg", "Projectile");

    entity_t player = createEntity("Player");
    m_player = player;

    entity_t enemy = createEntity("Enemy");
    entity_t block = createEntity("Block");
    
    {
        sf::Sprite& sprite = getSprite(player);
        float x = (windowWidth - sprite.getLocalBounds().size.x) / 2.f;
        float y = windowHeight - sprite.getLocalBounds().size.y;
        initPosition(player, x, y);
        m_registry.hittables_tag.push_back(player);
    }

    {
        sf::Sprite& sprite = getSprite(enemy);
        float x = (windowWidth - sprite.getLocalBounds().size.x) / 2.f;
        float y = 30.f;
        initPosition(enemy, x, y);
        m_registry.enemies_tag.push_back(enemy);
        m_registry.hittables_tag.push_back(enemy);
    }

    {
        sf::Sprite& sprite = getSprite(block);
        float x = (windowWidth - sprite.getLocalBounds().size.x) / 2.f;
        float y = (windowHeight - sprite.getLocalBounds().size.y) / 2.f;
        initPosition(block, x, y);
        m_registry.hittables_tag.push_back(block);
    }

    initVelocity(player);
    initVelocity(enemy);
    initVelocity(block);

}

void EntityManager::initPosition(entity_t entity, float x, float y)
{
    if(m_sprites.contains(entity))
    {
        sf::Sprite& sprite = getSprite(entity);
        sprite.setPosition({x,y});
    }
}

void EntityManager::initVelocity(entity_t entity)
{
    m_registry.velocities_map.insert({entity, {.0f, 0.0f}});
}

entity_t EntityManager::getEntities() { return m_entities; }

std::unordered_map<entity_t, sf::Sprite>& EntityManager::getSprites() { return m_sprites; }