#ifndef BASICGAME_H
#define BASICGAME_H

#include "Game.h"


class BasicGame : public Game
{
    public:
        BasicGame(sf::RenderWindow& wnd);
        void setup();
};

#endif // BASICGAME_H
