#include "Tile.h"

Tile::Tile(float width, float height) : RectangleShape(sf::Vector2f(width -2.f, height - 2.f))
{
    setOrigin(getLocalBounds().width/2.0f,getLocalBounds().height / 2.0f);
}
