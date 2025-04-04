#include "EasyGame.h"

// TODO (joefo#1#): ball speed is initialized in 2 places

EasyGame::EasyGame(sf::RenderWindow& wnd): Game(wnd, 0)
{
    setup();
}

void EasyGame::setup()
{
    int tileRows = 6;
    int tileCols = 8;
    ball[0] = new Ball(10.0f);  // radius = 10, speed = 500
    float tileWidth = 72.0f;
    tiles = new Tiles(tileRows, tileCols, tileWidth, 24.0f, tileWidth);      // 6 rows, 8 columns, tile size 72x24
    numTiles = tileRows * tileCols;
    paddle = new Paddle(80.0f);    // paddle width = 80
    uint8_t redcolor = 0;
    uint8_t greencolor = UINT8_MAX;
    uint8_t bluecolor = 0;
    for (int row = 0; row < tileRows; row++)
    {
        redcolor += UINT8_MAX / tileRows;
        for (int col = 0; col < tileCols; col++)
        {
            greencolor -= static_cast<uint8_t>(1);
            tiles->getTile(row, col)->setFillColor(sf::Color(redcolor,greencolor,bluecolor));
        }
    }
}
