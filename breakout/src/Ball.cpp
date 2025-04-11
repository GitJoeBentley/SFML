#include "constants.h"
#include "Ball.h"
#include <cmath>
#include <iostream>
using namespace std;

Ball::Ball(float ballradius, float ballspeed, Direction dir, float ang)
    : sf::CircleShape(ballradius), speed(ballspeed), direction(dir), angle(ang)
{
    setFillColor(Yellow);
    sf::FloatRect rect = getLocalBounds();
    setOrigin(rect.left + ballradius, rect.top + ballradius);
    moveToStartPosition();
}

// getters
bool Ball::getActive() const
{
    return active;
}

float Ball::getAngle() const
{
    return angle;
}

Ball::Direction Ball::getDirection() const
{
    return direction;
}

float Ball::getSpeed() const
{
    return speed;
}

float Ball::bottom() const
{
    return getPosition().y + getRadius();
}

float Ball::top() const
{
    return getPosition().y - getRadius();
}

float Ball::right() const
{
    return getPosition().x + getRadius();
}

float Ball::left() const
{
    return getPosition().x - getRadius();
}

// setters
void Ball::setDirection(Direction dir)
{
    direction = dir;
}

void Ball::setAngle( float ang)
{
    angle = ang;
}

void Ball::moveToStartPosition()
{
    setPosition(BallStartPosition);
    direction = Direction::Up;
    if (angle != 45) angle = static_cast<float>(rand()%90-45);
}

void Ball::moveDown(float distance)
{
    sf::Vector2f pos = getPosition();
    pos.y += distance;
    setPosition(pos);
}

void Ball::moveUp(float distance)
{
    sf::Vector2f pos = getPosition();
    pos.y -= distance;
    setPosition(pos);
}

void Ball::moveLeft(float distance)
{
    sf::Vector2f pos = getPosition();
    pos.x -= distance;
    setPosition(pos);
}

void Ball::moveRight(float distance)
{
    sf::Vector2f pos = getPosition();
    pos.x += distance;
    setPosition(pos);
}

void Ball::setSpeed( float speed_)
{
    speed = speed_;
}

void Ball::speedUp (float pctIncrease)
{
    speed = speed * (1.f + pctIncrease/100.f);
}

void Ball::setActive(bool activeStatus)
{
    active = activeStatus;
}

bool Ball::hitTheWall()
{
    // Hit the top wall
    if (top() <= GameBorderWidth)
    {
        direction = Direction::Down;
        return true;
    }
    // Hit the right wall
    if (right() >= GameWindowSize.x + GameBorderWidth)
    {
        // move the ball away from the wall
        sf::Vector2f ballPos = getPosition();
        ballPos.x -= 3.0f;
        setPosition(ballPos);
        angle = -angle;
        return true;
    }
    // Hit the left wall
    if (left() <= GameBorderWidth)
    {
        // move the ball away from the wall
        sf::Vector2f ballPos = getPosition();
        ballPos.x += 3.0f;
        setPosition(ballPos);
        angle = -angle;
        return true;
    }
    return false;
}

void Ball::update(sf::Time dt)
{
    const float RPD = 0.0174533f;   // Radians Per Degree
    if (direction == Direction::Up)
    {
        setPosition(sf::Vector2f(getPosition().x + speed * dt.asSeconds() * std::sin(RPD*angle), getPosition().y - speed * dt.asSeconds() *std::cos(RPD*angle)));
    }
    else  // ball direction is down
    {
        setPosition(sf::Vector2f(getPosition().x + speed * dt.asSeconds() * std::sin(RPD*angle), getPosition().y + speed * dt.asSeconds() * std::cos(RPD*angle)));
    }
}

