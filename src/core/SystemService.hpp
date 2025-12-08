# pragma once

#include "EntityManager.hpp"
#include "../model/Registry.hpp"
#include "../model/Components.hpp"
#include "GameService.hpp"

class SystemService
{
private:
    int& m_score;
    bool& m_isGameOver;
    bool& m_isPaused;
    sf::Clock& m_clock;
    sf::Vector2u m_windowSize;
    GameService& m_gameService;

public:
    SystemService(GameService& gameService, int& score, bool& isGameOver, bool& isPaused, sf::Clock& clock, sf::Vector2u windowSize); 
    ~SystemService() = default;

    void applyPassiveSystems();
    void applyActiveSystems(const sf::Event::KeyPressed* key);
    void applyActiveSystems(const sf::Event::MouseButtonPressed* click);

};