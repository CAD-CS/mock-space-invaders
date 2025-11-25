#include "SystemManager.hpp"
#include "../systems/passive/Passive.hpp"
#include "../systems/active/Active.hpp"

SystemManager::SystemManager(EntityManager& entityManager, registry& registry): m_entityManager(entityManager), m_registry(registry)
{}

void SystemManager::applyPassiveSystems(sf::Vector2u windowSize, sf::Clock& clock, int& score)
{
    Passive::Physics::apply(m_entityManager, m_registry);
    Passive::Collision::apply(m_entityManager, m_registry);
    Passive::OutOfBounds::apply(m_entityManager, m_registry, windowSize);
    Passive::EnemyMovement::apply(m_entityManager, m_registry);
    Passive::EnemyFiring::apply(m_entityManager, m_registry, windowSize, clock);
    Passive::Scoring::apply(m_entityManager, m_registry, score);
}

void SystemManager::applyActiveSystems(sf::Vector2u windowSize, const sf::Event::KeyPressed* key)
{
    Active::Movement::apply(m_entityManager, key, windowSize);
    Active::Firing::apply(m_entityManager, m_registry, key, windowSize);
}
