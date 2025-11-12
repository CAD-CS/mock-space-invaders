#include "Game.hpp"
#include "System.hpp"

Game::Game(int windowWidth, int windowHeight, const std::string& title)
: m_window(sf::VideoMode({static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight)}), title), m_entityManager(windowWidth, windowHeight)
{}

void Game::run()
{
    m_window.setKeyRepeatEnabled(true);

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
    System::PhysicsSystem::apply(m_entityManager);
    System::CollisionSystem::apply(m_entityManager);
}

void Game::activeUpdates(const sf::Event::KeyPressed* key)
{
    System::MovementSystem::apply(m_entityManager, key, m_window.getSize());
    System::FiringSystem::apply(m_entityManager, key, m_window.getSize());
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
