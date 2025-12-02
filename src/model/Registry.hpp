#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Components.hpp"

struct registry
{
    std::unordered_map<entity_t, velocity_component> velocities_map;
    std::unordered_map<entity_t, std::string> entityNames_map;
    std::unordered_map<entity_t, enemyPosition_component> enemyPositions_map;
    std::unordered_map<int, entity_t> lowestEnemies_map;
    std::unordered_map<entity_t, sf::Text> texts_map;

    std::vector<entity_t> projectiles_tag;
    std::vector<entity_t> enemies_tag;
    std::vector<entity_t> hittables_tag;
    std::vector<entity_t> environment_tag;
};
