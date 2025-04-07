#ifndef CRAZYBALL_H
#define CRAZYBALL_H
#include "Game.h"


class CrazyBall: public Game
{
    public:
        CrazyBall(sf::RenderWindow& wnd);
        void setup();
        void changeSpeed(int arg);
        void update(sf::Time dt);
        int processHitTile(Tile* ptrTile, int ballNo = 0);
};

#endif // CRAZYBALL_H
