#ifndef TWOBALLS_H
#define TWOBALLS_H
#include "Game.h"


class TwoBalls : public Game
{
public:
    TwoBalls(sf::RenderWindow& wnd);

    // Virtual functions
    virtual ~TwoBalls() = default;
    void setup();
    void update(sf::Time dt);
    int processHitTile(Tile* ptrTile, int ballNo = 0);
};

#endif // TWOBALLS_H
