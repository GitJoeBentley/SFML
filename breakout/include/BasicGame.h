#ifndef BASICGAME_H
#define BASICGAME_H

#include "Game.h"

class BasicGame : public Game
{
    public:
        BasicGame(sf::RenderWindow& wnd);
        virtual ~BasicGame() = default;
        void setup();
        int processHitTile(Tile* ptrTile, int ballNo = 0);
};

#endif // BASICGAME_H
