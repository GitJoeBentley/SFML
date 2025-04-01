#include "Tile.h"

Tile::Tile(int row_, int col_, float width, float height) : RectangleShape(sf::Vector2f(width -2.f, height - 2.f)), row(row_), col(col_)
{
    setOrigin(getLocalBounds().width/2.0f,getLocalBounds().height / 2.0f);
}

int Tile::getRow() const
{
    return row;
}
int Tile::getCol() const
{
    return col;
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
