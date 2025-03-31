#include "Rainbow.h"
#include <cmath>


const sf::Color Rainbow::Color[7] = {Red, Orange, Yellow, Green, Blue, Indigo, Violet};


Rainbow::Rainbow(sf::RenderWindow& wnd) : Game(wnd, 5, 7)
{
    setup();
}

void Rainbow::setup()
{
    int tileRows = 7;
    int tileCols = 11;

    float tileWidth = 60.0f;
    ball[0] = new Ball(9.0f, 700.f);  // radius = 9, speed = 700.f
    ball[0]->setFillColor(Color[currentColorNumber]);
    tiles = new Tiles(tileRows, tileCols, tileWidth, 16.0f, tileWidth);      // 8 rows, 12 columns, tile size 60x16
    numTiles = tileRows * tileCols;
    paddle = new Paddle(64.f);
    paddle->setFillColor(Color[currentColorNumber]);
    Tile* tile;
    sf::Vector2f tilePos;
    for (int row = 0; row < tileRows; row++)
    {
        for (int col = 0; col < tileCols; col++)
        {
            tile = tiles->getTile(row, col);
            tile->setFillColor(RainbowColor[6 - row]);
            tilePos = tile->getPosition();
            if (row % 2) tilePos.x -= tileWidth / 4.f;
            else tilePos.x -= 3.f * tileWidth / 4.f;
            tile->setPosition(tilePos);
        }
    }
}

void Rainbow::decrementColor()
{
    currentColorNumber--;
    ball[0]->setFillColor(Color[currentColorNumber]);
    paddle->setFillColor(Color[currentColorNumber]);
}

int Rainbow::getColorIndex(sf::Color color_)
{
    for (int i = 0; i < 7; i++)
        if (color_ == Color[i]) return i;
    return -1;
}
