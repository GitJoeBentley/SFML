#ifndef MESSAGE_H
#define MESSAGE_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Constants.h"
#include "Fonts.h"

class Message
{
public:
    Message(const std::string& txt, sf::Font& font, unsigned int characterSize=30, sf::Vector2f pos = MidWindow, sf::Color color = sf::Color::Yellow);
    ~Message() = default;
    void draw(sf::RenderWindow& window);

private:
    sf::Text text;
    sf::RectangleShape rectangle;
};

#endif // MESSAGE_H
