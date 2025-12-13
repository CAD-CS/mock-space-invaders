#pragma once

#include <SFML/Graphics.hpp>
#include "../model/Components.hpp"

class SpriteManager
{
private:
    std::unordered_map<entity_t, sf::Sprite> m_sprites;

public:
    SpriteManager() = default;
    ~SpriteManager() = default;

    sf::Sprite& createSprite(entity_t entity, sf::Texture& texture);

    sf::Sprite& getSprite(entity_t entity);
    std::unordered_map<entity_t, sf::Sprite>& getSprites();
};