#include "Animation.h"
#include "Game.h"

Animation::Animation(sf::Vector2f pos) : ball(new Ball(8.0f, 200.0f))
{
    sf::Vector2f tileSize = sf::Vector2f(30.0f, 10.0f);
    setPosition(pos);
    setSize(sf::Vector2f(10.0f*32.f,8.0f*12.0f));
    setFillColor(sf::Color::Black);
    setOutlineColor(Blue);
    setOutlineThickness(2.0f);
    for (int i = 0; i < 32; i++)
    {
        tile[i] = new Tile(0,0,30,10);
    }
    for (int i = 0; i < 8; i++)
    {
        tile[i]->setPosition(pos.x + tileSize.x/2.f, pos.y + i * 12.0f + tileSize.y / 2.f + 1.0f);
        tile[i]->setSize(tileSize);
        tile[i]->setFillColor(RandomColor[rand()%10]);
        tile[i+8]->setPosition(pos.x + tileSize.x/2.f + 9.0f * (tileSize.x + 2.0f), pos.y + i * 12.0f + tileSize.y / 2.f + 1.0f);
        tile[i+8]->setSize(tileSize);
        tile[i+8]->setFillColor(RandomColor[rand()%10]);
    }
    for (int i = 0; i < 8; i++)
    {
        tile[i+16]->setPosition(pos.x + tileSize.x/2.f + (i + 1) * (tileSize.x + 2.0f), pos.y + tileSize.y / 2.f + 1.0f);
        tile[i+16]->setSize(tileSize);
        tile[i+16]->setFillColor(RandomColor[rand()%10]);
        tile[i+24]->setPosition(pos.x + tileSize.x/2.f + (i + 1) * (tileSize.x + 2.0f), pos.y + 7.0f * (tileSize.y + 2.0f) + tileSize.y / 2.f + 1.0f);
        tile[i+24]->setSize(tileSize);
        tile[i+24]->setFillColor(RandomColor[rand()%10]);
    }
    sf::FloatRect rect = getGlobalBounds();
    ball->setPosition(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
    ball->setActive(false);
    ball->setFillColor(RandomColor[rand()%10]);
    ball->setSpeed(200.f + rand() % 100);
    ball->setAngle(35.f + rand()% 20);
}

Animation::~Animation()
{
    for (int i = 0; i < 20; i++)
    {
        delete tile[i];
        tile[i] = nullptr;
    }
}

void Animation::draw(sf::RenderWindow& window)
{
    window.draw(*this);
    for (int i = 0; i < 32; i++)
    {
        window.draw(*(tile[i]));
    }
    window.draw(*ball);
}

void Animation::hitATile()
{
    float angle;
    for (int i = 0; i < 32; i++ )
    {
        Game::SideOfTile side = hitTileSide(tile[i]);
        if (side == Game::SideOfTile::None) continue;
        switch (side)
        {
        case Game::SideOfTile::Bottom:
            ball->setDirection(Ball::Direction::Down);
            ball->moveDown(5);
            break;
        case Game::SideOfTile::Top:
            ball->setDirection(Ball::Direction::Up);
            ball->moveUp(3);
            break;
        case Game::SideOfTile::Right:
            ball->moveRight(5.0f);
            angle = ball->getAngle();
            ball->setAngle(-angle);
            break;
        case Game::SideOfTile::Left:
            ball->moveLeft(5.0f);
            angle = ball->getAngle();
            ball->setAngle(-angle);
            break;
        default:
            ;
        }
    }
}

Game::SideOfTile Animation::hitTileSide(const Tile* tile) const
{
    float ballX, ballY;

    ballX= ball->getPosition().x;
    ballY = ball->getPosition().y;

    if (ball->getDirection() == Ball::Direction::Up   && ball->top() < tile->bottom() && ballY > tile->top() && ballX >= tile->left() && ballX <= tile->right())
        return Game::SideOfTile::Bottom;
    if (ball->getDirection() == Ball::Direction::Down && ball->bottom() >= tile->top() && ball->top() <= tile->bottom() && ball->top() < tile->bottom() && ballX >= tile->left() && ballX <= tile->right())
        return Game::SideOfTile::Top;
    if (ball->right() >= tile->left() && ball->left() <= tile->left() && ballY >= tile->top() && ballY <= tile->bottom())
        return Game::SideOfTile::Left;
    if (ball->left() <= tile->right() && ball->right() >= tile->right() && ballY >= tile->top() && ballY <= tile->bottom())
        return Game::SideOfTile::Right;
    return Game::SideOfTile::None;
}

void Animation::update(sf::Time dt)
{
    ball->update(dt);
}

