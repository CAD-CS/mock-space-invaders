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
    bool& m_isPaused;

public:
    SystemManager(EntityManager& entityManager, registry& registry, int& score, bool& isGameOver, bool& isPaused); 
    ~SystemManager() = default;

    void applyPassiveSystems(sf::Vector2u windowSize, sf::Clock& clock, int& score, bool& isGameOver);
    void applyActiveSystems(sf::Vector2u windowSize, bool& isPaused, const sf::Event::KeyPressed* key);
    void applyActiveSystems(sf::Vector2u windowSize, bool& isPaused, const sf::Event::MouseButtonPressed* click);

};