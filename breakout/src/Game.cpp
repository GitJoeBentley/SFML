#include <cmath>
#include <string>
using namespace std;
#include "Game.h"

Game::Game(sf::RenderWindow& wnd, const std::string& name_, int balls, float ballspeed, int time_remaining)
    : window(wnd), name(name_), numBalls(balls),  ballSpeed(ballspeed), timeRemaining(time_remaining),
      gameWindow(GameWindowSize), ballsLeft(new sf::CircleShape[balls]), ballsLeftText("Balls Left", font, 24),
      timeRemainingText("", font, 24)
{
    font.loadFromFile(ResourcesPath + "Arial.ttf");
    // Game Name Text
    gameNameText.setFont(font);
    gameNameText.setString(name_);
    gameNameText.setFillColor(sf::Color(sf::Color::Yellow));
    gameNameText.setPosition(860.0f,30.0f);

    scoreText.setString("Score 0");
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color(150,150,250));
    scoreText.setPosition(900.0f,140.0f);

    timeRemainingText.setFillColor(sf::Color(250,150,150));
    timeRemainingText.setPosition(900.0f,300.0f);

    for (int i = 0; i < balls; i++)
    {
        ballsLeft[i].setRadius(10.0f);
        ballsLeft[i].setFillColor(sf::Color::White);
        ballsLeft[i].setPosition(sf::Vector2f(900.0f + i * 30.f, 250.f));
    }

    ballsLeftText.setFillColor(sf::Color(150,250,150));
    ballsLeftText.setPosition(900.0f,210.0f);

    gameWindow.setFillColor(sf::Color::Black);
    gameWindow.setOutlineColor(sf::Color::Blue);
    gameWindow.setOutlineThickness(20.0f);
    gameWindow.setPosition(GameBorderWidth,GameBorderWidth);
}

Game::~Game()
{
    delete tiles;
    tiles = nullptr;
    delete ball;
    ball = nullptr;
    delete paddle;
    paddle = nullptr;
}

Paddle* Game::getPaddle()
{
    return paddle;
}

Ball* Game::getBall()
{
    return ball;
}

Tiles* Game::getTiles()
{
    return tiles;
}

std::string Game::getName() const
{
    return name;
}

sf::RectangleShape& Game::getGameWindow()
{
    return gameWindow;
}

int Game::getNumTiles() const
{
    return numTiles;
}

int Game::getNumBalls() const
{
    return numBalls;
}

int Game::getTimeRemaining() const
{
    return timeRemaining;
}

Game::GameStatus Game::getStatus() const
{
    return status;
}

sf::Vector2f Game::getCenterOfGameWindow() const
{
    sf::FloatRect globalRect = gameWindow.getGlobalBounds();
    sf::FloatRect localRect = gameWindow.getLocalBounds();
    sf::Vector2f center = sf::Vector2f(globalRect.top + localRect.width/2.0f, globalRect.left + localRect.height/2.0f);
    return center;
}

///// Setters  /////

void Game::setStatus(Game::GameStatus status_)
{
    status = status_;
}

void Game::decrementTimeRemaining()
{
    timeRemaining--;
}

int Game::hitATile()
{
    Tile* tilePtr;
    sf::FloatRect ballLocation = ball->getGlobalBounds();
    sf::FloatRect tileLocation;
    float angle;

    for (int row = 0; row < tiles->getNumRows(); row++)
    {
        for (int col = 0; col < tiles->getNumCols(); col++)
        {
            tilePtr = tiles->getTile(row,col);
            if (!tilePtr) continue;
            tileLocation = tilePtr->getGlobalBounds();
            if (ballLocation.intersects(tileLocation))
            {
                SideOfTile side = hitTileSide(tilePtr);
                switch (side)
                {
                case SideOfTile::Bottom:
                    //std::cout << "bottom" << endl;
                    ball->setDirection(Ball::Direction::Down);
                    break;
                case SideOfTile::Top:
                    ball->setDirection(Ball::Direction::Up);
                    //std::cout << "top" << endl;
                    break;
                case SideOfTile::Right:
                    //std::cout << "right" << endl;
                    ball->moveLeft(2.0f);
                    angle = ball->getAngle();
                    if (fabs(angle) < 30.0) angle = 1.5f * angle;
                    ball->setAngle(-angle);
                    break;
                case SideOfTile::Left:
                    //std::cout << "left: " << ball->getAngle() << endl;
                    ball->moveRight(2.0f);
                    angle = ball->getAngle();
                    if (fabs(angle) < 30.0) angle = 1.5f * angle;
                    ball->setAngle(-angle);
                    break;
                default:
                    ;
                }
                if (side != SideOfTile::None)
                {
                    tiles->removeTile(row, col);
                    numTiles--;
                    if (name == "One Red Tile" && tilePtr->getFillColor() == sf::Color::Red)
                        return 100;
                    else
                        return 1;
                }
            }
        }
    }
    return 0;
}

Game::SideOfTile Game::hitTileSide(const Tile* tile) const
{
    float topofball, bottomofball, topoftile, bottomoftile, rightsideofball, leftsideofball, rightsideoftile, leftsideoftile, ballxpos, ballypos;

    ballxpos = ball->getPosition().x;
    ballypos = ball->getPosition().y;

    topofball = roundf(ball->getPosition().y - ball->getRadius());
    bottomofball = roundf(ball->getPosition().y + ball->getRadius());

    rightsideofball = ball->getPosition().x + ball->getRadius();
    leftsideofball = ball->getPosition().x - ball->getRadius();

    rightsideoftile = tile->getPosition().x + tile->getSize().x/2.0f;
    leftsideoftile = tile->getPosition().x - tile->getSize().x/2.0f;

    topoftile = tile->getPosition().y - tile->getSize().y / 2.0f;
    bottomoftile = tile->getPosition().y + tile->getSize().y / 2.0f;

    if      (ball->getDirection() == Ball::Direction::Up && topofball <= bottomoftile && ballxpos >= leftsideoftile && ballxpos <= rightsideoftile) return SideOfTile::Bottom;
    else if (ball->getDirection() == Ball::Direction::Down && bottomofball >= topoftile && ballxpos >= leftsideoftile && ballxpos <= rightsideoftile) return SideOfTile::Top;
    else if (rightsideofball >= leftsideoftile && ballypos >= topoftile && ballypos <= bottomoftile) return SideOfTile::Left;
    else if (leftsideofball <= rightsideoftile && ballypos >= topoftile && ballypos <= bottomoftile) return SideOfTile::Right;
    else {};
    return SideOfTile::None;
}

void Game::drawBallsLeft()
{
    window.draw(ballsLeftText);
    for (int i = 0; i < numBalls; i++) window.draw(ballsLeft[i]);
}

sf::Text& Game::getTimeRemainingText()
{
    timeRemainingText.setString("Time Remaining " + std::to_string(timeRemaining));
    return timeRemainingText;
}
