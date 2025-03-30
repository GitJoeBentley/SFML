#ifndef TWOBALLS_H
#define TWOBALLS_H
#include "Game.h"


class TwoBalls : public Game

{
public:


    TwoBalls(sf::RenderWindow& wnd);
    virtual ~TwoBalls() = default;
    void setup();
private:

};

#endif // TWOBALLS_H
