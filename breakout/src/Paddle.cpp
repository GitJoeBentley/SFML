#include <cmath>
#include <iostream>
#include "Paddle.h"
#include "constants.h"
using namespace std;

Paddle::Paddle(const float& width)
    : sf::RectangleShape(sf::Vector2f(width, 16.0f)), direction(Stopped)
{
    sf::FloatRect rect = getLocalBounds();
    setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
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

float Paddle::leftSide() const
{
    sf::Rect rect = getGlobalBounds();
    return rect.left;
}

float Paddle::rightSide() const
{
    sf::Rect rect = getGlobalBounds();
    return rect.left + rect.width;
}

float Paddle::topOfPaddle() const
{
    return getPosition().y - getSize().y;
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
    if (dir == Right) {
        newPosition.x += distance;
    }
    if (dir == Left) {
        newPosition.x -= distance;
    }
    setPosition(newPosition);
}

