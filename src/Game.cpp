#include "Game.hpp"

Game::Game(int windowWidth, int windowHeight, const std::string& title)
  : m_window(sf::VideoMode(windowWidth, windowHeight), title), m_entityManager()
{
  m_entityManager.init(windowWidth, windowHeight);
}

void Game::process()
{
  while (m_window.pollEvent(m_event))
  {
    if (m_event.type == sf::Event::Closed)
    {
      m_window.close();
    }
  }
}

void Game::update()
{
  // Run systems here
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
  while (m_window.isOpen())
  {
    process();
    update();
    render();
  }
}
