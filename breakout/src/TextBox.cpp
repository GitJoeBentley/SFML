#include "TextBox.h"
#include "constants.h"
#include <iostream>

TextBox::TextBox(const std::string& str, sf::Font& font, unsigned int textSize, sf::Color color, sf::Vector2f pos)
: textStr(str), text(str, font, textSize)
{
    text.setFillColor(color);
    text.setPosition(pos);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    setPosition(pos);
    setSize(sf::Vector2f(1.1f * textRect.width, 1.2f * textRect.height));
    setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    setOutlineColor(Indigo);
    setOutlineThickness(4.0f);
    setFillColor(sf::Color::Black);
}

void TextBox::drawTB(sf::RenderWindow& window)
{
    window.draw(*this);
    window.draw(text);
}
