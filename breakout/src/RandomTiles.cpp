#include "RandomTiles.h"
#include "constants.h"
#include "proto.h"

RandomTiles::RandomTiles(sf::RenderWindow& wnd) : Game(wnd, 6, 7, 70)
{
    setup();
}

void RandomTiles::setup()
{
    int tileRows = 9;
    int tileCols = 16;
    float tileWidth = 48.0f;
    ball[0] = new Ball(9.0f, 600.0f);  // radius = 9, speed = 600
    tiles = new Tiles(tileRows, tileCols, tileWidth);      // 10 rows, 15 columns, tile size 48x16
    numTiles = tileRows * tileCols;
    paddle = new Paddle;   // paddle width = 64
    sf::Vector2f tilePos;
    sf::Vector2f tileSize;
    for (int row = 0; row < tileRows; row++)
    {
        if (row % 2)
        {
            for (int col = 0; col < tileCols -1; col++)
            {
                tiles->getTile(row, col)->setFillColor(RainbowColor[rand() % 7]);
            }
            tiles->removeTile(row,tileCols -1);
        }
        else
        {
            for (int col = 0; col < tileCols; col++)
            {
                tiles->getTile(row, col)->setFillColor(RainbowColor[rand() % 7]);
                tilePos = tiles->getTile(row, col)->getPosition();
                tilePos.x -= tileWidth / 2.f;
                tiles->getTile(row, col)->setPosition(tilePos);

            }
            tileSize = tiles->getTile(row, 0)->getSize();
            tileSize.x = tileWidth / 2.0f - 2.0f;
            tiles->getTile(row, 0)-> setSize(tileSize);
            tiles->getTile(row, tileCols -1)-> setSize(tileSize);
            tilePos = tiles->getTile(row, 0)->getPosition();
            tilePos.x += tileWidth / 2.f;
            tiles->getTile(row, 0)->setPosition(tilePos);
        }
    }
}


int RandomTiles::processHitTile(Tile* ptrTile, int)
{
    sf::Vector2f curPos = ball[0]->getPosition();
    int shift;
    int colorIndex = getColorIndex(ptrTile->getFillColor());
    switch (colorIndex)
    {
    case 0:
        ball[0]->setSpeed(1.1f * ball[0]->getSpeed());
        break;
    case 1:
        ball[0]->setSpeed(0.9f * ball[0]->getSpeed());
        break;
    case 2:
        paddle->setWidth(1.1f * paddle-> getWidth());
        break;
    case 3:
        paddle->setWidth(0.9f * paddle-> getWidth());
        break;
    case 4:
        ball[0]->setFillColor(sf::Color::Black);
        LoopCounter = 1000 + rand()%1000;
        break;
    case 5:

        shift = rand() % 50 + 50;
        shift = (rand()%2) ? (-shift) : shift;
        curPos.x = curPos.x + static_cast<float>(shift);
        curPos.y = curPos.y + 16.0f;
        ball[0]->setPosition(curPos);
        break;
    case 6:
        ball[0]->setAngle(rand() % 150 - 75.f);
        ball[0]->setSpeed(1.05f * ball[0]->getSpeed());
        break;
    default:
        colorIndex = 0;
    }
    tiles->removeTile(ptrTile);
    numTiles--;
    return colorIndex;
}

