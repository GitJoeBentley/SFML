#ifndef PADDLE_H
#define PADDLE_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Ball.h"

// TODO (Joe#1#): Remove tile border ...
//
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
    bool hitTheBall(Ball* ptrBall);
    //sf::Vector2f size() const;
    void update(sf::Time dt);

private:
    //sf::Texture texture;
    Direction direction;
};

#endif // PADDLE_H
