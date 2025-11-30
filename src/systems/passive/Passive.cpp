#include "Passive.hpp"
#include "../../util/Util.hpp"
#include <iostream>

void Passive::Physics::apply(EntityManager& entityManager, registry& registry)
{
    for(auto& [entity, sprite] : entityManager.getSprites())
    {
        if(registry.velocities_map.contains(entity))
        {
            auto& velComp = registry.velocities_map.at(entity);
            sprite.move({velComp.xVel, velComp.yVel});
        }
    }
}

void Passive::Collision::apply(EntityManager& entityManager, registry& registry)
{
    std::vector<entity_t> spritesToRemove;

    for (auto& hittable1 : registry.hittables_tag)
    {
        for (auto& hittable2 : registry.hittables_tag)
        {
            if (hittable1 == hittable2)
            {
                continue;
            }
            if (Util::isColliding(entityManager.getSprite(hittable1), entityManager.getSprite(hittable2)))
            {
                spritesToRemove.push_back(hittable1);
                spritesToRemove.push_back(hittable2);
            }
        }
    }

    for (auto& spriteEntity : spritesToRemove)
    {
        entityManager.destroyEntity(spriteEntity);
    }
}

void Passive::OutOfBounds::apply(EntityManager& entityManager, registry& registry,sf::Vector2u windowSize)
{
    std::vector<entity_t> spritesToRemove;

    for (auto& projectile : registry.projectiles_tag)
    {
        if (Util::isOutOfBounds(entityManager.getSprite(projectile), windowSize))
        {
            spritesToRemove.push_back(projectile);
        }
    }

    for (auto& spriteEntity : spritesToRemove)
    {
        entityManager.destroyEntity(spriteEntity);
    }
}

void Passive::EnemyMovement::apply(EntityManager& entityManager, registry& registry)
{
    for (auto& enemy : registry.enemies_tag)
    {
        sf::Sprite& enemySprite = entityManager.getSprite(enemy);
        enemySprite.move({0.f, Util::ENEMY_MOVEMENT_SPEED});
    }
}

void Passive::EnemyFiring::apply(EntityManager& entityManager, registry& registry, sf::Vector2u windowSize, sf::Clock& clock)
{
    if (clock.getElapsedTime().asSeconds() < 1.f)
    {
        return;
    }

    for (auto& [col, enemy] : registry.lowestEnemies_map)
    {
        entity_t newProjectile = entityManager.createEntity("EnemyProjectile");

        sf::Sprite& projectileSprite = entityManager.getSprite(newProjectile);

        float x = entityManager.getSprite(enemy).getGlobalBounds().size.x / 2.f + entityManager.getSprite(enemy).getGlobalBounds().position.x - projectileSprite.getGlobalBounds().size.x / 2.f;

        float y =  entityManager.getSprite(enemy).getGlobalBounds().position.y + entityManager.getSprite(enemy).getGlobalBounds().size.y + 1.f; 

        projectileSprite.setPosition({x, y});

        registry.projectiles_tag.push_back(newProjectile);
        registry.hittables_tag.push_back(newProjectile);
        registry.velocities_map.insert({newProjectile, {0.f, 1.f}});
    }
    clock.restart();
}


void Passive::Scoring::apply(EntityManager& entityManager, registry& registry, int& score)
{
    int pointsPerHit = 10;
    int hits = 0;

    for (auto& projectile : registry.projectiles_tag)
    {
        for (auto& enemy : registry.enemies_tag)
        {
            if (Util::isColliding(entityManager.getSprite(projectile), entityManager.getSprite(enemy)))
            {
                hits++;
            }
        }
    }

    score += hits * pointsPerHit;
}

void Passive::GameOverCheck::apply(EntityManager& entityManager, registry& registry, bool& isGameOver)
{
    for (auto& environment : registry.environment_tag)
    {
        if (registry.entityNames_map[environment] == "GameOverMarker")
        {
            sf::Sprite& gameOverMarker = entityManager.getSprite(environment);
            for (auto& enemy : registry.enemies_tag)
            {
                sf::Sprite& enemySprite = entityManager.getSprite(enemy);
                if (Util::isColliding(enemySprite, gameOverMarker))
                {
                    isGameOver = true;
                    throw std::runtime_error("Game Over!");
                    return;
                }
            }
        }
    }
}