#include "TextureManager.hpp"

TextureManager::TextureManager()
{
    m_textures.reserve(MAX_TEXTURES);

    loadTextures();
}

TextureManager::~TextureManager()
{
    m_textures.clear();
}

void TextureManager::loadTextures()
{
    loadTexture("./assets/player.jpg", "Player");
    loadTexture("./assets/enemy.jpg", "Enemy");
    loadTexture("./assets/block.jpg", "Block");
    loadTexture("./assets/player_projectile.jpg", "PlayerProjectile");
    loadTexture("./assets/enemy_projectile.jpg", "EnemyProjectile");
    loadTexture("./assets/game_over_mark.jpg", "GameOverMarker");
    loadTexture("./assets/pause.jpg", "Pause");
    loadTexture("./assets/unpause.jpg", "Unpause");
    loadTexture("./assets/scoreboard.jpg", "ScoreBoard");
}

void TextureManager::loadTexture(const std::string& texturePath, const std::string& textureName)
{
    sf::Texture texture;
    if (!texture.loadFromFile(texturePath))
    {
        throw std::runtime_error("Failed to load texture from path: " + texturePath);
    }
    m_textures.try_emplace(textureName, texture);
}

sf::Texture& TextureManager::getTexture(std::string textureName)
{
    assert(m_textures.contains(textureName) && "Texture not found in texture map.");
    return m_textures.at(textureName);
}

std::unordered_map<std::string, sf::Texture>& TextureManager::getTextures()
{
    return m_textures;
}