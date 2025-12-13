#include "Passive.hpp"
#include "../../util/Util.hpp"
#include "../../util/Constants.hpp"

void Passive::Physics::apply(GameService& gameService)
{
    registry& registry = gameService.getRegistry();
    for(auto& [entity, sprite] : gameService.getSprites())
    {
        if(registry.velocities_map.contains(entity))
        {
            auto& velComp = registry.velocities_map.at(entity);
            sprite.move({velComp.xVel, velComp.yVel});
        }
    }
}

void Passive::Collision::apply(GameService& gameService)
{
    registry& registry = gameService.getRegistry();
    std::vector<entity_t> spritesToRemove;

    for (auto& hittable1 : registry.hittables_tag)
    {
        for (auto& hittable2 : registry.hittables_tag)
        {
            if (hittable1 == hittable2)
            {
                continue;
            }
            if (Util::isColliding(gameService.getSprite(hittable1), gameService.getSprite(hittable2)))
            {
                spritesToRemove.push_back(hittable1);
                spritesToRemove.push_back(hittable2);
            }
        }
    }

    for (auto& spriteEntity : spritesToRemove)
    {
        gameService.destroyEntity(spriteEntity);
    }
}

void Passive::OutOfBounds::apply(GameService& gameService,sf::Vector2u windowSize)
{
    std::vector<entity_t> spritesToRemove;
    registry& registry = gameService.getRegistry();
    for (auto& projectile : registry.projectiles_tag)
    {
        if (Util::isOutOfBounds(gameService.getSprite(projectile), windowSize))
        {
            spritesToRemove.push_back(projectile);
        }
    }

    for (auto& spriteEntity : spritesToRemove)
    {
        gameService.destroyEntity(spriteEntity);
    }
}

void Passive::EnemyMovement::apply(GameService& gameService, sf::Clock& clock)
{
    if (clock.getElapsedTime().asSeconds() < 6.f)
    {
        return;
    }

    registry& registry = gameService.getRegistry();
    for (auto& enemy : registry.enemies_tag)
    {
        sf::Sprite& enemySprite = gameService.getSprite(enemy);
        enemySprite.move({0.f, Constants::ENEMY_MOVEMENT_SPEED});
    }
}

void Passive::EnemyFiring::apply(GameService& gameService, sf::Vector2u windowSize, sf::Clock& clock)
{
    registry& registry = gameService.getRegistry();
    if (clock.getElapsedTime().asSeconds() < 6.f)
    {
        return;
    }

    for (auto& [col, enemy] : registry.lowestEnemies_map)
    {
        if ( (std::rand() % 100) < 75)
        {
            continue;
        }

        entity_t newProjectile = gameService.createSprite("EnemyProjectile");

        sf::Sprite& projectileSprite = gameService.getSprite(newProjectile);

        float x = gameService.getSprite(enemy).getGlobalBounds().size.x / 2.f + gameService.getSprite(enemy).getGlobalBounds().position.x - projectileSprite.getGlobalBounds().size.x / 2.f;

        float y =  gameService.getSprite(enemy).getGlobalBounds().position.y + gameService.getSprite(enemy).getGlobalBounds().size.y + 1.f; 

        projectileSprite.setPosition({x, y});

        registry.projectiles_tag.push_back(newProjectile);
        registry.hittables_tag.push_back(newProjectile);
        registry.velocities_map.insert({newProjectile, {0.f, 4.f}});
    }
    clock.restart();
}


void Passive::Scoring::apply(GameService& gameService, int& score)
{
    int pointsPerHit = 10;
    int hits = 0;

    registry& registry = gameService.getRegistry();
    for (auto& projectile : registry.projectiles_tag)
    {
        for (auto& enemy : registry.enemies_tag)
        {
            if (Util::isColliding(gameService.getSprite(projectile), gameService.getSprite(enemy)))
            {
                hits++;
            }
        }
    }

    score += hits * pointsPerHit;
    gameService.getText("ScoreValue").setString(std::to_string(score));
}

void Passive::GameOverCheck::apply(GameService& gameService, bool& isGameOver)
{
    registry& registry = gameService.getRegistry();

    if (!gameService.getSprites().contains(gameService.getPlayer()))
    {
        isGameOver = true;
        return;
    }

    if (registry.enemies_tag.empty())
    {
        isGameOver = true;
        return;
    }

    for (auto& environment : registry.environment_tag)
    {
        if (registry.entityNames_map[environment] == "GameOverMarker")
        {
            sf::Sprite& gameOverMarker = gameService.getSprite(environment);
            for (auto& enemy : registry.enemies_tag)
            {
                sf::Sprite& enemySprite = gameService.getSprite(enemy);
                if (Util::isColliding(enemySprite, gameOverMarker))
                {
                    isGameOver = true;
                    return;
                }
            }
        }
    }
}