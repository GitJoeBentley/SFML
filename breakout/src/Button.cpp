#include "Button.h"
#include "constants.h"

Button::Button(sf::Vector2f buttonSize, sf::Vector2f pos, const std::string& textStr, sf::Font& font, unsigned int textSize)
    : sf::RectangleShape(buttonSize), text(textStr, font, textSize)
{
    setPosition(pos);
    setFillColor(color);
    setOutlineThickness(1.0f);
    setOutlineColor(sf::Color::Green);
    sf::FloatRect buttonRect = getLocalBounds();
    setOrigin(buttonRect.left + buttonRect.width / 2.0f, buttonRect.top + buttonRect.height / 2.0f);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(pos);
}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(*this);
    window.draw(text);
}

void Button::highlight()
{
    setFillColor(highlightedColor);
    text.setFillColor(sf::Color::Black);
    setOutlineColor(sf::Color(0x004844ff));
    setOutlineThickness(3.0f);
}

void Button::normal()
{
    setFillColor(color);
    text.setFillColor(sf::Color::White);
    setOutlineColor(Indigo);
    setOutlineThickness(5.0f);
}

void Button::setColor(sf::Color buttColor, sf::Color textColor)
{
    color = buttColor;
    setFillColor(buttColor);
    text.setFillColor(textColor);
    setOutlineColor(sf::Color::Red);
    setOutlineThickness(3.0f);
}
