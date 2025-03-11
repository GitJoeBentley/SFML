#ifndef PADDLE_H
#define PADDLE_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Ball.h"

extern const float WallWidth;


class Paddle : public sf::Sprite
{
public:
    enum Direction {Right, Left, Stopped};
    Paddle();

    void move(Direction dir);
    void stop();
    void move(Direction dir, float distance);
    void moveToStartPosition();
    bool hitTheBall(Ball&);
    sf::Vector2f size() const;
    void update(sf::Time dt);

private:
    sf::Texture texture;
    Direction direction;
};

#endif // PADDLE_H
