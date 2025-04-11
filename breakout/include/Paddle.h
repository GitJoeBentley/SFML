#ifndef PADDLE_H
#define PADDLE_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Ball.h"

//extern const float WallWidth;


class Paddle : public sf::RectangleShape
{
public:
    enum Direction {Right, Left, Stopped};

    Paddle(float width = 64.0f);

    // getters
    float top() const;
    float left() const;
    float right() const;
    float getWidth() const;

    void setWidth(float width);
    void move(Direction dir);
    void move(Direction dir, float distance);
    void moveToStartPosition();
    void stop();
    void update(sf::Time dt);
private:
    Direction direction;
};

#endif // PADDLE_H
