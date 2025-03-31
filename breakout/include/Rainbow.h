#ifndef RAINBOW_H
#define RAINBOW_H

#include "Game.h"

class Rainbow : public Game
{
public:
    static const sf::Color Color[7];
    static int getColorIndex(sf::Color color_);

    Rainbow(sf::RenderWindow& wnd);
    virtual ~Rainbow() = default;
    void setup();
    void decrementColor();
private:
    int currentColorNumber = 6;
};

#endif // RAINBOW_H
