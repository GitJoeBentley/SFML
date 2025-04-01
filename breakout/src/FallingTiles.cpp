#include "FallingTiles.h"

FallingTiles::FallingTiles(sf::RenderWindow& wnd) : Game(wnd, 8)
{
    setup();
}

void FallingTiles::setup()
{
    sf::Color color[3] = { Red, Green, Blue };
    int tileRows = 8;
    int tileCols = 10;
    float tileWidth = 60.0f;
    paddle = new Paddle(64.f);
    ball[0] = new Ball(9.0f, 600.f);  // radius = 9, speed = 600.f
    tiles = new Tiles(tileRows, tileCols, tileWidth, 16.0f, tileWidth);      // 8 rows, 12 columns, tile size 60x16
    numTiles = tileRows * tileCols;

    int counter = 0;

    for (int row = 0; row < tileRows; row++)
    {
        for (int col = 0; col < tileCols; col++)
        {
            counter++;
            tiles->getTile(row, col)->setFillColor(color[counter%3]);
        }
    }
}

std::vector<Tile*>& FallingTiles::getFillingTiles()
{
    return fallingTiles;
}

void FallingTiles::insert(Tile* ptrTile)
{
    for (auto it = fallingTiles.begin(); it != fallingTiles.end(); ++it)
    {
        if (*it == ptrTile)
        {
            return;
        }
    }
    ptrTile->setFillColor(Yellow);
    sf::Vector2f size = ptrTile->getSize();
    size.x-=8.f;
    size.y-=4.f;
    ptrTile->setSize(size);
    auto lb = ptrTile->getLocalBounds();
    ptrTile->setOrigin(lb.width/2.0f,lb.height / 2.0f);
    fallingTiles.push_back(ptrTile);
}

void FallingTiles::fall()
{
    if (fallingTiles.size() == 0)
        return;
    size_t index = rand() % fallingTiles.size();
    Tile* ptrTile = fallingTiles[index];
    sf::Vector2f pos = ptrTile->getPosition();
    pos.y += static_cast<float>(rand() % 29);
    ptrTile->setPosition(pos);
}

void FallingTiles::findTileToFall()
{
    Tile* ptrTile;
    int col = rand() % tiles->getNumCols();
    // find the lowest tile in the col
    for (int i = tiles->getNumRows()-1; i > -1; i--)
    {
        ptrTile = tiles->getTile(i, col);
        if (ptrTile)
        {
            insert(ptrTile);
            break;
        }
    }
}

std::vector<Tile*>::iterator FallingTiles::findTile(Tile* ptrTile)
{
    std::vector<Tile*>::iterator it;
    for (it = fallingTiles.begin(); it != fallingTiles.end(); ++it)
    {
        if (*it == ptrTile)
        {
            return it;
        }
    }
    return fallingTiles.end();
}

bool FallingTiles::tileHitsPaddle(const sf::RectangleShape* paddle) const
{
    sf::FloatRect paddleRect = paddle->getGlobalBounds();
    sf::FloatRect tileRect;
    for (std::vector<Tile*>::const_iterator cit = fallingTiles.cbegin(); cit != fallingTiles.cend(); ++cit)
    {
        tileRect = (*cit)->getGlobalBounds();
        if (tileRect.intersects(paddleRect)) return true;
    }
    return false;
}

bool FallingTiles::tileGetsPassedThePaddle(const sf::RectangleShape* paddle)
{
    float tileHeight;
    float paddleHeight = paddle->getPosition().y;
    Tile* ptrTile;
    std::vector<Tile*>::iterator it;
    for (it = fallingTiles.begin(); it != fallingTiles.end(); ++it)
    {
        ptrTile = *(it);
        tileHeight = ptrTile->getPosition().y;
        if (tileHeight > paddleHeight)
        {
            tiles->removeTile(ptrTile->getRow(), ptrTile-> getCol());
            fallingTiles.erase(it);
            return true;
        }
    }
    return false;
}
