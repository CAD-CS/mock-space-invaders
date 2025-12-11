#include "GameService.hpp"
#include <iostream>

GameService::GameService()
:
m_entityManager(),
m_spriteManager(),
m_textManager(),
m_textureManager(),
m_registry()
{}

entity_t GameService::createSprite(std::string textureName, sf::Vector2f position)
{
    assert(m_textureManager.getTextures().contains(textureName) && "Texture not found in texture map.");
    entity_t newEntity = m_entityManager.createEntity();
    m_registry.entityNames_map[newEntity] = textureName;
    sf::Sprite& newSprite = m_spriteManager.createSprite(newEntity, m_textureManager.getTexture(textureName));
    newSprite.setPosition(position);
    m_registry.rendable_tag.push_back(newEntity);
    return newEntity;
}

void GameService::createText(std::string initialText, std::string textKey, sf::Vector2f position)
{
   sf::Text& newText = m_textManager.createText(initialText, textKey, position); 
   std::cout << m_textManager.getTexts().size() << std::endl;
   std::cout << newText.getString().toAnsiString() << std::endl;
}

sf::Sprite& GameService::getSprite(entity_t entity)
{
    return m_spriteManager.getSprite(entity);
}

sf::Text& GameService::getText(std::string textLabel)
{
    return m_textManager.getText(textLabel);
}

std::unordered_map<entity_t, sf::Sprite>& GameService::getSprites()
{
    return m_spriteManager.getSprites();
}
std::unordered_map<std::string, sf::Text>& GameService::getTexts()
{
    return m_textManager.getTexts();
}

registry& GameService::getRegistry()
{
    return m_registry;
}

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

void deleteFromLowestEnemiesMappping(std::unordered_map<int, entity_t>& mapping, entity_t entity)
{
    for (auto it = mapping.begin(); it != mapping.end(); )
    {
        if (it->second == entity)
        {
            it = mapping.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void GameService::updateEntities()
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

    m_registry.lowestEnemies_map = lowestEnemies;
}

entity_t GameService::getPlayer()
{
    return m_entityManager.getPlayer();
}

void GameService::destroyEntity(entity_t entity)
{
    deleteFromMapping(m_spriteManager.getSprites(), entity);
    
    deleteFromMapping(m_registry.entityNames_map, entity);
    deleteFromMapping(m_registry.velocities_map, entity);
    deleteFromMapping(m_registry.enemyPositions_map, entity);
    deleteFromLowestEnemiesMappping(m_registry.lowestEnemies_map, entity);

    deleteFromVector(m_registry.hittables_tag, entity);
    deleteFromVector(m_registry.projectiles_tag, entity);
    deleteFromVector(m_registry.enemies_tag, entity);

    updateEntities();

    //m_entityManager.decreaseEntityCount();
}
