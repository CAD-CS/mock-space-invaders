#include "Game.hpp"
#include "System.hpp"

Game::Game(int windowWidth, int windowHeight, const std::string& title)
  : m_window(sf::VideoMode({static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight)}), title), m_entityManager()
{
  m_entityManager.init(windowWidth, windowHeight);
}

void Game::process()
{
  update();
  
  while (const auto m_event = m_window.pollEvent())
  {
    if (m_event->is<sf::Event::Closed>())
    {
      m_window.close();
    } else if (const auto* key = m_event->getIf<sf::Event::KeyPressed>())
    {
        System::MovementSystem::apply(m_entityManager.getRegistry(), key, m_window.getSize());
      System::FiringSystem::apply(m_entityManager.getRegistry(), key, m_window.getSize(), m_entityManager);
    }
  }
}

void Game::update()
{
    System::PhysicsSystem::apply(m_entityManager.getRegistry());
}

void Game::render()
{  
  m_window.clear(sf::Color::Black);

  auto& sprites = m_entityManager.getRegistry().sprites;

  for (const auto& [entity, sprite] : sprites)
  {
    m_window.draw(sprite);
  }
  
  m_window.display();
}

void Game::run()
{
  m_window.setKeyRepeatEnabled(true);

  while (m_window.isOpen())
  {
    process();
    render();
  }
}
