#pragma once

#include <SFML/Graphics.hpp>

namespace Util
{
    bool isWithinWindow(const sf::Sprite& sprite, const sf::Vector2u& windowSize, sf::Keyboard::Key direction);
    bool isColliding(const sf::Sprite& spriteA, const sf::Sprite& spriteB);
    bool isOutOfBounds(const sf::Sprite& sprite, const sf::Vector2u& windowSize);

}