#pragma once

#include "Components.hpp"
#include "EntityManager.hpp"
#include <SFML/Window.hpp>
#include <iostream>

namespace System
{
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
    private:
        static constexpr float PROJECTILE_MOVEMENT_SPEED = 0.50f;
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

}