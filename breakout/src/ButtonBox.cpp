#include "ButtonBox.h"
#include "Button.h"


ButtonBox::ButtonBox(sf::RenderWindow& wdw, std::vector<std::string> buttonLabels, const std::string& message, sf::Font& font, unsigned textSize)
: window(wdw), numButtons(buttonLabels.size()), buttons(new Button*[numButtons]), msgText(message,font,textSize)
{
    // Determine button width
    // Find longest button width
    size_t maxStrLength = 0;
    for (int i = 0; i < numButtons; i++)
        if (buttonLabels[i].size() > maxStrLength) maxStrLength = buttonLabels[i].size();
    sf::Vector2f buttonSize = sf::Vector2f(maxStrLength * textSize * 1.1f, textSize * 1.5f);
    float buttonOffset = 2.5f * textSize;

    // Determine button window size
    setSize(sf::Vector2f(2.0f * buttonSize.x, (numButtons + 3) * buttonOffset));
    sf::FloatRect localRect = getLocalBounds();
    setOrigin(localRect.left + localRect.width / 2.0f, localRect.top + localRect.height / 2.0f);
    setPosition(sf::Vector2f(wdw.getSize().x/2.0f, wdw.getSize().y/2.0f));
    setOutlineColor(sf::Color::Blue);
    setOutlineThickness(10.0f);
    setFillColor(sf::Color::Black);

    sf::FloatRect globalRect = getGlobalBounds();
    float windowTop = globalRect.top;
    float windowMiddle = globalRect.left + localRect.width / 2.0f;

    // create the buttons

    for (int i = 0; i < numButtons; i++)
    {
        buttons[i] = new Button(buttonSize, sf::Vector2f(windowMiddle, windowTop + (i + 1.5f) *  buttonOffset), buttonLabels[i], font, textSize);
    }

    msgText.setFillColor(sf::Color::Cyan);
    sf::FloatRect textRect = msgText.getLocalBounds();
    msgText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    msgText.setPosition(sf::Vector2f(windowMiddle, windowTop + (numButtons + 2.0f) *  buttonOffset));
}

void ButtonBox::draw()
{
    window.draw(*this);
    for (int i = 0; i < numButtons; i++)
        buttons[i]->draw(window);
    window.draw(msgText);
}

