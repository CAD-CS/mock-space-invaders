#include "Active.hpp"
#include "../../util/Util.hpp"

void Active::Movement::apply(EntityManager& entityManager, const sf::Event::KeyPressed* key, sf::Vector2u windowSize) 
{
    sf::Sprite& playerSprite = entityManager.getSprite(entityManager.getPlayer());

    switch (key->code) {
    case sf::Keyboard::Key::Left:
        if (!Util::isWithinWindow(playerSprite, windowSize, sf::Keyboard::Key::Left))
        {
            playerSprite.setPosition({0.f, playerSprite.getPosition().y});
            return;
        }
        playerSprite.move({-Util::PLAYER_MOVEMENT_SPEED, 0.f});
        return;
    case sf::Keyboard::Key::Right:
        if(!Util::isWithinWindow(playerSprite, windowSize, sf::Keyboard::Key::Right))
        {
            playerSprite.setPosition({static_cast<float>(windowSize.x - playerSprite.getTexture().getSize().x), playerSprite.getPosition().y});
            return;
        }
        playerSprite.move({Util::PLAYER_MOVEMENT_SPEED, 0.f});
        return;
    }
}

void Active::Firing::apply(EntityManager& entityManager, registry& registry, const sf::Event::KeyPressed* key, sf::Vector2u windowSize) 
{
    switch (key->code) 
    {
    case sf::Keyboard::Key::Up:
        entity_t newProjectile = entityManager.createEntity("PlayerProjectile");

        sf::Sprite& projectileSprite = entityManager.getSprite(newProjectile);

        float x = entityManager.getSprite(entityManager.getPlayer()).getGlobalBounds().size.x / 2.f + entityManager.getSprite(entityManager.getPlayer()).getGlobalBounds().position.x - projectileSprite.getGlobalBounds().size.x / 2.f;

        float y =  entityManager.getSprite(entityManager.getPlayer()).getGlobalBounds().position.y - projectileSprite.getGlobalBounds().size.y - 1.f; 

        projectileSprite.setPosition({x, y});

        registry.projectiles_tag.push_back(newProjectile);
        registry.velocities_map.insert({newProjectile, {0.f, -Util::PROJECTILE_MOVEMENT_SPEED}});

        return;
    }
}

