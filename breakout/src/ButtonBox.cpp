#include "ButtonBox.h"
#include "constants.h"
#include <SFML/Graphics.hpp>

ButtonBox::ButtonBox(sf::RenderWindow& wdw, std::vector<std::string> buttonLabels, sf::Font& font, unsigned textSize)
    : window(wdw), numButtons(buttonLabels.size()), buttons(new Button*[numButtons])
{
    // Determine button width
    // Find longest button width
    size_t maxStrLength = 0;
    for (int i = 0; i < numButtons; i++)
        if (buttonLabels[i].size() > maxStrLength) maxStrLength = buttonLabels[i].size();
    sf::Vector2f buttonSize = sf::Vector2f(maxStrLength * textSize * 1.1f, textSize * 1.5f);
    float buttonOffset = 2.75f * textSize;

    // Determine button window size
    setSize(sf::Vector2f(1.2f * buttonSize.x, (numButtons + .95f) * buttonOffset));
    sf::FloatRect localRect = getLocalBounds();
    setOrigin(localRect.left + localRect.width / 2.0f, localRect.top + localRect.height / 2.0f);
    setPosition(sf::Vector2f(wdw.getSize().x/2.0f, wdw.getSize().y/2.0f));
    //setOutlineColor(Red);
    //setOutlineThickness(2.0f);
    setFillColor(sf::Color::Black);

    sf::FloatRect globalRect = getGlobalBounds();
    float windowTop = globalRect.top;
    float windowMiddle = globalRect.left + localRect.width / 2.0f;

    // create the buttons
    for (int i = 0; i < numButtons; i++)
    {
        buttons[i] = new Button(buttonSize, sf::Vector2f(windowMiddle, windowTop + (i + 1.15f) *  buttonOffset), buttonLabels[i], font, textSize);
    }
    buttons[numButtons - 1] -> setColor(Green, sf::Color::Black);

    //msgText.setFillColor(sf::Color::Cyan);
    //sf::FloatRect textRect = msgText.getLocalBounds();
    //msgText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    //msgText.setPosition(sf::Vector2f(windowMiddle, windowTop + (numButtons + 2.0f) *  buttonOffset));
}

sf::Vector2f ButtonBox::getBoxSize() const
{
    return getSize();
}

Button** ButtonBox::getButtons() const
{
    return buttons;
}

Button* ButtonBox::getButton(int index) const
{
    return buttons[index];
}

void ButtonBox::draw()
{
    window.draw(*this);
    for (int i = 0; i < numButtons; i++)
        buttons[i]->draw(window);
    //window.draw(msgText);
}

sf::Vector2f ButtonBox::getUpperLeftCorner() const
{
    sf::FloatRect boxRect = getGlobalBounds();
    return sf::Vector2f(boxRect.left, boxRect.top);
}
