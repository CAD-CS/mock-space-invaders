#pragma once

#include <cstddef>

using entity_t = std::size_t;

struct VelocityComponent
{
    float xVel;
    float yVel;
};

struct EnemyPositionComponent
{
    int row;
    int col;
};
