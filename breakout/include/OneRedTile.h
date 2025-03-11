#ifndef ONEREDTILE_H
#define ONEREDTILE_H
#include "Game.h"

class OneRedTile : public Game
{
    public:
        OneRedTile(sf::RenderWindow& wnd);
        virtual ~OneRedTile();
        void setup();
        //int hitATile() override;
};

#endif // ONEREDTILE_H
