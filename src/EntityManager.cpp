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
    m_registry.entityNames_map.insert({newEntity, textureName });
    
    return newEntity;
}

void EntityManager::createSprite(entity_t entity, std::string textureName)
{
    assert(m_textures.contains(textureName) && "Texture not found in texture map.");

    m_sprites.try_emplace(entity, m_textures.at(textureName));
}

void EntityManager::destroyEntity(entity_t entity)
{
    std::cout << "Destroying entity: " << entity << " Name: " << m_registry.entityNames_map[entity] << std::endl;
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
        std::cout << "Removing entity: " << m_registry.entityNames_map[entity] << " from hittables_tag" << std::endl;
        m_registry.hittables_tag.erase(position);
    }

    position = std::find(m_registry.projectiles_tag.begin(), m_registry.projectiles_tag.end(), entity);
    if (position != m_registry.projectiles_tag.end())
    {
        std::cout << "Removing entity: " << m_registry.entityNames_map[entity] << " from projectiles tag" << std::endl;
        m_registry.projectiles_tag.erase(position);
    }

    position = std::find(m_registry.enemies_tag.begin(), m_registry.enemies_tag.end(), entity);
    if (position != m_registry.enemies_tag.end())
    {
        std::cout << "Removing entity: " << m_registry.entityNames_map[entity] << " from enemy tag" << std::endl;
        m_registry.enemies_tag.erase(position);
    }

    updateEntities();
}

registry& EntityManager::getRegistry() { return m_registry;}


entity_t EntityManager::getPlayer() { return m_player; }

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

void EntityManager::init(int windowWidth, int windowHeight)
{
    loadTexture("assets/player.jpg", "Player");
    loadTexture("assets/enemy.jpg", "Enemy");
    loadTexture("assets/block.jpg", "Block");
    loadTexture("assets/projectile.jpg", "Projectile");

    entity_t player = createEntity("Player");
    m_player = player;
    
    {
        sf::Sprite& sprite = getSprite(player);
        float x = (windowWidth - sprite.getLocalBounds().size.x) / 2.f;
        float y = windowHeight - sprite.getLocalBounds().size.y;
        initPosition(player, x, y);
        m_registry.hittables_tag.push_back(player);
    }

    spawnEnemies();

    spawnBlocks();

    initVelocity(player);

    updateEntities();
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

std::unordered_map<entity_t, sf::Sprite>& EntityManager::getSprites() { return m_sprites; }


void EntityManager::spawnEnemies()
{
    const int rows = 2;
    const int cols = 2;
    const float spacingX = 20.f;
    const float spacingY = 20.f;
    const float startX = 50.f;
    const float startY = 50.f;

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            entity_t enemy = createEntity("Enemy");
            sf::Sprite& sprite = getSprite(enemy);
            float x = startX + col * (sprite.getLocalBounds().size.x + spacingX);
            float y = startY + row * (sprite.getLocalBounds().size.y + spacingY);
            initPosition(enemy, x, y);
            initVelocity(enemy);
            m_registry.enemies_tag.push_back(enemy);
            m_registry.hittables_tag.push_back(enemy);
            m_registry.enemyPositions_map.insert({enemy, {row, col}});
        }
    }
    m_Cols = cols;
}

void EntityManager::spawnBlocks()
{
    const int numBlocks = 3;
    const float spacing = 200.f;

    for (int i = 0; i < numBlocks; ++i)
    {
        entity_t block = createEntity("Block");
        sf::Sprite& sprite = getSprite(block);
        float x = spacing + i * (sprite.getLocalBounds().size.x + spacing);
        float y = 400.f;
        initPosition(block, x, y);
        initVelocity(block);
        m_registry.hittables_tag.push_back(block);
    }

}

void EntityManager::updateEntities()
{
    // Find lowest enemy in each column
    std::unordered_map<int, entity_t> lowestEnemies;
    for (int col = 0; col < m_Cols; ++col)
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
    m_registry.lowestEnemies_map = lowestEnemies;
}