#ifndef BUTTONBOX_H
#define BUTTONBOX_H
#include <SFML/Graphics.hpp>
#include <string>
#include "Button.h"

class ButtonBox : sf::RectangleShape
{
    public:
        ButtonBox(sf::RenderWindow& wdw, std::vector<std::string> buttonLabels, const std::string& message, sf::Font& font, unsigned textSize = 20u);
        ~ButtonBox() = default;
        void draw();
        sf::Vector2f getBoxSize() const { return getSize(); }
        Button** getButtons() { return buttons; }
        Button* getButton(int index) { return buttons[index]; }

    private:
        sf::RenderWindow& window;
        int numButtons;
        Button** buttons;
        sf::Text msgText;
};

#endif // BUTTONBOX_H
