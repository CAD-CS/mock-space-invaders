#include "EntityManager.hpp"
#include "../model/Registry.hpp"
#include "../util/Util.hpp"
#include <cassert>
#include <iostream>
#include <filesystem>

EntityManager::EntityManager()
: m_entities(0)
{}

entity_t EntityManager::createEntity()
{
    assert(m_entities < MAX_ENTITIES && "Too many entities in existence.");

    entity_t newEntity = ++m_entities;

    return newEntity;
}

entity_t EntityManager::getPlayer() { return 1; }
