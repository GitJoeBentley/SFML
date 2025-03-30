#include "Tiles.h"
#include "constants.h"
#include <iostream>

Tiles::Tiles(int rows, int cols, float width, float height, float offset) : numRows(rows), numCols(cols), array(new Tile**[rows])
{
    sf::Vector2f location;
    for (int row = 0; row < numRows; row++)
    {
        array[row] = new Tile*[numCols];
        for (int col = 0; col < numCols; col++)
        {
            array[row][col] = new Tile(width, height);
            location = sf::Vector2f(GameBorderWidth + offset + width / 2 + col * width, TopEdge + GameBorderWidth + row * height);
            array[row][col]->setLocation(location);
        }
    }
}

Tiles::~Tiles()
{
    for (int row = 0; row < numRows; row++)  // draw tiles
    {
        for (int col = 0; col < numCols; col++)
        {
            if (array[row][col])
            {
                delete array[row][col];
                array[row][col] = nullptr;
            }
        }
        delete [] array[row];
    }
    delete [] array;
    array = nullptr;
}

Tile* Tiles::getTile(unsigned row, unsigned col) const
{
    return array[row][col];
}

void Tiles::removeTile(unsigned row, unsigned col)
{
    delete array[row][col];
    array[row][col] = nullptr;
}

int Tiles::getNumRows() const
{
    return numRows;
}
int Tiles::getNumCols() const
{
    return numCols;
}

void Tiles::draw(sf::RenderWindow& window)
{
    for (int row = 0; row < numRows; row++)  // draw tiles
    {
        for (int col = 0; col < numCols; col++)
        {
            if (array[row][col]) window.draw(*(array[row][col]));
        }
    }
}
