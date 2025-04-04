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
    Paddle(float width = 64.0f);

    void move(Direction dir);
    void stop();
    void move(Direction dir, float distance);
    void moveToStartPosition();

    float top() const;
    void update(sf::Time dt);
    float left() const;
    float right() const;
    void setWidth(float width);
    float getWidth() const;

private:
    Direction direction;
};

#endif // PADDLE_H
