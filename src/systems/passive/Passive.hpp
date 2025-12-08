#pragma once

#include "../../model/Registry.hpp"
#include "../../core/GameService.hpp"

namespace Passive
{
    class Physics
    {
    public:
        static void apply(GameService& gameService);
    };

    class Collision
    {
    public:
        static void apply(GameService& gameService);
    };

    class OutOfBounds
    {
    public:
        static void apply(GameService& gameService, sf::Vector2u windowSize);
    };

    class EnemyMovement
    {
    public:
        static void apply(GameService& gameService);
    };

    class EnemyFiring
    {
    public:
        static void apply(GameService& gameService, sf::Vector2u windowSize, sf::Clock& clock);
    };

    class Scoring
    {
    public:
        static void apply(GameService& gameService, int& score);
    };

    class GameOverCheck
    {
    public:
        static void apply(GameService& gameService, bool& isGameOver);
    };
}