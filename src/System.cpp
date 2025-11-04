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
        playerSprite.move({-PLAYER_MOVEMENT_SPEED, 0.f});
        return;
    case sf::Keyboard::Key::Right:
        if(!isWithinWindow(playerSprite, windowSize, sf::Keyboard::Key::Right))
        {
            playerSprite.setPosition({static_cast<float>(windowSize.x - playerSprite.getTexture().getSize().x), playerSprite.getPosition().y});
            return;
        }
        playerSprite.move({PLAYER_MOVEMENT_SPEED, 0.f});
        return;
    }
}

bool System::MovementSystem::isWithinWindow(const sf::Sprite& sprite, const sf::Vector2u& windowSize, sf::Keyboard::Key direction)
{
    switch (direction)
    {
    case sf::Keyboard::Key::Left:
        if ((sprite.getPosition().x - PLAYER_MOVEMENT_SPEED) < 0)
        {
            return false;
        }
        break;
    case sf::Keyboard::Key::Right:
        if ((sprite.getPosition().x + sprite.getTexture().getSize().x + PLAYER_MOVEMENT_SPEED)> windowSize.x)
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
    switch (key->code) 
    {
    case sf::Keyboard::Key::Up:
        entity_t newProjectile = entityManager.createEntity("Projectile");

        sf::Sprite projectileSprite = entityManager.getSprite(newProjectile);

        float x = entityManager.getSprite(1).getTexture().getSize().x / 2.f + entityManager.getSprite(1).getPosition().x - projectileSprite.getTexture().getSize().x / 2.f;
        float y = windowSize.y - 115.f;


        reg.sprites.insert({newProjectile, projectileSprite});
        reg.projectiles.insert({newProjectile, projectileSprite});
        reg.velocities.insert({newProjectile, {0.f, -PROJECTILE_MOVEMENT_SPEED}});
        reg.sprites.at(newProjectile).setPosition({x, y});

        std::cout << "Projectile address: " << &projectileSprite << "\n";
        std::cout << "Projectile Position: (" << projectileSprite.getPosition().x << ", " << projectileSprite.getPosition().y << ")\n";
        std::cout << "Projectile Texture Address: " << &projectileSprite.getTexture() << "\n";
        std::cout << "Sprite address: " << &reg.sprites.at(newProjectile) << "\n";
        std::cout << "Sprite Position: (" << reg.sprites.at(newProjectile).getPosition().x << ", " << reg.sprites.at(newProjectile).getPosition().y << ")\n";
        std::cout << "Sprite Texture Address: " << &reg.sprites.at(newProjectile).getTexture() << "\n";

        return;
    }
}

