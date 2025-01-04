#include "Button.h"
#include "Fonts.h"
using namespace std;

Button::Button(std::string text_, sf::Color color_, sf::Color highlighted_, sf::Vector2f position_)
    : Message(text_, Fonts::Arial, 24, position_, sf::Color::Black),
      color(color_),
      highlightedColor(highlighted_)
{
    setSize(sf::Vector2f(200.0f, 64.0f));
    setFillColor(color_);

    sf::FloatRect rect = getLocalBounds();
    setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
    setPosition(position_);
}

void Button::highlight()
{
    setFillColor(highlightedColor);
    setOutlineColor(sf::Color(0x3f48ccff));
    setOutlineThickness(10.0f);
}

void Button::normal()
{
    setFillColor(color);
    setOutlineColor(sf::Color::Blue);
    setOutlineThickness(5.0f);
}
