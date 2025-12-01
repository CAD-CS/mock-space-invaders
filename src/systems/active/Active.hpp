#pragma once

#include "../../managers/EntityManager.hpp"
#include "../../model/Registry.hpp"
#include <SFML/Graphics.hpp>

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

    class Pause
    {
    public:
        static void apply(sf::Vector2u windowSize,  bool& isPaused, const sf::Event::KeyPressed* key);  
        static void apply(sf::Vector2u windowSize, bool& isPaused, const sf::Event::MouseButtonPressed* click);  
    };
    
}