#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <SFML/Graphics.hpp>
#include <string>

class TextBox : sf::RectangleShape
{
    public:
        TextBox(std::string textStr, sf::Font& font, unsigned int textSize, sf::Color color, sf::Vector2f pos);
        ~TextBox() = default;
        void draw(sf::RenderWindow& window);
    private:
        sf::Text text;
};

#endif // TEXTBOX_H
