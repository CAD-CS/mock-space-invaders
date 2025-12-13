#pragma once

#include <SFML/Graphics.hpp>
#include "../../model/Registry.hpp"
#include "../../core/GameService.hpp"

namespace Active
{
    class Movement
    {
    public:
        static void apply(GameService& gameService, const sf::Event::KeyPressed* key, sf::Vector2u windowSize);  
    };

    class Firing
    {
    public:
        static void apply(GameService& gameService, const sf::Event::KeyPressed* key, sf::Vector2u windowSize);  
    };

    class Pause
    {
    public:
        static void apply(const sf::Event::KeyPressed* key, sf::Vector2u windowSize,  bool& isPaused);
        static void apply(const sf::Event::MouseButtonPressed* click, sf::Vector2u windowSize, bool& isPaused);  
    };
    
}