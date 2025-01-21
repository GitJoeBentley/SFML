#include "Wall.h"
#include "Constants.h"

Wall::Wall(Type type_, int col, int row) : sf::RectangleShape(CellSize), type(type_)
{
    setPosition(sf::Vector2f(WindowHorizontalOffset + col * CellWidth, WindowVerticalOffset + row * CellWidth));
    if (type == Rubber) setFillColor(sf::Color::Magenta);
    else
    {
        updateColor();
    }
}

Wall::~Wall()
{
    //dtor
}

Wall& Wall::operator--()
{
    if (type == Soft) type = None;
    if (type == Medium) type = Soft;
    if (type == Hard) type = Medium;
    return *this;
}

sf::Color Wall::color() const
{
    if (type == Rubber) return sf::Color::Magenta;
    sf::Uint8 shade = (4 - type) * 255;
    return sf::Color(shade, shade, shade);
}

void Wall::updateColor()
{
    int shade = static_cast<int>((4 - type) / 4.0f * 255);
    if (shade >= 0) setFillColor(sf::Color(shade, shade, shade));
}
