#ifndef BASICGAME_H
#define BASICGAME_H

#include "Game.h"

class BasicGame : public Game
{
    public:
        BasicGame(sf::RenderWindow& wnd);
        virtual ~BasicGame() = default;
        void setup();
};

#endif // BASICGAME_H
