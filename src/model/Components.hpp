#pragma once

using entity_t = std::size_t;

struct velocity_component
{
    float xVel;
    float yVel;
};

struct enemyPosition_component
{
    int row;
    int col;
};
