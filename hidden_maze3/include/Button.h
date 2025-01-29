#ifndef BUTTON_H
#define BUTTON_H

//#include <SFML/Graphics.hpp>
#include <string>
#include "Message.h"


class Button : public Message
{
public:
    Button(std::string text, sf::Color color, sf::Color highlighted, sf::Vector2f position = MidWindow);
    ~Button() = default;
    void highlight();
    void normal();

private:
    sf::Color color;
    sf::Color highlightedColor;
};

#endif // BUTTON_H
