#include "BasicGame.h"
#include "Game.h"

BasicGame::BasicGame(sf::RenderWindow& wnd) : Game(wnd, "Basic Game", 5, 600.0f)
{
    setup();
}

void BasicGame::setup()
{
    int tileRows = 8;
    int tileCols = 10;
    float tileWidth = 60.0f;
    //ball = new Ball(9.0f, 800.f);  // radius = 9, speed = 800.f
    ball = new Ball(9.0f, 600.f);  // radius = 9, speed = 800.f
    tiles = new Tiles(tileRows, tileCols, tileWidth, 16.0f, tileWidth);      // 8 rows, 12 columns, tile size 60x16
    numTiles = tileRows * tileCols;
    paddle = new Paddle(64.f);
    uint8_t redcolor = 0;
    uint8_t greencolor = 0;
    uint8_t bluecolor = UINT8_MAX;
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
