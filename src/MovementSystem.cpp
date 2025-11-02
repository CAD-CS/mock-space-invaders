#include <SFML/Window.hpp>
#include <iostream>
#include "MovementSystem.hpp"
#include "EntityManager.hpp"


void MovementSystem::apply(registry& reg, const sf::Event::KeyPressed* key, sf::Vector2u windowSize) 
{
    sf::Sprite& playerSprite = reg.sprites.at(1);

    switch (key->code) {
    case sf::Keyboard::Key::Left:
        playerSprite.move({-MOVEMENT_SPEED, 0.f});
        break;
    case sf::Keyboard::Key::Right:
        playerSprite.move({MOVEMENT_SPEED, 0.f});
        break;
    default:
        break;
    }
}

bool isWithinWindow(const sf::Sprite& sprite, const sf::Vector2u& windowSize)
{
    return true;
}