#include "Tiles150.h"

const sf::Color Tiles150::Color[7] = { Red, Orange, Yellow, Green, Blue};

Tiles150::Tiles150(sf::RenderWindow& wnd) : Game(wnd, 9, 7, 75)
{
    setup();
}

void Tiles150::setup()
{
    int tileRows = 12;
    int tileCols = 10;  // There will never be more than 120 tiles up
    ball[0] = new Ball(9.0f, 500.f);  // radius = 9, speed = 500.f
    paddle = new Paddle;
    tiles = new Tiles(tileRows, tileCols);
    numTiles = tileRows * tileCols;
    float x, y;
    Tile* tilePtr;
    int tileType;

    for (int row = 0; row < tileRows; row++)
    {
        for (int col = 0; col < tileCols; col++)
        {
            tilePtr = tiles->getTile(row, col);
            tilePtr->setPosition(randomTilePosition());
            tileType = col / 2 % 5;
            tilePtr->setFillColor(Color[tileType]);
            // set the tile size
            x = static_cast<float>(48 + 6 * col);
            y = static_cast<float>(12 + 2 * col);
            tilePtr->setSize(sf::Vector2f(x,y));
            tilePtr->setOutlineThickness(2.0f);
            tilePtr->setOutlineColor(sf::Color::Magenta);
        }
    }
}

sf::Vector2f Tiles150::randomTilePosition()
{
    return sf::Vector2f(static_cast<float>(rand()% 620 + 50), static_cast<float>(rand()% 390 + 40));
}

int Tiles150::getColorIndex(sf::Color color_)
{
    for (int i = 0; i < 7; i++)
        if (color_ == Color[i]) return i;
    return -1;
}


int Tiles150::processHitTile(Tile* ptrTile, int)
{
    int index = getColorIndex(ptrTile->getFillColor());
    int tileValue;
    tileValue = 5 - index;
    // if the color is red (index = 0) and more than 30 tiles, create another one
    if (index == 0 and numTiles > 30)
    {
        ptrTile->setPosition(Tiles150::randomTilePosition());
    }
    else
    {
        tiles->removeTile(ptrTile);
    }
    numTiles--;
    return tileValue;
}

