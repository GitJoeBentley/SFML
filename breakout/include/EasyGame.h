#ifndef EASYGAME_H
#define EASYGAME_H
#include "Game.h"

class EasyGame: public Game
{
    public:
        EasyGame(sf::RenderWindow& wnd);
        ~EasyGame() = default;
        void setup();
};

#endif // EASYGAME_H
