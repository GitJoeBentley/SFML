#include <cmath>
#include <cstdint>
#include <iostream>
#include "TwoBalls.h"

TwoBalls::TwoBalls(sf::RenderWindow& wnd) : Game(wnd, 7)
{
    setup();
}

void TwoBalls::setup()
{
    int tileRows = 12;
    int tileCols = 12;
    float tileWidth = 60.0f;
    float tileHeight = 16.0f;
    ball[0] = new Ball(9.0f, 500.f);  // radius = 9, speed = 500.f
    ball[1] = new Ball(9.0, 250.f, Ball::Direction::Up, 45.f);
    tiles = new Tiles(tileRows, tileCols, tileWidth);      // 8 rows, 12 columns, tile size 60x16
    numTiles = tileRows * tileCols;
    paddle = new Paddle(64.f);
    uint8_t redcolor = 0;
    uint8_t greencolor = 0;
    uint8_t bluecolor = UINT8_MAX;
    for (int row = 0; row < tileRows; row++)
    {
        greencolor += UINT8_MAX / tileRows;
        for (int col = 0; col < tileCols; col++)
        {
            bluecolor -= static_cast<uint8_t>(1);
            tiles->getTile(row, col)->setFillColor(sf::Color(redcolor,greencolor,bluecolor));
        }
    }

    ball[1]->setPosition(tiles->getTile(tileRows/2, tileCols/2)->getPosition());
    ball[1]->setFillColor(sf::Color::Cyan);
    ball[1]->setActive(false);

    for (int row = 4; row < 8; row++)
    {
        for (int col = 4; col < 8; col++)
        {
            tiles->removeTile(row, col);
        }
    }
    innerRect = sf::FloatRect(GameBorderWidth + 4.f * tileWidth, TopEdge + GameBorderWidth + 4.f * tileHeight, 4.f * tileWidth, 4.f * tileHeight);
}

int TwoBalls::processHitTile(Tile* ptrTile, int ballNo)
{
    int tileValue;
    if (ballNo == 1 and ball2Status == Ball2Status::Active)
    {
        tiles->removeTile(ptrTile);
        numTiles--;
        tileValue = 2;
    }
    if (ballNo == 1 and ball2Status == Ball2Status::Inactive)  // Two Balls
    {
        tileValue = -1;
    }
    if (ballNo == 0)
    {
        tiles->removeTile(ptrTile);
        numTiles--;
        tileValue = 1;
    }
    return tileValue;
}

void TwoBalls::update(sf::Time dt)
{
    paddle->update(dt);
    ball[0]->update(dt);
    updateBall2(dt);
}
