# pragma once

#include "EntityManager.hpp"
#include "../model/Registry.hpp"
#include "../model/Components.hpp"

class SystemManager
{
private:
    EntityManager& m_entityManager;
    registry& m_registry;
    int& m_score;
    bool& m_isGameOver;

public:
    SystemManager(EntityManager& entityManager, registry& registry, int& score, bool& isGameOver); 
    ~SystemManager() = default;

    void applyPassiveSystems(sf::Vector2u windowSize, sf::Clock& clock, int& score, bool& isGameOver);
    void applyActiveSystems(sf::Vector2u windowSize, const sf::Event::KeyPressed* key);

};