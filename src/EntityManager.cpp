#include "EntityManager.hpp"
#include <cassert>

EntityManager::EntityManager() : m_entities(0) {}

entity_t EntityManager::createEntity()
{
    assert(m_entities < MAX_ENTITIES && "Too many entities in existence.");
    return m_entities++;
}