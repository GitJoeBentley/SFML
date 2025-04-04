#include "OneRedTile.h"

// Allot 5 balls and 60 seconds
OneRedTile::OneRedTile(sf::RenderWindow& wnd) : Game(wnd, 2, 5, 60)
{
    setup();
}

OneRedTile::~OneRedTile()
{
    //dtor
}

void OneRedTile::setup()
{
    int tileRows = 7;
    int tileCols = 15;
    float tileWidth = 48.0f;
    ball[0] = new Ball(9.0f, 600.f);  // radius = 9, speed = 600
    tiles = new Tiles(tileRows, tileCols, tileWidth);      // 7 rows, 15 columns, tile size 48x16
    numTiles = tileRows * tileCols;
    paddle = new Paddle;   // paddle width = 64
    for (int row = 0; row < tileRows; row++)
    {
        for (int col = 0; col < tileCols; col++)
        {
            tiles->getTile(row, col)->setFillColor(sf::Color(0,255,row*40));
        }
    }
    tiles->getTile(tileRows/2, tileCols/2)->setFillColor(sf::Color::Red);
}
