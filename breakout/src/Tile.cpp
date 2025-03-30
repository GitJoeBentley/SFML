#include "Tile.h"

Tile::Tile(float width, float height) : RectangleShape(sf::Vector2f(width -2.f, height - 2.f))
{
    setOrigin(getLocalBounds().width/2.0f,getLocalBounds().height / 2.0f);
}

void Tile::setLocation(sf::Vector2f loc)
{
    setPosition(loc);
}

float Tile::top() const
{
    return getPosition().y - getSize().y / 2.0f;
}

float Tile::bottom() const
{
    return getPosition().y + getSize().y / 2.0f;
}

float Tile::left() const
{
    return getPosition().x - getSize().x / 2.0f;
}

float Tile::right() const
{
    return getPosition().x + getSize().x / 2.0f;
}
