#include <SFML/Graphics.hpp>
#include <cstdio>
#include "PhysicsSystem.hpp"
#include "EntityManager.hpp"

void PhysicsSystem::apply(registry& reg)
{
  for(auto& [entity, posComp] : reg.positions)
  {
    if(reg.velocities.contains(entity))
    {
      auto& velComp = reg.velocities[entity];
      posComp.x += velComp.xVel;
      posComp.y += velComp.yVel;
      reg.sprites[entity].sprite.setPosition(posComp.x, posComp.y);
    }
  }
}