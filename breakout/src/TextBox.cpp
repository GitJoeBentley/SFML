#include "TextBox.h"

TextBox::TextBox(std::string textStr, sf::Font& font, unsigned int textSize, sf::Color color, sf::Vector2f pos)
: text(textStr, font, textSize)
{

    text.setFillColor(color);
    text.setPosition(pos);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    setPosition(pos);
    setSize(sf::Vector2f(1.1f * textRect.width, 1.1f * textRect.height));
    setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    setOutlineColor(sf::Color::Blue);
    setOutlineThickness(2.0f);
    setFillColor(sf::Color::Black);
}

void TextBox::draw(sf::RenderWindow& window)
{
    window.draw(*this);
    window.draw(text);
}
