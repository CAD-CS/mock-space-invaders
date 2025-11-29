#include "Util.hpp"

bool Util::isWithinWindow(const sf::Sprite& sprite, const sf::Vector2u& windowSize, sf::Keyboard::Key direction)
{
    switch (direction)
    {
    case sf::Keyboard::Key::Left:
        if ((sprite.getPosition().x - Util::PLAYER_MOVEMENT_SPEED) < 0)
        {
            return false;
        }
        break;
    case sf::Keyboard::Key::Right:
        if ((sprite.getPosition().x + sprite.getTexture().getSize().x + Util::PLAYER_MOVEMENT_SPEED)> windowSize.x)
        {
            return false;
        }
    }

    return true;
}

bool Util::isColliding(const sf::Sprite& spriteA, const sf::Sprite& spriteB)
{
    sf::FloatRect boundsA = spriteA.getGlobalBounds();
    sf::FloatRect boundsB = spriteB.getGlobalBounds();

    bool collisionX = (boundsA.position.x < boundsB.position.x + boundsB.size.x) && (boundsA.position.x + boundsA.size.x > boundsB.position.x);

    bool collisionY = (boundsA.position.y < boundsB.position.y + boundsB.size.y) && (boundsA.position.y + boundsA.size.y > boundsB.position.y);

    return collisionX && collisionY;
}


bool Util::isOutOfBounds(const sf::Sprite& sprite, const sf::Vector2u& windowSize)
{
    sf::FloatRect bounds = sprite.getGlobalBounds();

    if (bounds.position.y + bounds.size.y < 0 || bounds.position.y > windowSize.y)
    {
        return true;
    }

    return false;
} 
