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
    float getAngle() const;
    Direction getDirection() const;
    void setDirection(Direction dir);
    void setAngle( float ang);
    float getSpeed() const { return speed; }
    void setSpeed( float speed_) { speed = speed_; }
    void move();
    void moveToStartPosition();
    bool hitTheWall();
    bool hitATile(Tiles& tiles);
    void update(sf::Time dt);
    void moveDown(float distance = 1.0f)
    {
        sf::Vector2f pos = getPosition();
        pos.y += distance;
        setPosition(pos);
    }
    void moveUp(float distance = 1.0f)
    {
        sf::Vector2f pos = getPosition();
        pos.y -= distance;
        setPosition(pos);
    }
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

    void setActive(bool activeStatus = true) { active = activeStatus; }
    bool getActive() const { return active; }


    float bottom() const;
    float top() const;
    float right() const;
    float left() const;
/*     bool isCloseToATile(const Tile& tile) const;
 *     bool hitBottomOfTile(const Tile& tile) const;
 *     bool hitTopOfTile(const Tile& tile) const;
 *     bool hitLeftSideOfTile(const Tile& tile) const;
 *     bool hitRightSideOfTile(const Tile& tile) const;
 */

private:
    float speed;
    Direction direction;
    float angle;
    bool active = true;
};

#endif // BALL_H
