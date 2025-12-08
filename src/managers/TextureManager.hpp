#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>

constexpr int MAX_TEXTURES = 20;
class TextureManager
{
private:
    std::unordered_map<std::string, sf::Texture> m_textures;

    void loadTextures();
    void loadTexture(const std::string& texturePath, const std::string& textureName);

public:
    TextureManager();
    ~TextureManager();

    sf::Texture& getTexture(std::string textureName);
    std::unordered_map<std::string, sf::Texture>& getTextures();
};