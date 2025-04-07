#ifndef RANDOMTILES_H
#define RANDOMTILES_H
#include "Game.h"

class RandomTiles : public Game
{
public:
    RandomTiles(sf::RenderWindow& wnd);

    // virtual functions
    virtual ~RandomTiles() = default;
    void setup();
    int processHitTile(Tile* ptrTile, int);

    int doRandomTileHit(Tile* tileptr);
};


#endif // RANDOMTILES_H

