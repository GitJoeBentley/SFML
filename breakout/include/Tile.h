#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "constants.h"

class Tile : public sf::RectangleShape
{
public:
    Tile(float width, float height);
    float top() const;
    float bottom() const;
    float left() const;
    float right() const;
    void setLocation(sf::Vector2f loc);
};

#endif // TILE_H
