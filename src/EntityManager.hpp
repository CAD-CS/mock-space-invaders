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
    entity_t m_player;
    registry m_registry;
    std::unordered_map<std::string, sf::Texture> m_textures;

    void createSprite(entity_t entity, std::string texturePath, std::string textureName);
    void createSprite(entity_t entity, std::string textureName);

    void init(int windowWidth, int windowHeight);

    void initPosition(entity_t entity, float x, float y);
    void initVelocity(entity_t entity);

public:
    EntityManager(int  windowWidth, int windowHeight);
    ~EntityManager();

    entity_t createEntity(std::string texturePath, std::string textureName);
    entity_t createEntity(std::string textureName);
    registry& getRegistry();
    entity_t getEntities();
    entity_t getPlayer();
    sf::Sprite& getSprite(entity_t entity);
};
