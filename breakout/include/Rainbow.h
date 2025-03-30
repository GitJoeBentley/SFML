#ifndef RAINBOW_H
#define RAINBOW_H

#include "Game.h"

class Rainbow : public Game
{
public:
    static const sf::Color Color[7];
    Rainbow(sf::RenderWindow& wnd);
    virtual ~Rainbow() = default;
    void setup();
    void decrementColor();
    int hitATile(int ballNo = 0);
private:
    int currentColorNumber = 6;
    int getColorIndex(sf::Color color_) const;
};

#endif // RAINBOW_H
