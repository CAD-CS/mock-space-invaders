#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "../managers/EntityManager.hpp"
#include "../managers/SystemManager.hpp"
#include "../model/Registry.hpp"
#include "Initializer.hpp"

class Game 
{
private:
    int m_score;
    bool m_isGameOver;
    bool m_isPaused;

    sf::RenderWindow m_window;
    sf::Clock m_clock;
    registry m_registry;

    EntityManager m_entityManager;
    SystemManager m_systemManager;
    Initializer m_initializer;

    void process();
    void passiveUpdates();
    void activeUpdates(const sf::Event::KeyPressed* key);
    void render();

public:
    Game(int windowWidth, int windowHeight, const std::string& title);
    void run();
};