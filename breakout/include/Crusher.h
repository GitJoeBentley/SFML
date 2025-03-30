#ifndef CRUSHER_H
#define CRUSHER_H
#include "Game.h"


class Crusher : public Game
{
public:
    Crusher(sf::RenderWindow& wnd);
    virtual ~Crusher() = default;
    void setup();
    void crush();
};

#endif // CRUSHER_H
