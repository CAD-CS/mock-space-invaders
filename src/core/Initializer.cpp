#include "Initializer.hpp"

Initializer::Initializer(GameService& GameService, int windowWidth, int windowHeight) 
: 
gameService(GameService),
m_registry(gameService.getRegistry())
    {
    initializePlayer(windowWidth, windowHeight);
    initializeEnemies();
    initializeBlocks();
    initializeEnvironmentEntities(windowWidth, windowHeight);
    initializeScoreBoard();
}

void Initializer::initializePlayer(int windowWidth, int windowHeight)
{
    entity_t player = gameService.createSprite("Player");
    sf::Sprite& sprite = gameService.getSprite(player);
    float x = (windowWidth - sprite.getLocalBounds().size.x) / 2.f;
    float y = windowHeight - sprite.getLocalBounds().size.y;

    initPosition(player, x, y);
    initVelocity(player);

    m_registry.hittables_tag.push_back(player);
}

void Initializer::initializeEnemies()
{
    const int rows = 4;
    const int cols = Util::COLUMNS;
    const float spacingX = 20.f;
    const float spacingY = 20.f;
    const float startX = 180.f;
    const float startY = 150.f;

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            entity_t enemy = gameService.createSprite("Enemy");
            sf::Sprite& sprite = gameService.getSprite(enemy);
            float x = startX + col * (sprite.getLocalBounds().size.x + spacingX);
            float y = startY + row * (sprite.getLocalBounds().size.y + spacingY);
            initPosition(enemy, x, y);
            initVelocity(enemy);
            m_registry.enemies_tag.push_back(enemy);
            m_registry.hittables_tag.push_back(enemy);
            m_registry.enemyPositions_map.insert({enemy, {row, col}});
        }
    }

    gameService.updateEntities();
}

void Initializer::initializeBlocks()
{
    const int numBlocks = 9;
    const float spacing = 50.f;

    for (int i = 0; i < numBlocks; ++i)
    {
        entity_t block = gameService.createSprite("Block");
        sf::Sprite& sprite = gameService.getSprite(block);
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
        entity_t gameOverMarker = gameService.createSprite("GameOverMarker");
        sf::Sprite& sprite = gameService.getSprite(gameOverMarker);
        float x = 0.f;
        float y = 900.f;
        initPosition(gameOverMarker, x, y);
        m_registry.environment_tag.push_back(gameOverMarker);
    }

    {
        entity_t pauseButton = gameService.createSprite("Pause");
        sf::Sprite& pauseSprite = gameService.getSprite(pauseButton);
        float x = windowWidth - pauseSprite.getLocalBounds().size.x - 10.f;
        float y = 10.f;
        initPosition(pauseButton, x, y);
        m_registry.environment_tag.push_back(pauseButton);
    }

    {
        entity_t unpauseButton = gameService.createSprite("Unpause");
        sf::Sprite& unpauseSprite = gameService.getSprite(unpauseButton);
        float x = windowWidth - unpauseSprite.getLocalBounds().size.x - 10.f;
        float y = 10.f;
        initPosition(unpauseButton, x, y);
        m_registry.environment_tag.push_back(unpauseButton);
    }
}

void Initializer::initializeScoreBoard()
{
    entity_t scoreBoard = gameService.createSprite("ScoreBoard");
    sf::Sprite& sprite = gameService.getSprite(scoreBoard);
    float x = 10.f;
    float y = 10.f;
    initPosition(scoreBoard, x, y);
    m_registry.environment_tag.push_back(scoreBoard);

    gameService.createText("Score: 0", "ScoreLabel", {x + 15.f, y + 10.f});
    sf::Text& scoreBoardLabel = gameService.getText("ScoreLabel");
}

void Initializer::initPosition(entity_t entity, float x, float y)
{
    sf::Sprite& sprite = gameService.getSprite(entity);
    sprite.setPosition({x,y});
}

void Initializer::initVelocity(entity_t entity)
{
    m_registry.velocities_map.insert({entity, {.0f, 0.0f}});
}