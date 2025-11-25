#pragma once

#include "EntityManager.hpp"

namespace Active
{
    class Movement
    {
    public:
        static void apply(EntityManager& entityManager, const sf::Event::KeyPressed* key, sf::Vector2u windowSize);  
    };

    class Firing
    {
    public:
        static void apply(EntityManager& entityManager, registry& registry, const sf::Event::KeyPressed* key, sf::Vector2u windowSize);  
    };
    
}