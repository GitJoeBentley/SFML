#include <cstdint>
#include "Crusher.h"

Crusher::Crusher(sf::RenderWindow& wnd) : Game(wnd, 4, 10, INT_MAX)
{
    setup();
}

void Crusher::setup()
{
    int tileRows = 10;
    int tileCols = 15;
    float tileWidth = 48.0f;
    ball[0] = new Ball(9.0f, 600.f);  // radius = 9, speed = 600
    tiles = new Tiles(tileRows, tileCols, tileWidth);      // 10 rows, 15 columns, tile size 48x16
    numTiles = tileRows * tileCols;
    paddle = new Paddle(64.0f);   // paddle width = 64
    uint8_t redcolor = 255;
    uint8_t greencolor = 255;
    uint8_t bluecolor = 0;

    for (int row = 0; row < tileRows; row++)
    {
        for (int col = 0; col < tileCols; col++)
        {
            tiles->getTile(row, col)->setFillColor(sf::Color(redcolor, greencolor, bluecolor));
        }
        redcolor -= 25;
    }
}

void Crusher::crush()
{
    sf::Vector2f currentPos;
    for (int row = 0; row < tiles->getNumRows(); row++)
    {
        for (int col = 0; col < tiles->getNumCols(); col++)
        {
            if (tiles->getTile(row, col))
            {
                currentPos = tiles->getTile(row, col)->getPosition();
                currentPos.y += 25;
                tiles->getTile(row, col)->setPosition(currentPos);
            }
        }
    }
    // speed the ball up by 3%
    ball[0]->speedUp(3.f);
}
