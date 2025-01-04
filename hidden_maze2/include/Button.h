#ifndef BUTTON_H
#define BUTTON_H

//#include <SFML/Graphics.hpp>
#include <string>
#include "Message.h"


//class Button : public sf::RectangleShape
class Button : public Message
{
public:
    Button(std::string text, sf::Color color, sf::Color highlighted, sf::Vector2f position);
    ~Button() = default;
    //void draw(sf::RenderWindow& window);
    void highlight();
    void normal();

private:
    //sf::Text text;
    sf::Color color;
    sf::Color highlightedColor;
    //sf::Vector2f position;
};

#endif // BUTTON_H
