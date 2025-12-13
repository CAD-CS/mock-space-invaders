#pragma once

#include "../managers/EntityManager.hpp"
#include "../managers/SpriteManager.hpp"
#include "../managers/TextManager.hpp"
#include "../managers/TextureManager.hpp"
#include "../model/Registry.hpp"
#include "../util/Util.hpp"
#include "../util/Constants.hpp"

class GameService
{

private:
    EntityManager m_entityManager;
    SpriteManager m_spriteManager;
    TextManager m_textManager;
    TextureManager m_textureManager;
    registry m_registry;


public:
    GameService();
    ~GameService();

    entity_t createSprite(std::string texture, sf::Vector2f position = {0.f, 0.f});
    void createText(std::string initialText, std::string textKey, sf::Vector2f position);

    void destroyEntity(entity_t entity);

    sf::Sprite& getSprite(entity_t entity);
    sf::Text& getText(std::string textLabel);

    std::unordered_map<entity_t, sf::Sprite>& getSprites();
    std::unordered_map<std::string, sf::Text>& getTexts();
    
    void updateEntities();

    registry& getRegistry();

    entity_t getPlayer();
};