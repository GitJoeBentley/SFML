#include "CrazyBall.h"
#include "Game.h"

CrazyBall::CrazyBall(sf::RenderWindow& wnd) : Game(wnd, 3)
{
    setup();
}

void CrazyBall::setup()
{
    int tileRows = 8;
    int tileCols = 10;
    float tileWidth = 60.0f;
    ball[0] = new Ball(9.0f);  // radius = 9, starting speed = 500.f
    tiles = new Tiles(tileRows, tileCols, tileWidth, 16.0f, tileWidth);      // 8 rows, 12 columns, tile size 60x16
    numTiles = tileRows * tileCols;
    paddle = new Paddle(64.f);
    uint8_t redcolor = UINT8_MAX;
    uint8_t greencolor = 50;
    uint8_t bluecolor = 0;
    for (int row = 0; row < tileRows; row++)
    {
        //redcolor += UINT8_MAX / tileRows;
        for (int col = 0; col < tileCols; col++)
        {
            bluecolor += static_cast<uint8_t>(3);
            redcolor -= static_cast<uint8_t>(2);
            tiles->getTile(row, col)->setFillColor(sf::Color(redcolor,greencolor,bluecolor));
        }
    }
}

void CrazyBall::changeSpeed(int arg)
{
    switch (arg)
    {
    case 0:
        ball[0]->setSpeed(500.f);
        ball[0]->setFillColor(sf::Color::White);
        break;
    case 1:
        ball[0]->setSpeed(600.f);
        ball[0]->setFillColor(sf::Color::Green);
        break;
    case 2:
        ball[0]->setSpeed(700.f);
        ball[0]->setFillColor(sf::Color::Red);
        break;
    default:
        ;
    }
}

void CrazyBall::doCrazy()
{
    float gameWindowYPos = gameWindow.getSize().y / 2.f;
    int temp = rand()%32767;
    switch (temp)
    {
    case 1: // Change Ball speed
        changeSpeed(rand()%3);
        break;
    case 2:
        if (ball[0]->getDirection() == Ball::Direction::Down && ball[0]->getPosition().y < gameWindowYPos)
        {
            ball[0]->setFillColor(Orange);
            ball[0]->setAngle(ball[0]->getAngle()/2.0f);
        }
        break;
    case 3:
        if (ball[0]->getDirection() == Ball::Direction::Down && ball[0]->getPosition().y < gameWindowYPos)
        {
            ball[0]->setFillColor(sf::Color::Cyan);
            sf::Vector2f currentPos = ball[0]->getPosition();
            currentPos.x += rand() % 11 - 5;
            ball[0]->setPosition(currentPos);
        }
        break;
    case 4:
        if (ball[0]->getDirection() == Ball::Direction::Down)
        {
            ball[0]->setFillColor(sf::Color::Magenta);
            ball[0]->setDirection(Ball::Direction::Up);
            sf::sleep(sf::Time(sf::seconds(0.25f)));
            //clock.restart();
        }
        break;
    default:
        ;
    }
}

