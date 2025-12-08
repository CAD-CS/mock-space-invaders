#include "TextManager.hpp"

TextManager::TextManager()
: 
m_font("./assets/BOOKOS.TTF")
{}

TextManager::~TextManager()
{
    m_texts.clear();
}

sf::Text& TextManager::createText(std::string initialText, std::string textKey, sf::Vector2f position)
{
    sf::Text text(m_font, initialText, 12);
    text.setPosition(position);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);

    m_texts.try_emplace(textKey, text);

    return m_texts.at(textKey);
}

std::unordered_map<std::string, sf::Text>& TextManager::getTexts()
{
    return m_texts;
}

sf::Text& TextManager::getText(std::string textKey)
{
    assert(m_texts.contains(textKey) && "Text not found in text map.");
    return m_texts.at(textKey);
}