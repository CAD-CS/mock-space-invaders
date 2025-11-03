#include "System.hpp"

void System::MovementSystem::apply(registry& reg, const sf::Event::KeyPressed* key, sf::Vector2u windowSize) 
{
    sf::Sprite& playerSprite = reg.sprites.at(1);

    switch (key->code) {
    case sf::Keyboard::Key::Left:
        if (!isWithinWindow(playerSprite, windowSize, sf::Keyboard::Key::Left))
        {
            playerSprite.setPosition({0.f, playerSprite.getPosition().y});
            return;
        }
        playerSprite.move({-MOVEMENT_SPEED, 0.f});
        return;
    case sf::Keyboard::Key::Right:
        if(!isWithinWindow(playerSprite, windowSize, sf::Keyboard::Key::Right))
        {
            playerSprite.setPosition({static_cast<float>(windowSize.x - playerSprite.getTexture().getSize().x), playerSprite.getPosition().y});
            return;
        }
        playerSprite.move({MOVEMENT_SPEED, 0.f});
        return;
    default:
        std::cout << "Unhandled key in MovementSystem\n";
        break;
    }
}

bool System::MovementSystem::isWithinWindow(const sf::Sprite& sprite, const sf::Vector2u& windowSize, sf::Keyboard::Key direction)
{
    switch (direction)
    {
    case sf::Keyboard::Key::Left:
        if ((sprite.getPosition().x - MOVEMENT_SPEED) < 0)
        {
            return false;
        }
        break;
    case sf::Keyboard::Key::Right:
        if ((sprite.getPosition().x + sprite.getTexture().getSize().x + MOVEMENT_SPEED)> windowSize.x)
        {
            return false;
        }
    }

    return true;
}

void System::PhysicsSystem::apply(registry& reg)
{

  for(auto& [entity, sprite] : reg.sprites)
  {
    if(reg.velocities.contains(entity))
    {
      auto& velComp = reg.velocities.at(entity);
      sprite.move({velComp.xVel, velComp.yVel});
    }
  }
}

void System::FiringSystem::apply(registry& reg, const sf::Event::KeyPressed* key, sf::Vector2u windowSize, EntityManager& entityManager) 
{
    switch (key->code) {
    case sf::Keyboard::Key::Up:
        std::cout << "Fire projectile!\n";
        return;
    default:
        std::cout << "Unhandled key in FiringSystem\n";
        break;
    }
}

