#ifndef CRAZYBALL_H
#define CRAZYBALL_H
#include "Game.h"


class CrazyBall: public Game
{
    public:
        CrazyBall(sf::RenderWindow& wnd);
        void setup();
        void changeSpeed(int arg);
        void doCrazy();
};

#endif // CRAZYBALL_H
