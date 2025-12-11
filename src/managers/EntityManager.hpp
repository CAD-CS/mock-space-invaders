#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include "../model/Components.hpp"
#include "../model/Registry.hpp"

constexpr entity_t MAX_ENTITIES = 500;

class EntityManager
{

private:
    entity_t m_entities;

public:
    EntityManager();
    ~EntityManager() = default;

    entity_t createEntity();
    entity_t getPlayer();
    void decreaseEntityCount();
};
