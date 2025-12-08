#include "Active.hpp"
#include "../../util/Util.hpp"
#include <iostream>

void Active::Movement::apply(GameService& gameService, const sf::Event::KeyPressed* key, sf::Vector2u windowSize) 
{
    sf::Sprite& playerSprite = gameService.getSprite(gameService.getPlayer());

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

void Active::Firing::apply(GameService& gameService, registry& registry, const sf::Event::KeyPressed* key, sf::Vector2u windowSize) 
{
    switch (key->code) 
    {
    case sf::Keyboard::Key::Up:
        entity_t newProjectile = gameService.createSprite("PlayerProjectile");

        sf::Sprite& projectileSprite = gameService.getSprite(newProjectile);

        float x = gameService.getSprite(gameService.getPlayer()).getGlobalBounds().size.x / 2.f + gameService.getSprite(gameService.getPlayer()).getGlobalBounds().position.x - projectileSprite.getGlobalBounds().size.x / 2.f;

        float y =  gameService.getSprite(gameService.getPlayer()).getGlobalBounds().position.y - projectileSprite.getGlobalBounds().size.y - 1.f; 

        projectileSprite.setPosition({x, y});

        registry.projectiles_tag.push_back(newProjectile);
        registry.hittables_tag.push_back(newProjectile);
        registry.velocities_map.insert({newProjectile, {0.f, -Util::PROJECTILE_MOVEMENT_SPEED}});

        return;
    }
}


void Active::Pause::apply(sf::Vector2u windowSize, bool& isPaused, const sf::Event::KeyPressed* key)
{
    if (key->code == sf::Keyboard::Key::P)
    {
        isPaused = !isPaused;
    }
}
void Active::Pause::apply(sf::Vector2u windowSize, bool& isPaused, const sf::Event::MouseButtonPressed* click)
{
    auto isClickInsideButton = [windowSize, click]() {
        int xClick = click->position.x;
        int yClick = click->position.y;
        bool isInY = yClick >= 10 && yClick <= 10 + 60;
        bool isInX = xClick >= static_cast<int>(windowSize.x) - 100 - 10;
        if (isInX && isInY)
        {
            return true;
        }
        return false;
    };

    if (isClickInsideButton())
    {
        isPaused = !isPaused;
    }
}