#include "FallingTiles.h"

FallingTiles::FallingTiles(sf::RenderWindow& wnd) : Game(wnd, 8, 8, 80)
{
    setup();
}

void FallingTiles::setup()
{
    sf::Color color[3] = { Red, Green, Blue };
    int counter = 0;
    int tileRows = 8;
    int tileCols = 10;
    numTiles = tileRows * tileCols;
    float tileWidth = 60.0f;
    float tileOffset = 60.0f;
    paddle = new Paddle;
    ball[0] = new Ball(9.0f, 600.f);  // radius = 9, speed = 600.f
    tiles = new Tiles(tileRows, tileCols, tileWidth, 16.0f, tileOffset);      // 8 rows, 12 columns, tile size 60x16

    for (int row = 0; row < tileRows; row++)
    {
        for (int col = 0; col < tileCols; col++)
        {
            counter++;
            tiles->getTile(row, col)->setFillColor(color[counter%3]);
        }
    }
}

void FallingTiles::update(sf::Time dt)
{
    paddle->update(dt);
    ball[0]->update(dt);
    if (rand() % 32767 == 0)
    {
        findTileToFall();
    }
    if (rand() % 1200 == 1)
    {
        fall();
    }
    processTileAtPaddleHeight();
}

int FallingTiles::processHitTile(Tile* ptrTile, int)
{
    int tileValue = 1;
    auto it = findTile(ptrTile);
    if (it != fallingTiles.end())
    {
        fallingTiles.erase(it);

        // Speed the ball up
        ball[0]->speedUp(3);     // 5%
        tileValue = 10;
    }
    tiles->removeTile(ptrTile);
    numTiles--;
    return tileValue;
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

void FallingTiles::processTileAtPaddleHeight()
{
    float tileHeight;
    float paddleHeight = paddle->getPosition().y;
    if (fallingTiles.size() < 1) return;
    for (std::vector<Tile*>::iterator it = fallingTiles.begin(); it != fallingTiles.end(); ++it)
    {
        tileHeight = (*it)->getPosition().y;
        if (tileHeight >= paddleHeight)
        {
            // Did the tile hit the paddle?
            sf::FloatRect paddleRect = paddle->getGlobalBounds();
            sf::FloatRect tileRect = (*it)->getGlobalBounds();
            if (tileRect.intersects(paddleRect)) setStatus(Game::GameStatus::TileHitsPaddle);
            else
            {
                incrementScore(-10);
                tiles->removeTile((*it)->getRow(), (*it)-> getCol());
                fallingTiles.erase(it);
            }
            return;
        }
    }

    return;
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
    // decrease the size of a falling tile
    size.x -= 8.f;
    size.y -= 4.f;
    ptrTile->setSize(size);
    sf::FloatRect rect = ptrTile->getLocalBounds();
    ptrTile->setOrigin(rect.width/2.0f, rect.height / 2.0f);
    fallingTiles.push_back(ptrTile);
}

void FallingTiles::fall()
{
    // If no tiles are falling, bail out
    if (fallingTiles.size() == 0) return;

    // choose a random falling tile to fall
    size_t index = rand() % fallingTiles.size();
    Tile* ptrTile = fallingTiles[index];

    // Move the random falling tile down a random amount
    sf::Vector2f pos = ptrTile->getPosition();
    pos.y += static_cast<float>(rand() % 29);
    ptrTile->setPosition(pos);
}

// Find a random tile at the bottom of a random column
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
