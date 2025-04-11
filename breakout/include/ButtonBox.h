#ifndef BUTTONBOX_H
#define BUTTONBOX_H
#include <SFML/Graphics.hpp>
#include <string>
#include "Button.h"

class ButtonBox : sf::RectangleShape
{
public:
    ButtonBox(sf::RenderWindow& wdw, std::vector<std::string> buttonLabels, sf::Font& font, unsigned textSize = 20u);
    ~ButtonBox() = default;

    // getters
    sf::Vector2f getBoxSize() const;
    Button** getButtons() const;
    Button* getButton(int index) const;
    sf::Vector2f getUpperLeftCorner() const;
    void draw();

private:
    sf::RenderWindow& window;
    int numButtons;
    Button** buttons;
    //sf::Text msgText;
};

#endif // BUTTONBOX_H
