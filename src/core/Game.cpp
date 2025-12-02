#include "Game.hpp"
#include <iostream>

Game::Game(int windowWidth, int windowHeight, const std::string& title)
: 
m_score(0),
m_isGameOver(false),
m_isPaused(false),
m_window(sf::VideoMode({static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight)}), title), 
m_clock(),
m_registry(),
m_entityManager(windowWidth, windowHeight, m_registry),
m_systemManager(m_entityManager, m_registry, m_score, m_isGameOver, m_isPaused),
m_initializer(m_entityManager, m_registry, windowWidth, windowHeight)
{}

void Game::run()
{
    m_window.setKeyRepeatEnabled(true);
    m_window.setFramerateLimit(60);

    while (m_window.isOpen() && !m_isGameOver)
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
        } 
        else if (const auto* key = m_event->getIf<sf::Event::KeyPressed>())
        {
            activeUpdates(key);
        }
        else if (const auto* click = m_event->getIf<sf::Event::MouseButtonPressed>())
        {
            activeUpdates(click);
        }
    }
}

void Game::passiveUpdates()
{
    m_systemManager.applyPassiveSystems(m_window.getSize(), m_clock, m_score, m_isGameOver);
}

void Game::activeUpdates(const sf::Event::KeyPressed* key)
{
    m_systemManager.applyActiveSystems(m_window.getSize(), m_isPaused, key);
}

void Game::activeUpdates(const sf::Event::MouseButtonPressed* click)
{
    m_systemManager.applyActiveSystems(m_window.getSize(), m_isPaused, click);
}

void Game::render()
{  
    m_window.clear(sf::Color::Black);

    auto& sprites = m_entityManager.getSprites();

    for (const auto& [entity, sprite] : sprites)
    {
        if (m_registry.entityNames_map[entity] == "Pause" && m_isPaused)
        {
            continue;
        }
        m_window.draw(sprite);
    }

    for (const auto& [entity, text] : m_registry.texts_map)
    {
        m_window.draw(text);
    }

    m_window.display();
}
