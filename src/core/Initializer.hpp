#pragma once

#include <iostream>
#include "GameService.hpp"
#include "../model/Registry.hpp"
#include "../util/Util.hpp"

class Initializer
{
private:
    GameService& gameService;
    registry& m_registry;

    void initializePlayer(int windowWidth, int windowHeight);
    void initializeEnemies();
    void initializeBlocks();
    void initializeEnvironmentEntities(int windowWidth, int windowHeight);
    void initializeScoreBoard();
    void initPosition(entity_t entity, float x, float y);
    void initVelocity(entity_t entity);
public:
    Initializer(GameService& gameService, int windowWidth, int windowHeight);
    
};