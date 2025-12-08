#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "../managers/EntityManager.hpp"
#include "../model/Registry.hpp"
#include "Initializer.hpp"
#include "SystemService.hpp"
#include "GameService.hpp"

class Game 
{
private:
    int m_score;
    bool m_isGameOver;
    bool m_isPaused;

    sf::RenderWindow m_window;
    sf::Clock m_clock;

    GameService m_gameService;
    SystemService m_systemService;
    Initializer m_initializer;

    void process();
    void passiveUpdates();
    void activeUpdates(const sf::Event::KeyPressed* key);
    void activeUpdates(const sf::Event::MouseButtonPressed* click);
    void render();

public:
    Game(int windowWidth, int windowHeight, const std::string& title);
    void run();
};