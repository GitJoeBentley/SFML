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
    enum class Direction {Up, Down};
    Ball(float ballradius, float ballspeed, Direction dir = Direction::Up, float ang = 0.0f);
    float getAngle() const;
    Direction getDirection() const;
    void setDirection(Direction dir);
    void setAngle( float ang);
    void move();
    void moveToStartPosition();
    bool hitTheWall();
    bool hitATile(Tiles& tiles);
    void update(sf::Time dt);
    void moveLeft(float distance = 1.0f)
    {
        sf::Vector2f pos = getPosition();
        pos.x -= distance;
        setPosition(pos);
    }
    void moveRight(float distance = 1.0f)
    {
        sf::Vector2f pos = getPosition();
        pos.x += distance;
        setPosition(pos);
    }
// TODO (Joe#1#): Remove these functions ???

    float bottomOfBall() const;
    float topOfBall() const;
    float rightSideOfBall() const;
    float leftSideOfBall() const;
    bool isCloseToATile(const Tile& tile) const;
    bool hitBottomOfTile(const Tile& tile) const;
    bool hitTopOfTile(const Tile& tile) const;
    bool hitLeftSideOfTile(const Tile& tile) const;
    bool hitRightSideOfTile(const Tile& tile) const;

private:
    float speed;
    Direction direction;
    float angle;
};

#endif // BALL_H
