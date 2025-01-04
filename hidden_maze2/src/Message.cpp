#include "Message.h"
#include "Fonts.h"
#include <iostream>

Message::Message(const std::string& txt, sf::Font& font, unsigned int characterSize, sf::Vector2f pos, sf::Color color)
    : text(txt, font, characterSize)
{
    text.setFillColor(color);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(pos);

    setSize(sf::Vector2f(textRect.width * 1.2f, textRect.height * 1.5f));
    setOutlineColor(sf::Color::Blue);
    setOutlineThickness(10.0f);
    setFillColor(sf::Color(sf::Color::Black));
    sf::FloatRect rect = getLocalBounds();
    setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
    setPosition(pos);
}


void Message::draw(sf::RenderWindow& window)
{
    window.draw(*this);
    window.draw(text) ;
}
