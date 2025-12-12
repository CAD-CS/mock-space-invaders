#pragma once

#include <SFML/Graphics.hpp>

namespace Util
{
    static constexpr float PROJECTILE_MOVEMENT_SPEED = 5.f;
    static constexpr float ENEMY_MOVEMENT_SPEED = 40.f;
    static constexpr float PLAYER_MOVEMENT_SPEED = 60.f;
    static constexpr int COLUMNS = 20;
    bool isWithinWindow(const sf::Sprite& sprite, const sf::Vector2u& windowSize, sf::Keyboard::Key direction);
    bool isColliding(const sf::Sprite& spriteA, const sf::Sprite& spriteB);
    bool isOutOfBounds(const sf::Sprite& sprite, const sf::Vector2u& windowSize);

}