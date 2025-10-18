#include "Game.hpp"
#include "PhysicsSystem.hpp"
#include "MovementSystem.hpp"

Game::Game(int windowWidth, int windowHeight, const std::string& title)
  : m_window(sf::VideoMode(windowWidth, windowHeight), title), m_entityManager()
{
  m_entityManager.init(windowWidth, windowHeight);
}

void Game::process()
{
    // Update game state regardless of events
    update();
    
    // Handle window events
    while (m_window.pollEvent(m_event))
    {
        if (m_event.type == sf::Event::Closed)
        {
            m_window.close();
        }
        // Handle keyboard input events
        if (m_event.type == sf::Event::KeyPressed)
        {
            MovementSystem::apply(m_entityManager.getRegistry(), m_event);
        }
    }
}

void Game::update()
{
    PhysicsSystem::apply(m_entityManager.getRegistry());
}

void Game::render()
{  
  m_window.clear(sf::Color::Black);

  auto& sprites = m_entityManager.getRegistry().sprites;

  for (const auto& [entity, spriteComponent] : sprites)
  {
    m_window.draw(spriteComponent.sprite);
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
