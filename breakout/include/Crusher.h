#ifndef CRUSHER_H
#define CRUSHER_H
#include "Game.h"

class Crusher : public Game
{
public:
    Crusher(sf::RenderWindow& wnd);

    // Virtual functions
    virtual ~Crusher() = default;
    void setup();
    int processHitTile(Tile* ptrTile, int ballNo = 0);
    void crush();
};

#endif // CRUSHER_H
