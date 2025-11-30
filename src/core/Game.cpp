#include "Game.hpp"
#include <iostream>

Game::Game(int windowWidth, int windowHeight, const std::string& title)
: 
m_window(sf::VideoMode({static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight)}), title), 
m_clock(),
m_registry(),
m_score(0),
m_isGameOver(false),
m_entityManager(windowWidth, windowHeight, m_registry),
m_systemManager(m_entityManager, m_registry, m_score, m_isGameOver),
m_initializer(m_entityManager, m_registry, windowWidth, windowHeight)
{}

void Game::run()
{
    m_window.setKeyRepeatEnabled(true);
    m_window.setFramerateLimit(60);

    while (m_window.isOpen())
    {
        process();
        render();
    }
}

void Game::process()
{
    passiveUpdates();

    while (const auto m_event = m_window.pollEvent())
    {
        if (m_event->is<sf::Event::Closed>())
        {
            m_window.close();
        } else if (const auto* key = m_event->getIf<sf::Event::KeyPressed>())
        {
            activeUpdates(key);
        }
    }
}

void Game::passiveUpdates()
{
    m_systemManager.applyPassiveSystems(m_window.getSize(), m_clock, m_score, m_isGameOver);
}

void Game::activeUpdates(const sf::Event::KeyPressed* key)
{
    m_systemManager.applyActiveSystems(m_window.getSize(), key);
}

void Game::render()
{  
    m_window.clear(sf::Color::Black);

    auto& sprites = m_entityManager.getSprites();

    for (const auto& [entity, sprite] : sprites)
    {
        m_window.draw(sprite);
    }

    m_window.display();
}
