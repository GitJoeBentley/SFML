#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "constants.h"

class Tile : public sf::RectangleShape
{
public:
    Tile(int row_, int col_, float width, float height);
    float top() const;
    float bottom() const;
    float left() const;
    float right() const;
    void setLocation(sf::Vector2f loc);
    int getRow() const;
    int getCol() const;
private:
    int row;
    int col;
};

#endif // TILE_H
