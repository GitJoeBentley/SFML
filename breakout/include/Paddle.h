#ifndef PADDLE_H
#define PADDLE_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Ball.h"

extern const float WallWidth;


class Paddle : public sf::RectangleShape
{
public:
    enum Direction {Right, Left, Stopped};
    Paddle(const float& width);

    void move(Direction dir);
    void stop();
    void move(Direction dir, float distance);
    void moveToStartPosition();
    float topOfPaddle() const;
    void update(sf::Time dt);
    float leftSide() const;
    float rightSide() const;
    void setWidth(float width) { setSize(sf::Vector2f(width, getSize().y)); }
    float getWidth() const { return getSize().x; }

private:
    Direction direction;
};

#endif // PADDLE_H
