#include <cmath>
#include <iostream>
#include "Paddle.h"
#include "constants.h"

Paddle::Paddle(const float& width)
    : sf::RectangleShape(sf::Vector2f(width, 16.0f)), direction(Stopped)
{
    setOrigin(getLocalBounds().width/2.0f,getLocalBounds().height / 2.0f);
    moveToStartPosition();
}

void Paddle::moveToStartPosition()
{
    setPosition(PaddleStartPosition);
}

void Paddle::move(Direction dir)
{
    direction = dir;
}

void Paddle::stop()
{
    direction = Stopped;
}

void Paddle::update(sf::Time dt)
{
    sf::Vector2f newPosition(getPosition());
    if (direction == Left)
    {
        newPosition.x -= PaddleSpeed * dt.asSeconds();
    }
    if (direction == Right)
    {
        newPosition.x += PaddleSpeed * dt.asSeconds();
    }
    setPosition(newPosition);
}

void Paddle::move(Direction dir, float distance)
{
    sf::Vector2f newPosition(getPosition());
    if (dir == Right)
        newPosition.x += distance;
    if (dir == Left)
        newPosition.x -= distance;
    setPosition(newPosition);
}

// TODO (Joe#1#): Adjust Ball bounce angle to the location of the hit on the paddle
bool Paddle::hitTheBall(Ball* ball)
{
    if (ball->getPosition().y > (getPosition().y + ball->getRadius() + getLocalBounds().height/2.f)) return false;

    sf::FloatRect ballPosition = ball->getGlobalBounds();
    sf::FloatRect paddlePosition = getGlobalBounds();

    if (ballPosition.intersects(paddlePosition))
    {
        float adjustment = static_cast<float>(rand() % 9 - 4);
        ball->setAngle(ball->getAngle() + adjustment);
        ball->setDirection(Ball::Direction::Up);
        return true;
    }
    return false;
}
