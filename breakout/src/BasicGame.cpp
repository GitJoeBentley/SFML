#include <cstdint>
#include "BasicGame.h"

BasicGame::BasicGame(sf::RenderWindow& wnd) : Game(wnd, 1, 8, 80)
{
    setup();
}

void BasicGame::setup()
{
    int tileRows = 8;
    int tileCols = 10;
    numTiles = tileRows * tileCols;
    float tileWidth = 60.0f;
    float tileOffset = 60.0f;
    uint8_t redcolor = 0;
    uint8_t greencolor = 0;
    uint8_t bluecolor = UINT8_MAX;
    ball[0] = new Ball(9.0f, 600.f);  // radius = 9, speed = 600.f
    paddle = new Paddle;

    tiles = new Tiles(tileRows, tileCols, tileWidth, 16.0f, tileOffset);      // 8 rows, 12 columns, tile size 60x16

    for (int row = 0; row < tileRows; row++)
    {
        redcolor += UINT8_MAX / tileRows;
        for (int col = 0; col < tileCols; col++)
        {
            bluecolor -= static_cast<uint8_t>(1);
            tiles->getTile(row, col)->setFillColor(sf::Color(redcolor,greencolor,bluecolor));
        }
    }
}

int BasicGame::processHitTile(Tile* ptrTile, int)
{
    tiles->removeTile(ptrTile);
    numTiles--;
    return 1;
}
