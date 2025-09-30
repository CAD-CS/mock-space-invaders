#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "EntityManager.hpp"

const int WINDOW_WIDTH = 700;
const int WINDOW_HEIGHT = 800;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_HEIGHT, WINDOW_HEIGHT), "Mock invaders");

    sf::Texture playerTexture;
    playerTexture.loadFromFile("./assets/player.jpg");

    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);

    auto [xPos, yPos, width, height] = playerSprite.getLocalBounds();
    
    playerSprite.setPosition({ 0.5f * (WINDOW_WIDTH - width) , WINDOW_HEIGHT - height});

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Left)
                    {
                        std::cout << "Pressed!" << std::endl;
                    }
            }
        }
        window.clear(sf::Color::Black);
        window.draw(playerSprite);
        window.display();
    }
    return 0;
}
