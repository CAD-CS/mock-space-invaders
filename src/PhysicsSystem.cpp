#include "PhysicsSystem.hpp"
#include <SFML/Graphics.hpp>

void PhysicsSystem::apply(registry& reg)
{
  for(auto& [entity, posComp] : reg.positions)
  {
    if(reg.velocities.find(entity) != reg.velocities.end())
    {
      auto& velComp = reg.velocities[entity];
      posComp.x += velComp.xVel;
      posComp.y += velComp.yVel;

      if(reg.sprites.find(entity) != reg.sprites.end())
      {
        reg.sprites[entity].sprite.setPosition(posComp.x, posComp.y);
      }
    }
  }
}