#pragma once

#include "Components.hpp"
#include "EntityManager.hpp"
#include <SFML/Window.hpp>
#include <iostream>

namespace System
{
    static constexpr float PROJECTILE_MOVEMENT_SPEED = 2.f;
    static bool isColliding(const sf::Sprite& spriteA, const sf::Sprite& spriteB);
    class MovementSystem
    {
    private:
        static constexpr float PLAYER_MOVEMENT_SPEED = 100.f;
        bool static isWithinWindow(const sf::Sprite& sprite, const sf::Vector2u& windowSize, sf::Keyboard::Key direction);
    public:
        void static apply(EntityManager& entityManager, const sf::Event::KeyPressed* key, sf::Vector2u windowSize);  
    };

    class PhysicsSystem
    {
    public:
        static void apply(EntityManager& entityManager);
    };
    
    class FiringSystem
    {
    public:
        void static apply(EntityManager& entityManager, const sf::Event::KeyPressed* key, sf::Vector2u windowSize);  
    };

    class CollisionSystem
    {
    private:
        static bool isColliding(const sf::Sprite& spriteA, const sf::Sprite& spriteB);
    public:
        static void apply(EntityManager& entityManager);
    };

    class OutOfBoundsSystem
    {
    private:
        static bool isOutOfBounds(const sf::Sprite& sprite, const sf::Vector2u& windowSize);
    public:
        static void apply(EntityManager& entityManager, sf::Vector2u windowSize);
    };

    class EnemyMovementSystem
    {
    private:
        static constexpr float ENEMY_MOVEMENT_SPEED = 0.5f;
    public:
        static void apply(EntityManager& entityManager);
    };

    class EnemyFiringSystem
    {
    public:
        static void apply(EntityManager& entityManager, sf::Vector2u windowSize, sf::Clock& clock);
    };

    class ScoringSystem
    {
    public:
        static void apply(EntityManager& entityManager, int& score);
    };
}

// TODO: Enemy firing system, game over system, scoring system, pausing system