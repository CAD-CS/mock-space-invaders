#pragma once

#include <cstdint>
#include <unordered_map>

using entity_t = std::size_t;
constexpr entity_t MAX_ENTITIES = 5;

struct position_component
{
  int x;
  int y;
};

struct registry
{
  std::unordered_map<entity_t, position_component> positions;
};

class EntityManager
{

private:
  entity_t m_entities;

public:
  EntityManager() : m_entities(0) {}

  entity_t createEntity();
};
