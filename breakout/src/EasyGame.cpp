#include <cstdint>
#include "EasyGame.h"

EasyGame::EasyGame(sf::RenderWindow& wnd): Game(wnd, 0)
{
    setup();
}

void EasyGame::setup()
{
    int tileRows = 6;
    int tileCols = 8;
    numTiles = tileRows * tileCols;
    uint8_t redcolor = 0;
    uint8_t greencolor = UINT8_MAX;
    uint8_t bluecolor = 0;
    float tileWidth = 72.0f;
    float tileOffset = 72.0f;
    ball[0] = new Ball(10.0f);  // radius = 10, speed = 500
    paddle = new Paddle(80.0f);    // paddle width = 80
    tiles = new Tiles(tileRows, tileCols, tileWidth, 24.0f, tileOffset);      // 6 rows, 8 columns, tile size 72x24

    for (int row = 0; row < tileRows; row++)
    {
        redcolor += UINT8_MAX / tileRows;
        for (int col = 0; col < tileCols; col++)
        {
            greencolor -= static_cast<uint8_t>(3);
            tiles->getTile(row, col)->setFillColor(sf::Color(redcolor,greencolor,bluecolor));
        }
    }
}
