#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>

using entity_t = std::size_t;

struct velocity_component
{
    float xVel;
    float yVel;
};

struct registry
{
    std::unordered_map<entity_t, velocity_component> velocities_map;
    std::unordered_map<entity_t, std::string> entityNames_map;

    std::vector<entity_t> projectiles_tag;
    std::vector<entity_t> enemies_tag;
    std::vector<entity_t> hittables_tag;
};