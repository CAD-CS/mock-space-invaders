#include "Initializer.hpp"
#include "../util/Util.hpp"
#include <iostream>

Initializer::Initializer(EntityManager& entityManager, registry& registry, int windowWidth, int windowHeight) 
: m_entityManager(entityManager), m_registry(registry)
{
    initializePlayer(windowWidth, windowHeight);
    initializeEnemies();
    initializeBlocks();
    initializeEnvironmentEntities(windowWidth, windowHeight);
}

void Initializer::initializePlayer(int windowWidth, int windowHeight)
{
    entity_t player = m_entityManager.createEntity("Player");
    sf::Sprite& sprite = m_entityManager.getSprite(player);
    float x = (windowWidth - sprite.getLocalBounds().size.x) / 2.f;
    float y = windowHeight - sprite.getLocalBounds().size.y;

    initPosition(player, x, y);
    initVelocity(player);

    m_registry.hittables_tag.push_back(player);
}

void Initializer::initializeEnemies()
{
    const int rows = 2;
    const int cols = Util::COLUMNS;
    const float spacingX = 20.f;
    const float spacingY = 20.f;
    const float startX = 50.f;
    const float startY = 50.f;

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            entity_t enemy = m_entityManager.createEntity
            ("Enemy");
            sf::Sprite& sprite = m_entityManager.getSprite(enemy);
            float x = startX + col * (sprite.getLocalBounds().size.x + spacingX);
            float y = startY + row * (sprite.getLocalBounds().size.y + spacingY);
            initPosition(enemy, x, y);
            initVelocity(enemy);
            m_registry.enemies_tag.push_back(enemy);
            m_registry.hittables_tag.push_back(enemy);
            m_registry.enemyPositions_map.insert({enemy, {row, col}});
        }
    }

    m_entityManager.updateEntities();
}

void Initializer::initializeBlocks()
{
    const int numBlocks = 9;
    const float spacing = 50.f;

    for (int i = 0; i < numBlocks; ++i)
    {
        entity_t block = m_entityManager.createEntity("Block");
        sf::Sprite& sprite = m_entityManager.getSprite(block);
        float x = spacing + i * (sprite.getLocalBounds().size.x + spacing);
        float y = 600.f;
        initPosition(block, x, y);
        initVelocity(block);
        m_registry.hittables_tag.push_back(block);
    }

}

void Initializer::initializeEnvironmentEntities(int windowWidth, int windowHeight)
{
    {
        entity_t gameOverMarker = m_entityManager.createEntity("GameOverMarker");
        sf::Sprite& sprite = m_entityManager.getSprite(gameOverMarker);
        float x = 0.f;
        float y = 900.f;
        initPosition(gameOverMarker, x, y);
        m_registry.environment_tag.push_back(gameOverMarker);
    }

    {
        entity_t pauseButton = m_entityManager.createEntity("Pause");
        sf::Sprite& pauseSprite = m_entityManager.getSprite(pauseButton);
        float x = windowWidth - pauseSprite.getLocalBounds().size.x - 10.f;
        float y = 10.f;
        std::cout << "Pause and unpause button initialized at (" << x << ", " << y << ")\n";
        initPosition(pauseButton, x, y);
        m_registry.environment_tag.push_back(pauseButton);
    }

    {
        entity_t unpauseButton = m_entityManager.createEntity("Unpause");
        sf::Sprite& unpauseSprite = m_entityManager.getSprite(unpauseButton);
        float x = windowWidth - unpauseSprite.getLocalBounds().size.x - 10.f;
        float y = 10.f;
        initPosition(unpauseButton, x, y);
        m_registry.environment_tag.push_back(unpauseButton);
    }

}

void Initializer::initPosition(entity_t entity, float x, float y)
{
    if(m_entityManager.getSprites().contains(entity))
    {
        sf::Sprite& sprite = m_entityManager.getSprite(entity);
        sprite.setPosition({x,y});
    }
}

void Initializer::initVelocity(entity_t entity)
{
    m_registry.velocities_map.insert({entity, {.0f, 0.0f}});
}