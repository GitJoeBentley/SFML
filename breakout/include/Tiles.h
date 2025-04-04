#ifndef TILES_H
#define TILES_H

#include <string>
#include "Tile.h"
#include <SFML/Graphics.hpp>


class Tiles
{
public:
    Tiles(int rows, int cols, float tilewidth = 64.0f, float tileheight = 16.0f, float offset = 0.0f);
    virtual ~Tiles();
    // const Tile& getTile(unsigned row, unsigned col) const;
    Tile* getTile(unsigned row, unsigned col) const;
    float getBottomEdge();
    void draw(sf::RenderWindow& window);
    int getNumRows() const;
    int getNumCols() const;
    void removeTile(unsigned row, unsigned col);
private:
    int numRows;
    int numCols;
    Tile*** array;
};

#endif // TILES_H
