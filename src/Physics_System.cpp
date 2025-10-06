#include "Components.hpp"

namespace PhysicsSystem
{
  void apply(registry& reg)
  {
    for (auto& [entity, pos] : reg.positions)
    {
      if (reg.velocities.contains(entity))
      {
        auto& vel = reg.velocities[entity];
        pos.x += vel.xVel;
        pos.y += vel.yVel;
      }
    }
  }
}