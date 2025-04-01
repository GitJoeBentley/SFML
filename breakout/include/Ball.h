#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Tiles.h"


class Ball : public sf::CircleShape
{
public:
    enum class Direction : int {Up, Down};
    Ball(float ballradius, float ballspeed = 500.0f, Direction dir = Direction::Up, float ang = static_cast<float>(rand()%90-45));

    // getters
    float getAngle() const;
    Direction getDirection() const;
    float getSpeed() const;
    bool getActive() const;
    float bottom() const;
    float top() const;
    float right() const;
    float left() const;

    void setDirection(Direction dir);
    void setAngle(float ang);
    void setSpeed(float speed_);
    void speedUp (float pctIncrease = 5.0f);
    void move();
    void moveToStartPosition();
    bool hitTheWall();
    bool hitATile(Tiles& tiles);
    void update(sf::Time dt);
    void moveDown(float distance = 1.0f);
    void moveUp(float distance = 1.0f);
    void moveLeft(float distance = 1.0f);
    void moveRight(float distance = 1.0f);
    void setActive(bool activeStatus = true);

private:
    float speed;
    Direction direction;
    float angle;
    bool active = true;
};

#endif // BALL_H
