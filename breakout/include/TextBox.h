#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <SFML/Graphics.hpp>
#include <string>

class TextBox : sf::RectangleShape
{
    public:
        TextBox(const std::string& textStr, sf::Font& font, unsigned int textSize, sf::Color color, sf::Vector2f pos);
        ~TextBox() = default;
        void drawTB(sf::RenderWindow& window);
    private:
        const std::string textStr;
        sf::Text text;
};

#endif // TEXTBOX_H
