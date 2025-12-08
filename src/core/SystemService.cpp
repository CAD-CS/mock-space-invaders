#include "SystemService.hpp"
#include "../systems/passive/Passive.hpp"
#include "../systems/active/Active.hpp"
#include <iostream>

SystemService::SystemService(GameService& gameService, int& score, bool& isGameOver, bool& isPaused, sf::Clock& clock, sf::Vector2u windowSize)
: 
m_score(score),
m_isGameOver(isGameOver),
m_isPaused(isPaused),
m_clock(clock),
m_windowSize(windowSize),
m_gameService(gameService)
{}

void SystemService::applyPassiveSystems()
{
    if (m_isPaused)
    {
        return;
    }

    Passive::Physics::apply(m_gameService);
    Passive::Scoring::apply(m_gameService, m_score);
    Passive::Collision::apply(m_gameService);
    Passive::OutOfBounds::apply(m_gameService, m_windowSize);
    Passive::EnemyMovement::apply(m_gameService);
    //Passive::EnemyFiring::apply(m_gameService, m_windowSize, m_clock);
    Passive::GameOverCheck::apply(m_gameService, m_isGameOver);
}

void SystemService::applyActiveSystems(const sf::Event::KeyPressed* key)
{
    Active::Pause::apply(m_windowSize, m_isPaused, key);
    if (m_isPaused)
    {
        return;
    }
    Active::Movement::apply(m_gameService, key, m_windowSize);
    Active::Firing::apply(m_gameService, key, m_windowSize);
}

void SystemService::applyActiveSystems(const sf::Event::MouseButtonPressed* click)
{
    Active::Pause::apply(m_windowSize, m_isPaused, click);
}