#include "OneRedTile.h"

// Allot 5 balls and 60 seconds
OneRedTile::OneRedTile(sf::RenderWindow& wnd) : Game(wnd, "One Red Tile", 5, 64.0f, 60)
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
    ball = new Ball(9.0f, 600.f);  // radius = 9, speed = .1
    tiles = new Tiles(tileRows, tileCols, tileWidth, 16.0f, 0);      // 8 rows, 12 columns, tile size 60x16
    numTiles = tileRows * tileCols;
    paddle = new Paddle(64.0f);   // paddle width = 64
    for (int row = 0; row < tileRows; row++)
    {
        for (int col = 0; col < tileCols; col++)
        {
            tiles->getTile(row, col)->setFillColor(sf::Color(0,255,row*40));
        }
    }
    tiles->getTile(tileRows/2, tileCols/2)->setFillColor(sf::Color::Red);
}

/*int OneRedTile::hitATile()
{
    Tile* tilePtr;
    int returnValue = 1;

    for (int row = tiles->getNumRows() - 1; row >= 0 ; row--)
    {
        for (int col = 0; col < tiles->getNumCols(); col++)
        {
            tilePtr = tiles->getTile(row,col);
            if (!tilePtr) continue;
            if (ball->getGlobalBounds().intersects(tilePtr->getGlobalBounds()))
            {
                if (tiles->getTile(row, col)->getFillColor() == sf::Color::Red) returnValue = 100;
                numTiles--;
                if (ball->getDirection() == Ball::Up && hitBottomOfTile(tilePtr))  // ball hit bottom of tile
                {
                    ball->setDirection(Ball::Down);
                    tiles->removeTile(row, col);
                    return returnValue;
                }
                else if (ball->getDirection() == Ball::Down && hitTopOfTile(tilePtr))  // ball hit top of tile
                {
                    ball->setDirection(Ball::Up);
                    tiles->removeTile(row, col);
                    return returnValue;
                }
                else if (hitLeftSideOfTile(tilePtr))  // ball hit left side of tile
                {
                    ball->setAngle(-(ball->getAngle()));
                    tiles->removeTile(row, col);
                    return returnValue;
                }
                else if (hitRightSideOfTile(tilePtr))  // ball hit right side of tile
                {
                    ball->setAngle(-(ball->getAngle()));
                    // ball->getAngle() = -ball->getAngle();
                    tiles->removeTile(row, col);
                    return returnValue;
                }
                else
                {
                    std::cout << "No collusion" << std::endl;
                }
            }
        }
    }
    return 0;
}*/
