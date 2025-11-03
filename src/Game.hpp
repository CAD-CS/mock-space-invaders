#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "EntityManager.hpp"

class Game 
{
private:
    sf::RenderWindow m_window;

    EntityManager m_entityManager;

    void process();
    void passiveUpdates();
    void activeUpdates(const sf::Event::KeyPressed* key);
    void render();

public:
    Game(int windowWidth, int windowHeight, const std::string& title);
    void run();
};