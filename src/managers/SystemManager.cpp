#include "SystemManager.hpp"
#include "../systems/passive/Passive.hpp"
#include "../systems/active/Active.hpp"
#include <iostream>

SystemManager::SystemManager(EntityManager& entityManager, registry& registry, int& score, bool& isGameOver, bool& isPaused)
: 
m_entityManager(entityManager),
m_registry(registry),
m_score(score),
m_isGameOver(isGameOver),
m_isPaused(isPaused)
{}

void SystemManager::applyPassiveSystems(sf::Vector2u windowSize, sf::Clock& clock, int& score, bool& isGameOver)
{
    if (m_isPaused)
    {
        return;
    }

    Passive::Physics::apply(m_entityManager, m_registry);
    Passive::Scoring::apply(m_entityManager, m_registry, score);
    Passive::Collision::apply(m_entityManager, m_registry);
    Passive::OutOfBounds::apply(m_entityManager, m_registry, windowSize);
    Passive::EnemyMovement::apply(m_entityManager, m_registry);
    //Passive::EnemyFiring::apply(m_entityManager, m_registry, windowSize, clock);
    Passive::GameOverCheck::apply(m_entityManager, m_registry, isGameOver);
}

void SystemManager::applyActiveSystems(sf::Vector2u windowSize, bool& isPaused, const sf::Event::KeyPressed* key)
{
    Active::Pause::apply(windowSize, isPaused, key);
    if (isPaused)
    {
        return;
    }
    Active::Movement::apply(m_entityManager, key, windowSize);
    Active::Firing::apply(m_entityManager, m_registry, key, windowSize);
}

void SystemManager::applyActiveSystems(sf::Vector2u windowSize, bool& isPaused, const sf::Event::MouseButtonPressed* click)
{
    Active::Pause::apply(windowSize, isPaused, click);
}