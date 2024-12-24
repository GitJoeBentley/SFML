#include "Message.h"
#include "Fonts.h"
#include <iostream>

Message::Message(const std::string& txt, sf::Font& font, unsigned int characterSize, sf::Vector2f pos, sf::Color color)
    : text(txt, font, characterSize)
{
    //text.setFont(Fonts::Arial);
    text.setFillColor(color);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left +
                   textRect.width / 2.0f,
                   textRect.top +
                   textRect.height / 2.0f);
    text.setPosition(pos);

    rectangle.setSize(sf::Vector2f(textRect.width * 1.2f, textRect.height * 1.5f));
    rectangle.setOutlineColor(sf::Color::Blue);
    rectangle.setOutlineThickness(10.0f);
    rectangle.setFillColor(sf::Color(sf::Color::Black));
    sf::FloatRect rect = rectangle.getLocalBounds();
    rectangle.setOrigin(rect.left +
                        rect.width / 2.0f,
                        rect.top +
                        rect.height / 2.0f);
    rectangle.setPosition(pos);


}

void Message::draw(sf::RenderWindow& window)
{
    //text.setFont(Fonts::Arial);
    window.draw(rectangle);
    //std::cout << text.getString().toAnsiString() << ' ' << text.getFont()->getInfo().family << std::endl;
    window.draw(text) ;
}
