#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Window");

    sf::Texture texture;
    texture.loadFromFile("./ball.jpg");

    sf::Sprite sprite(texture);

    sf::Font font;
    font.loadFromFile("./BOOKOS.TTF");

    sf::Text text;
    text.setFont(font);
    text.setString("Hello!");
    text.setFillColor(sf::Color::Blue);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);
        window.draw(sprite);
        window.draw(text);
        window.display();
    }
    return 0;
}
