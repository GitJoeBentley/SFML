#ifndef TILES150_H
#define TILES150_H

#include "Game.h"


class Tiles150 : public Game

{
public:
    static const sf::Color Color[7];
    static int getColorIndex(sf::Color color_);
    static sf::Vector2f randomTilePosition();
    Tiles150(sf::RenderWindow& wnd);
    virtual ~Tiles150() = default;
    void setup();
};

#endif // TILES150_H
