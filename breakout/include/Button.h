#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include "constants.h"

class Button : public sf::RectangleShape
{
public:
    Button(sf::Vector2f buttonSize, sf::Vector2f pos, const std::string& text, sf::Font& font, unsigned int textSize);
    ~Button() = default;
    void highlight();
    void normal();
    void draw(sf::RenderWindow& window);
    void setColor(sf::Color buttColor, sf::Color textColor);
private:
    sf::Text text;
    sf::Color color = Blue;
    sf::Color highlightedColor = LightGreen;
};

#endif // BUTTON_H
