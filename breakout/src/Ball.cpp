#include "constants.h"
#include "Ball.h"
#include <cmath>
#include <iostream>

Ball::Ball(float ballradius, float ballspeed, Direction dir, float ang)
    : sf::CircleShape(ballradius), speed(ballspeed), direction(dir), angle(ang)
{
    setFillColor(sf::Color::Yellow);
    setOrigin(getLocalBounds().width/2.0f,getLocalBounds().height / 2.0f);
    angle = static_cast<float>(rand()%90-45);
    moveToStartPosition();
}
float Ball::getAngle() const
{
    return angle;
}

Ball::Direction Ball::getDirection() const
{
    return direction;
}

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
    angle = static_cast<float>(rand()%90-45);
}

bool Ball::hitTheWall()
{
    // Hit the top wall
    if (topOfBall() <= GameBorderWidth)
    {
        direction = Direction::Down;
        return true;
    }
    // Hit the right wall
    if (rightSideOfBall() >= GameWindowSize.x + GameBorderWidth)
    {
        angle = -angle;
        return true;
    }
    // Hit the left wall
    if (leftSideOfBall() <= GameBorderWidth)
    {
        angle = -angle;
        return true;
    }
    return false;
}

float Ball::bottomOfBall() const
{
    return getPosition().y + getRadius();
}

float Ball::topOfBall() const
{
    return getPosition().y - getRadius();
}

float Ball::rightSideOfBall() const
{
    return getPosition().x + getRadius();
}

float Ball::leftSideOfBall() const
{
    return getPosition().x - getRadius();
}

void Ball::update(sf::Time dt)
{
    const float RPD = 0.0174533f;   // Radians Per Degree

    if (direction == Direction::Up)
    {
        setPosition(sf::Vector2f(getPosition().x + speed * dt.asSeconds() * std::sin(RPD*angle), getPosition().y - speed * dt.asSeconds() *std::cos(RPD*angle)));
        // exit(1);
    }
    else  // ball direction is down
    {
        setPosition(sf::Vector2f(getPosition().x + speed * dt.asSeconds() * std::sin(RPD*angle), getPosition().y + speed * dt.asSeconds() * std::cos(RPD*angle)));
    }
}
