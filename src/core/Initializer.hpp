#pragma once

#include "../managers/EntityManager.hpp"
#include "../model/Registry.hpp"

class Initializer
{
private:
    EntityManager& m_entityManager;
    registry& m_registry;
    sf::Font m_font;
    sf::Text m_scoreBoardLabel;
    
    void initializePlayer(int windowWidth, int windowHeight);
    void initializeEnemies();
    void initializeBlocks();
    void initializeEnvironmentEntities(int windowWidth, int windowHeight);
    void initializeScoreBoard();
    void initPosition(entity_t entity, float x, float y);
    void initVelocity(entity_t entity);
public:
    Initializer(EntityManager& entityManager, registry& registry, int windowWidth, int windowHeight);
    
};