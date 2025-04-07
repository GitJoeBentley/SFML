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

    // getters
    int getNumRows() const;
    int getNumCols() const;
    Tile* getTile(unsigned row, unsigned col) const;

    void removeTile(unsigned row, unsigned col);
    void removeTile(Tile* ptrTile);
    void draw(sf::RenderWindow& window);

private:
    int numRows;
    int numCols;
    Tile*** array;
};

#endif // TILES_H
