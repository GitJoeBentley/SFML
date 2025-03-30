#ifndef RANDOMTILES_H
#define RANDOMTILES_H
#include "Game.h"

class RandomTiles : public Game
{
public:
    RandomTiles(sf::RenderWindow& wnd);
    virtual ~RandomTiles() = default;
    void setup();
    int doRandomTileHit(Tile* tileptr);
};


#endif // RANDOMTILES_H

