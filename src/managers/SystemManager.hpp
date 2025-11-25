# pragma once

#include "EntityManager.hpp"
#include "../model/Registry.hpp"
#include "../model/Components.hpp"

class SystemManager
{
private:
    EntityManager& m_entityManager;
    registry& m_registry;

public:
    SystemManager(EntityManager& entityManager, registry& registry); 
    ~SystemManager() = default;

    void applyPassiveSystems(sf::Vector2u windowSize, sf::Clock& clock, int& score);
    void applyActiveSystems(sf::Vector2u windowSize, const sf::Event::KeyPressed* key);

};