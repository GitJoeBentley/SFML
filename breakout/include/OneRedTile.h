#ifndef ONEREDTILE_H
#define ONEREDTILE_H
#include "Game.h"

class OneRedTile : public Game
{
    public:
        OneRedTile(sf::RenderWindow& wnd);

        // virtual functions
        virtual ~OneRedTile() = default;
        void setup();
        int processHitTile(Tile* ptrTile, int = 0);
};

#endif // ONEREDTILE_H
