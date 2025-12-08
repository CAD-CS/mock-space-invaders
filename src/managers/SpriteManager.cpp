#include "SpriteManager.hpp"

sf::Sprite& SpriteManager::createSprite(entity_t entity, sf::Texture texture)
{

    sf::Sprite sprite(texture);
    m_sprites.try_emplace(entity, sprite);  
    return m_sprites.at(entity);
}

std::unordered_map<entity_t, sf::Sprite>& SpriteManager::getSprites() { return m_sprites; }

sf::Sprite& SpriteManager::getSprite(entity_t entity)
{
    assert(m_sprites.contains(entity) && "Entity does not have a sprite component.");
    return m_sprites.at(entity);
}

