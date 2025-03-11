#include "Message.h"
#include <iostream>

Message::Message(const std::string& txt, sf::Font& font, unsigned int characterSize, sf::Vector2f pos, sf::Color color, bool contButton)
    : text(txt, font, characterSize)
{
    text.setFillColor(color);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(pos);

    setSize(sf::Vector2f(textRect.width * 1.2f, textRect.height * 1.2f));
    setOutlineColor(sf::Color(0xFF7F27));
    setOutlineThickness(10.0f);
    setFillColor(sf::Color(sf::Color::Black));
    sf::FloatRect rect = getLocalBounds();
    setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
    setPosition(pos);
    if (contButton)
    {
        unsigned fontsize = 20u;
        const std::string continueStr("CONTINUE");

        sf::Vector2f buttonSize = sf::Vector2f(continueStr.size() * fontsize * 1.1f, fontsize*1.5f);
        setSize(sf::Vector2f(getSize().x, getSize().y + buttonSize.y * 1.5f));

        continueButton = new Button(buttonSize, sf::Vector2f(getPosition().x, getPosition().y + 0.45 * getSize().y), continueStr, font, fontsize);
        sf::FloatRect continueButtonRect = continueButton->getLocalBounds();
        continueButton->setOrigin(continueButtonRect.left + continueButtonRect.width / 2.0f, continueButtonRect.top + continueButtonRect.height / 2.0f);
        continueButton->setButtColorTextColor(sf::Color::Yellow, sf::Color::Black);

        //sf::Vector2f continueButtonPosition = sf::Vector2f(pos.x, getPosition().y + .45 * getSize().y);
        //continueButton->setPosition(continueButtonPosition);
    }
}


void Message::draw(sf::RenderWindow& window)
{
    window.draw(*this);
    window.draw(text) ;
    if (continueButton) continueButton->draw(window);
}
