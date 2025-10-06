#include "EntityManager.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Game 
{
private:
  sf::RenderWindow m_window;
  sf::Event m_event;

  EntityManager m_entityManager;

  void process();
  void update();
  void render();

public:
  Game(int windowWidth, int windowHeight, const std::string& title);
  void run();
};