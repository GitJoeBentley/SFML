#ifndef EASYGAME_H
#define EASYGAME_H
#include "Game.h"

class EasyGame: public Game
{
    public:
        EasyGame(sf::RenderWindow& wnd);

        // Virtual Functions
        ~EasyGame() = default;
        void setup();
        int processHitTile(Tile* ptrTile, int ballNo = 0);
};

#endif // EASYGAME_H
