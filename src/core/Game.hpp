#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "../managers/EntityManager.hpp"
#include "../managers/SystemManager.hpp"
#include "../model/Registry.hpp"

class Game 
{
private:
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    int score;

    EntityManager m_entityManager;
    SystemManager m_systemManager;
    registry m_registry;

    void process();
    void passiveUpdates();
    void activeUpdates(const sf::Event::KeyPressed* key);
    void render();

public:
    Game(int windowWidth, int windowHeight, const std::string& title);
    void run();
};