#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include "../model/Components.hpp"
#include "../model/Registry.hpp"

class TextManager
{
private:
    sf::Font m_font;
    std::unordered_map<std::string, sf::Text> m_texts;

public:
    TextManager();
    ~TextManager();

    sf::Text& createText(std::string initialText, std::string textKey, sf::Vector2f position);

    std::unordered_map<std::string, sf::Text>& getTexts();
    sf::Text& getText(std::string textKey);
};

