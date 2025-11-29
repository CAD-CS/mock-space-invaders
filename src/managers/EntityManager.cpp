#include "EntityManager.hpp"
#include "../model/Registry.hpp"
#include "../util/Util.hpp"
#include <cassert>
#include <iostream>
#include <filesystem>

EntityManager::EntityManager(int windowWidth, int windowHeight, registry& registry)
: m_entities(0), m_registry(registry)
{
    m_textures.reserve(MAX_ENTITIES);
    init(windowWidth, windowHeight);
}

EntityManager::~EntityManager() 
{
    m_textures.clear();
    m_sprites.clear();
}

void EntityManager::init(int windowWidth, int windowHeight)
{
    loadTextures();
    updateEntities();
}

void EntityManager::loadTextures()
{
    loadTexture("./assets/player.jpg", "Player");
    loadTexture("./assets/enemy.jpg", "Enemy");
    loadTexture("./assets/block.jpg", "Block");
    loadTexture("./assets/player_projectile.jpg", "PlayerProjectile");
    loadTexture("./assets/enemy_projectile.jpg", "EnemyProjectile");
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

void EntityManager::createSprite(entity_t entity, std::string textureName)
{
    assert(m_textures.contains(textureName) && "Texture not found in texture map.");

    m_sprites.try_emplace(entity, m_textures.at(textureName));
}

void EntityManager::updateEntities()
{
    std::unordered_map<int, entity_t> lowestEnemies;
    for (int col = 0; col < Util::COLUMNS; ++col)
    {
        for (const auto& enemy : m_registry.enemies_tag)
        {
            if (m_registry.enemyPositions_map[enemy].col == col)
            {
                if (!lowestEnemies.contains(col))
                {
                    lowestEnemies[col] = enemy;
                }
                if (m_registry.enemyPositions_map[enemy].row > m_registry.enemyPositions_map[lowestEnemies[col]].row)
                {
                    lowestEnemies[col] = enemy;
                }    
            }
        }
    }
    for (const auto& [col, enemy] : lowestEnemies)
    {
        std::cout << "Lowest enemy in column " << col << " is entity " << enemy << " at row " << m_registry.enemyPositions_map[enemy].row << std::endl;
    }
    m_registry.lowestEnemies_map = lowestEnemies;
}

entity_t EntityManager::createEntity(std::string textureName)
{
    assert(m_entities < MAX_ENTITIES && "Too many entities in existence.");

    entity_t newEntity = ++m_entities;

    createSprite(newEntity, textureName);
    m_registry.entityNames_map.insert({newEntity, textureName });
    
    return newEntity;
}

std::unordered_map<entity_t, sf::Sprite>& EntityManager::getSprites() { return m_sprites; }

sf::Sprite& EntityManager::getSprite(entity_t entity)
{
    if (!m_sprites.contains(entity)) 
    {
        // Print all sprites with their names for debugging
        std::cout << "Current sprites in EntityManager:" << std::endl;
        for (const auto& [ent, sprite] : m_sprites) {
            std::cout << "Entity ID: " << ent << ", Name: " << m_registry.entityNames_map[ent] << std::endl;
        }
        std::cout << "Attempted to access sprite for non-existent entity: " << entity << " --> " << m_registry.entityNames_map[entity] << std::endl;
        std::cerr << "Error: Attempted to access sprite for non-existent entity " << entity << std::endl;
    }
    assert(m_sprites.contains(entity) && "Entity does not have a sprite component.");
    return m_sprites.at(entity);
}

entity_t EntityManager::getPlayer() { return 1; }

template<typename T>
void deleteFromMapping(std::unordered_map<entity_t, T>& mapping, entity_t entity)
{
    if (mapping.contains(entity))
    {
        mapping.erase(entity);
    }
}

void deleteFromVector(std::vector<entity_t>& vec, entity_t entity)
{
    auto position = std::find(vec.begin(), vec.end(), entity);
    if (position != vec.end())
    {
        vec.erase(position);
    }
}

void EntityManager::destroyEntity(entity_t entity)
{
    std::cout << "Destroying entity: " << entity << " Name: " << m_registry.entityNames_map[entity] << std::endl;

    std::cout << "Sizes of mappings and tags before deletion:" << std::endl;
    std::cout << "Sprites map size: " << m_sprites.size() << std::endl;
    std::cout << "Velocities map size: " << m_registry.velocities_map.size() << std::endl;
    std::cout << "Enemy Positions map size: " << m_registry.enemyPositions_map.size() << std::endl;
    std::cout << "Entity Names map size: " << m_registry.entityNames_map.size() << std::endl;
    std::cout << "Hittables tag size: " << m_registry.hittables_tag.size() << std::endl;
    std::cout << "Projectiles tag size: " << m_registry.projectiles_tag.size() << std::endl;
    std::cout << "Enemies tag size: " << m_registry.enemies_tag.size() << std::endl;

    deleteFromMapping(m_sprites, entity);
    deleteFromMapping(m_registry.velocities_map, entity);
    deleteFromMapping(m_registry.enemyPositions_map, entity);
    deleteFromMapping(m_registry.entityNames_map, entity);

    deleteFromVector(m_registry.hittables_tag, entity);
    deleteFromVector(m_registry.projectiles_tag, entity);
    deleteFromVector(m_registry.enemies_tag, entity);

    updateEntities();
}
