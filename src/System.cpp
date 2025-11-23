#include "System.hpp"

void System::MovementSystem::apply(EntityManager& entityManager, const sf::Event::KeyPressed* key, sf::Vector2u windowSize) 
{
    sf::Sprite& playerSprite = entityManager.getSprite(entityManager.getPlayer());

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

void System::PhysicsSystem::apply(EntityManager& entityManager)
{
    for(auto& [entity, sprite] : entityManager.getSprites())
    {
        if(entityManager.getRegistry().velocities_map.contains(entity))
        {
            auto& velComp = entityManager.getRegistry().velocities_map.at(entity);
            sprite.move({velComp.xVel, velComp.yVel});
        }
    }
}

void System::FiringSystem::apply(EntityManager& entityManager, const sf::Event::KeyPressed* key, sf::Vector2u windowSize) 
{
    switch (key->code) 
    {
    case sf::Keyboard::Key::Up:
        entity_t newProjectile = entityManager.createEntity("Projectile");

        sf::Sprite& projectileSprite = entityManager.getSprite(newProjectile);

        float x = entityManager.getSprite(entityManager.getPlayer()).getGlobalBounds().size.x / 2.f + entityManager.getSprite(entityManager.getPlayer()).getGlobalBounds().position.x - projectileSprite.getGlobalBounds().size.x / 2.f;

        float y =  entityManager.getSprite(entityManager.getPlayer()).getGlobalBounds().position.y - projectileSprite.getGlobalBounds().size.y - 1.f; 

        projectileSprite.setPosition({x, y});

        entityManager.getRegistry().projectiles_tag.push_back(newProjectile);
        entityManager.getRegistry().velocities_map.insert({newProjectile, {0.f, -System::PROJECTILE_MOVEMENT_SPEED}});

        return;
    }
}

void System::CollisionSystem::apply(EntityManager& entityManager)
{
    std::vector<entity_t> spritesToRemove;

    for (auto& hittable1 : entityManager.getRegistry().hittables_tag)
    {
        for (auto& hittable2 : entityManager.getRegistry().hittables_tag)
        {
            if (hittable1 == hittable2)
            {
                continue;
            }
            if (isColliding(entityManager.getSprite(hittable1), entityManager.getSprite(hittable2)))
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

bool System::isColliding(const sf::Sprite& spriteA, const sf::Sprite& spriteB)
{
    sf::FloatRect boundsA = spriteA.getGlobalBounds();
    sf::FloatRect boundsB = spriteB.getGlobalBounds();

    bool collisionX = (boundsA.position.x < boundsB.position.x + boundsB.size.x) && (boundsA.position.x + boundsA.size.x > boundsB.position.x);

    bool collisionY = (boundsA.position.y < boundsB.position.y + boundsB.size.y) && (boundsA.position.y + boundsA.size.y > boundsB.position.y);

    return collisionX && collisionY;
}


void System::OutOfBoundsSystem::apply(EntityManager& entityManager, sf::Vector2u windowSize)
{
    std::vector<entity_t> spritesToRemove;

    for (auto& projectile : entityManager.getRegistry().projectiles_tag)
    {
        if (isOutOfBounds(entityManager.getSprite(projectile), windowSize))
        {
            spritesToRemove.push_back(projectile);
        }
    }

    for (auto& spriteEntity : spritesToRemove)
    {
        entityManager.destroyEntity(spriteEntity);
    }
}

bool System::OutOfBoundsSystem::isOutOfBounds(const sf::Sprite& sprite, const sf::Vector2u& windowSize)
{
    sf::FloatRect bounds = sprite.getGlobalBounds();

    if (bounds.position.y + bounds.size.y < 0 || bounds.position.y > windowSize.y)
    {
        return true;
    }

    return false;
} 

void System::EnemyMovementSystem::apply(EntityManager& entityManager)
{
    for (auto& enemy : entityManager.getRegistry().enemies_tag)
    {
        sf::Sprite& enemySprite = entityManager.getSprite(enemy);
        enemySprite.move({0.f, ENEMY_MOVEMENT_SPEED});
    }
}

void System::EnemyFiringSystem::apply(EntityManager& entityManager, sf::Vector2u windowSize, sf::Clock& clock)
{
    if (clock.getElapsedTime().asSeconds() < 3.f)
    {
        return;
    }

    for (auto& [col, enemy] : entityManager.getRegistry().lowestEnemies_map)
    {
        entity_t newProjectile = entityManager.createEntity("Projectile");

        sf::Sprite& projectileSprite = entityManager.getSprite(newProjectile);

        float x = entityManager.getSprite(enemy).getGlobalBounds().size.x / 2.f + entityManager.getSprite(enemy).getGlobalBounds().position.x - projectileSprite.getGlobalBounds().size.x / 2.f;

        float y =  entityManager.getSprite(enemy).getGlobalBounds().position.y + entityManager.getSprite(enemy).getGlobalBounds().size.y + 1.f; 

        projectileSprite.setPosition({x, y});

        entityManager.getRegistry().projectiles_tag.push_back(newProjectile);
        entityManager.getRegistry().velocities_map.insert({newProjectile, {0.f, 0.50f}});
    }
    clock.restart();
}


void System::ScoringSystem::apply(EntityManager& entityManager, int& score)
{
    int pointsPerHit = 10;
    int hits = 0;

    for (auto& projectile : entityManager.getRegistry().projectiles_tag)
    {
        for (auto& enemy : entityManager.getRegistry().enemies_tag)
        {
            if (System::isColliding(entityManager.getSprite(projectile), entityManager.getSprite(enemy)))
            {
                hits++;
            }
        }
    }

    score += hits * pointsPerHit;
}