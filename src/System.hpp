#include "Components.hpp"
#include "EntityManager.hpp"
#include <SFML/Window.hpp>
#include <iostream>

namespace System
{
    class MovementSystem
    {
        static constexpr float PLAYER_MOVEMENT_SPEED = 100.f;
        bool static isWithinWindow(const sf::Sprite& sprite, const sf::Vector2u& windowSize, sf::Keyboard::Key direction);
        public:
        void static apply(registry&, const sf::Event::KeyPressed* key, sf::Vector2u windowSize);  
    };

    class PhysicsSystem
    {
        public:
        static void apply(registry& reg);
    };
    
    class FiringSystem
    {
        static constexpr float PROJECTILE_MOVEMENT_SPEED = 100.f;
        public:
        void static apply(registry&, const sf::Event::KeyPressed* key, sf::Vector2u windowSize, EntityManager& entityManager);  
    };

}