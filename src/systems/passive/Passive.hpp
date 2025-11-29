#pragma once

#include "../../managers/EntityManager.hpp"
#include "../../model/Registry.hpp"

namespace Passive
{
    class Physics
    {
    public:
        static void apply(EntityManager& entityManager, registry& registry);
    };

    class Collision
    {
    public:
        static void apply(EntityManager& entityManager, registry& registry);
    };

    class OutOfBounds
    {
    public:
        static void apply(EntityManager& entityManager, registry& registry, sf::Vector2u windowSize);
    };

    class EnemyMovement
    {
    public:
        static void apply(EntityManager& entityManager, registry& registry);
    };

    class EnemyFiring
    {
    public:
        static void apply(EntityManager& entityManager, registry& registry, sf::Vector2u windowSize, sf::Clock& clock);
    };

    class Scoring
    {
    public:
        static void apply(EntityManager& entityManager, registry& registry, int& score);
    };
}