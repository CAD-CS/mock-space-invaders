#pragma once

#include <SFML/Graphics.hpp>

namespace Util
{
    static constexpr float PROJECTILE_MOVEMENT_SPEED = 2.f;
    static constexpr float ENEMY_MOVEMENT_SPEED = 0.5f;
    static constexpr float PLAYER_MOVEMENT_SPEED = 60.f;
    static bool isWithinWindow(const sf::Sprite& sprite, const sf::Vector2u& windowSize, sf::Keyboard::Key direction);
    static bool isColliding(const sf::Sprite& spriteA, const sf::Sprite& spriteB);
    static bool isOutOfBounds(const sf::Sprite& sprite, const sf::Vector2u& windowSize);

}