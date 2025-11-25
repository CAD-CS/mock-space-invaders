#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include "Components.hpp"

constexpr entity_t MAX_ENTITIES = 100;

class EntityManager
{

private:
    entity_t m_entities;
    registry m_registry;
    std::unordered_map<std::string, sf::Texture> m_textures;
    std::unordered_map<entity_t, sf::Sprite> m_sprites;
    int m_Cols;

    void init(int windowWidth, int windowHeight);

    void loadTextures();
    void loadTexture(const std::string& texturePath, const std::string& textureName);

    void createSprite(entity_t entity, std::string textureName);

    void updateEntities();


public:
    EntityManager(int  windowWidth, int windowHeight);
    ~EntityManager();

    entity_t createEntity(std::string textureName);

    std::unordered_map<entity_t, sf::Sprite>& getSprites();
    sf::Sprite& getSprite(entity_t entity);
    entity_t getPlayer();

    void destroyEntity(entity_t entity);

};
