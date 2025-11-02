#include <SFML/Graphics.hpp>
#include <cstdio>
#include "PhysicsSystem.hpp"
#include "EntityManager.hpp"

void PhysicsSystem::apply(registry& reg)
{

  for(auto& [entity, sprite] : reg.sprites)
  {
    if(reg.velocities.contains(entity))
    {
      auto& velComp = reg.velocities.at(entity);
      sprite.move({velComp.xVel, velComp.yVel});
    }
  }
}